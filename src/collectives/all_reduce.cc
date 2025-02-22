/*************************************************************************
 * Copyright (c) 2015-2019, NVIDIA CORPORATION. All rights reserved.
 *
 * See LICENSE.txt for license information
 ************************************************************************/

#include "enqueue.h"
//#include <curand_kernel.h>

NCCL_API(ncclResult_t, ncclAllReduce, const void* sendbuff, void* recvbuff, size_t count,
    ncclDataType_t datatype, ncclRedOp_t op, ncclComm* comm, cudaStream_t stream);
ncclResult_t ncclAllReduce(const void* sendbuff, void* recvbuff, size_t count,
    ncclDataType_t datatype, ncclRedOp_t op, ncclComm* comm, cudaStream_t stream) {


  //cudaSetDevice(comm->cudaDev);
  //size_t nbytes = count * ncclTypeSize(datatype);
  ////////void* tempbuff1;
  ////////void* tempbuff2;
  ////////void* tempbuff3;
  ////////void** tempbuff_ptr1 = &tempbuff1;
  ////////void** tempbuff_ptr2 = &tempbuff2;
  ////////void** tempbuff_ptr3 = &tempbuff3;

  //int bucket_size;
  //int bits=8;
  ////void * states;
  //char* ring_allReduce_version = getenv("RING_ALLREDUCE_VERSION");
  //if (strcasecmp(ring_allReduce_version, "new") == 0) {
  //  char* bucket_size_str = getenv("bucket_size");
  //  //int INITIAL_SIZE = 256*1024*1024;
  //  if (bucket_size_str == NULL) {
  //    bucket_size = 1024;
  //  } else {
  //    bucket_size = atoi(bucket_size_str);
  //  }
  //  int num_buckets = DIVUP(count, bucket_size);
  //  int meta_size = 2 * sizeof(float) * num_buckets;

  //  //char* quantization_size_per_entry = getenv("BITS");
  //  //if (quantization_size_per_entry == NULL) {
  //  //  bits = 8;
  //  //} else {
  //  //  bits = atoi(quantization_size_per_entry);
  //  //}

  //  //////cudaMalloc(tempbuff_ptr1, nbytes/4 + meta_size);
  //  //////cudaMalloc(tempbuff_ptr3, nbytes);
  //  //if (count > INITIAL_SIZE) {
  //  //   cudaFree(comm->hostDevComm.tempbuff1);
  //  //   cudaFree(comm->hostDevComm.tempbuff3);
  //  //   cudaMalloc((unsigned char**)&comm->hostDevComm.tempbuff1, nbytes/4 + meta_size);
  //  //   cudaMalloc((float**)&comm->hostDevComm.tempbuff3, nbytes);
  //  //}
  //  //cudaMalloc((void **)&states, 544 * 64 * sizeof(curandState));
  //  //cudaMemset(comm->hostDevComm.tempbuff1, 0, nbytes*bits/32 + meta_size);
  //  //cudaMemset(comm->hostDevComm.tempbuff1, 0, nbytes/4 + meta_size);
  //  //cudaMemset(comm->hostDevComm.tempbuff3, 0, nbytes);
  //  //comm->callIndex += 1;
  //  //comm->hostDevComm.callIndex = comm->opCount;
  //  //comm->callIndex = comm->opCount;
  //  //printf("opcount is %d\n", comm->opCount);
  //  //printf("opcount is %d\n", comm->collOpCount);
  //  //int* host_callIndex = (int*)malloc(4);
  //  //cudaMemcpy(host_callIndex, comm->hostDevComm.callIndex, 1 * sizeof(int), cudaMemcpyDeviceToHost);
  //  //host_callIndex[0] += 1;
  //  //cudaMemcpy(comm->hostDevComm.callIndex, host_callIndex, 1 * sizeof(int), cudaMemcpyHostToDevice);
  //}
  //cudaDeviceSynchronize();

  struct ncclInfo info = { ncclCollAllReduce, "AllReduce",
    sendbuff, recvbuff, count, datatype, op, 0, comm, stream, /* Args */
    ALLREDUCE_CHUNKSTEPS, ALLREDUCE_SLICESTEPS};
  return ncclEnqueueCheck(&info);
}
