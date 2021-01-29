/*************************************************************************
 * Copyright (c) 2015-2019, NVIDIA CORPORATION. All rights reserved.
 *
 * See LICENSE.txt for license information
 ************************************************************************/

#include "enqueue.h"
#include <curand_kernel.h>


NCCL_API(ncclResult_t, ncclAllReduce, const void* sendbuff, void* recvbuff, size_t count,
    ncclDataType_t datatype, ncclRedOp_t op, ncclComm* comm, cudaStream_t stream);
ncclResult_t ncclAllReduce(const void* sendbuff, void* recvbuff, size_t count,
    ncclDataType_t datatype, ncclRedOp_t op, ncclComm* comm, cudaStream_t stream) {
   
  cudaSetDevice(comm->cudaDev);
  size_t nbytes = count * ncclTypeSize(datatype);
  void* tempbuff1;
  void* tempbuff2;
  void* tempbuff3;
  //const void* compressedbuff1;
  //void* compressedbuff2;
  void** tempbuff_ptr1 = &tempbuff1;
  //void** tempbuff_ptr2 = &tempbuff2;
  void** tempbuff_ptr3 = &tempbuff3;
  //const void** compressedbuff_ptr1 = &compressedbuff1;
  //void** compressedbuff_ptr2 = &compressedbuff2;

  //int num_buckets = 64 ;
  //int header_size = 2*num_buckets; 
  //cudaMalloc(tempbuff_ptr1, header_size*sizeof(float) + nbytes/4);

  int bucket_size;
  char* bucket_size_str = getenv("bucket_size");
  if (bucket_size_str == NULL) {
    bucket_size = 1024;
  } else {
    bucket_size = atoi(bucket_size_str);
  }

  int num_buckets = DIVUP(count, bucket_size);
  int meta_size = 2 * sizeof(float) * num_buckets;

  //cudaMalloc(tempbuff_ptr1, nbytes);
  cudaMalloc(tempbuff_ptr1, nbytes/4 + meta_size);
  //cudaMalloc(tempbuff_ptr2, nbytes/4 + meta_size);
  cudaMalloc(tempbuff_ptr3, nbytes);

  const unsigned int threadsPerBlock = 544;
  const unsigned int blockCount = 64;
  const unsigned int totalThreads = threadsPerBlock * blockCount;
  void * random_numbers;
  void * states;

  /* Allocate space for random_numbers on device */
  //cudaMalloc((void **)&random_numbers, totalThreads * sizeof(float));

  /* Allocate space for prng states on device */
  cudaMalloc((void **)&states, totalThreads * 16);
  //cudaMalloc((void **)&states, totalThreads * sizeof(curandStatePhilox4_32_10_t));
  //cudaMalloc((void **)&states, totalThreads * sizeof(curandStateMRG32k3a));
 
  cudaDeviceSynchronize();

  struct ncclInfo info = { ncclCollAllReduce, "AllReduce",
    sendbuff, recvbuff, tempbuff1, tempbuff2, tempbuff3, random_numbers, states, count, datatype, op, 0, comm, stream, /* Args */
    ALLREDUCE_CHUNKSTEPS, ALLREDUCE_SLICESTEPS};
  return ncclEnqueueCheck(&info);
}
