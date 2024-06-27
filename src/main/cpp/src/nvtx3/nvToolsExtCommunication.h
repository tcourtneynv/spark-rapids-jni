/*
* Copyright 2021-2023 NVIDIA Corporation.  All rights reserved.
*
* Licensed under the Apache License v2.0 with LLVM Exceptions.
* See https://llvm.org/LICENSE.txt for license information.
* SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
*/

#include "nvToolsExtPayload.h"

#ifndef NVTOOLSEXTV3_COMMUNICATION_V1
#define NVTOOLSEXTV3_COMMUNICATION_V1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* \cond SHOW_HIDDEN
 * \brief A compatibility ID value used in structures and initialization to
 * identify version differences.
 */
#define NVTX_EXT_COMMUNICATION_COMPATID 0x0102

#define NVTX_EXT_COMMUNICATION_MODULEID 3

/**
 * \brief Additional value for the enum nvtxPayloadType_t
 *
 * This can be used, if there is only one binary payload with communication
 * parameters.
 */
#define NVTX_PAYLOAD_TYPE_COMMUNICATION 10

/**
 * \brief Types of communication operation.
 *
 * Each base communication category or property owns a bit (starting with 1<<8)
 * and uses the lower 8 bits to distinguish communications operations within
 * this category.
 *
 * Communication operation types are passed as `uint64_t` to
 * `nvtxCommParamsRegister`.
 */
#define NVTX_COMMUNICATION_OP_UNKNOWN     0

/*** Collective communication operations ***/
#define NVTX_COMMUNICATION_OP_COLLECTIVE     (1 << 8)
#define NVTX_COMMUNICATION_OP_BARRIER        (NVTX_COMMUNICATION_OP_COLLECTIVE + 1)
#define NVTX_COMMUNICATION_OP_BOADCAST       (NVTX_COMMUNICATION_OP_COLLECTIVE + 2)
#define NVTX_COMMUNICATION_OP_ALLTOALL       (NVTX_COMMUNICATION_OP_COLLECTIVE + 3)
#define NVTX_COMMUNICATION_OP_ALLGATHER      (NVTX_COMMUNICATION_OP_COLLECTIVE + 4)
#define NVTX_COMMUNICATION_OP_GATHER         (NVTX_COMMUNICATION_OP_COLLECTIVE + 5)
#define NVTX_COMMUNICATION_OP_REDUCE         (NVTX_COMMUNICATION_OP_COLLECTIVE + 6)
#define NVTX_COMMUNICATION_OP_SCATTER        (NVTX_COMMUNICATION_OP_COLLECTIVE + 7)
#define NVTX_COMMUNICATION_OP_REDUCE_SCATTER (NVTX_COMMUNICATION_OP_COLLECTIVE + 8)

/*** Point-to-point (two-sided) communication operations ***/
#define NVTX_COMMUNICATION_OP_PT_TO_PT (1 << 9)
#define NVTX_COMMUNICATION_OP_SEND     (NVTX_COMMUNICATION_OP_PT_TO_PT + 1)
#define NVTX_COMMUNICATION_OP_RECV     (NVTX_COMMUNICATION_OP_PT_TO_PT + 2)
#define NVTX_COMMUNICATION_OP_SENDRECV \
    (NVTX_COMMUNICATION_OP_SEND | NVTX_COMMUNICATION_OP_RECV)

/*** Remote memory access (one-sided) operations ***/
#define NVTX_COMMUNICATION_OP_RMA (1 << 10)
#define NVTX_COMMUNICATION_OP_PUT        (NVTX_COMMUNICATION_OP_RMA + 1)
#define NVTX_COMMUNICATION_OP_GET        (NVTX_COMMUNICATION_OP_RMA + 2)

/* RMA subcategory - atomic operations */
#define NVTX_COMMUNICATION_OP_ATOMIC (NVTX_COMMUNICATION_OP_RMA | (1 << 7))

/* RMA atomic fetch operations can be combined with inc, add, and, or and xor */
#define NVTX_COMMUNICATION_OP_FETCH (NVTX_COMMUNICATION_OP_ATOMIC | (1 << 6))

#define NVTX_COMMUNICATION_OP_SET     (NVTX_COMMUNICATION_OP_ATOMIC + 3)
#define NVTX_COMMUNICATION_OP_SWAP    (NVTX_COMMUNICATION_OP_ATOMIC + 4)
#define NVTX_COMMUNICATION_OP_CMPSWAP (NVTX_COMMUNICATION_OP_ATOMIC + 5)
#define NVTX_COMMUNICATION_OP_INC     (NVTX_COMMUNICATION_OP_ATOMIC + 6)
#define NVTX_COMMUNICATION_OP_ADD     (NVTX_COMMUNICATION_OP_ATOMIC + 7)
#define NVTX_COMMUNICATION_OP_AND     (NVTX_COMMUNICATION_OP_ATOMIC + 8)
#define NVTX_COMMUNICATION_OP_OR      (NVTX_COMMUNICATION_OP_ATOMIC + 9)
#define NVTX_COMMUNICATION_OP_XOR     (NVTX_COMMUNICATION_OP_ATOMIC + 10)

/* Element-wise atomic reduction operation, e.g. MPI_Accumulate */
#define NVTX_COMMUNICATION_OP_ACCUMULATE (NVTX_COMMUNICATION_OP_ATOMIC + 11)
#define NVTX_COMMUNICATION_OP_RMA_GET_ACCUMULATE \
    (NVTX_COMMUNICATION_OP_FETCH | NVTX_COMMUNICATION_OP_RMA_ACCUMULATE)

/*** Asynchronous completion ***/
#define NVTX_COMMUNICATION_OP_TEST      (1 << 11)
#define NVTX_COMMUNICATION_OP_WAIT      (2 << 11) /* MPI_Wait, shmem_quiet */
#define NVTX_COMMUNICATION_OP_COND_WAIT (3 << 11) /* shmem_wait_until* */
#define NVTX_COMMUNICATION_OP_FENCE     (4 << 11) /* communication order */

/*** Non-blocking/asynchronous/immediate communication operation ***/
#define NVTX_COMMUNICATION_OP_ASYNC     (1 << 14)

/* E.g. `shmem_put_signal` or any other signaling operation. */
#define NVTX_COMMUNICATION_OP_SIGNAL    (1 << 15)

/* Diagnostic communication operation */
#define NVTX_COMMUNICATION_OP_DIAGNOSTIC (1 << 16)


/**
 * \brief Communication parameter types.
 *
 * Communication parameter types are annotated to NVTX binary payload schema
 * entries as `uint64_t` via `nvtxCommParam_t`.
 * If no communication operation is provided a more explicit parameter such as
 * `*PARAM_SRC` instead of `*PARAM_REMOTE` is helpful in a potential follow-up
 * data analysis.
 */

#define NVTX_COMMUNICATION_PARAM_UNKNOWN  0

/**
 * Parameters for  communication teams and partner(s) matching
 */

/* Communication team, e.g. MPI communicator, SHMEM team. */
#define NVTX_COMMUNICATION_PARAM_TEAM     1

/* Communication context, e.g. SHMEM or UCP context. */
#define NVTX_COMMUNICATION_PARAM_CONTEXT  2

/* Root process/rank/PE in a collective. */
#define NVTX_COMMUNICATION_PARAM_ROOT     3

/* Local resource ID, e.g. process, MPI rank, SHMEM PE or UCP worker address or
EP, GPU ID. This might be implicitly the process/thread that writes the event. */
#define NVTX_COMMUNICATION_PARAM_LOCAL    4

/* Message matching tag (integral type expected) */
#define NVTX_COMMUNICATION_PARAM_TAG      5
#define NVTX_COMMUNICATION_PARAM_SEND_TAG 6
#define NVTX_COMMUNICATION_PARAM_RECV_TAG 7

/* Communication partner ID, e.g. remote process, MPI rank, SHMEM PE, UCP worker
address or EP, GPU ID. Source and destination version are e.g. required for
MPI_Sendrecv and might be used to specify the communication direction, e.g. in
point-to-point communication, a “remote source” parameter indicates a receive
operation. */
#define NVTX_COMMUNICATION_PARAM_REMOTE   8
#define NVTX_COMMUNICATION_PARAM_SRC      9
#define NVTX_COMMUNICATION_PARAM_DST     10

/**
 * Source and destination resource types: The expected value is of type
 * `enum nvtxCommunicationEndpointType` or if not available a string.
 */
#define NVTX_COMMUNICATION_PARAM_SRC_TYPE 17
#define NVTX_COMMUNICATION_PARAM_DST_TYPE 18

/**
 * Data addresses and layout, e.g. shmem_{alltoalls,iput,iget}
 */
#define NVTX_COMMUNICATION_PARAM_SRC_ADDR   19
#define NVTX_COMMUNICATION_PARAM_SRC_STRIDE 20
#define NVTX_COMMUNICATION_PARAM_DST_ADDR   21
#define NVTX_COMMUNICATION_PARAM_DST_STRIDE 22

/**
 * Amount of data to be transferred (BYTES ELEM_NUM * ELEM_SIZE), e.g.
 * MPI_{Scatter,Gather,Sendrecv}. Integral types are expected.
 */
#define NVTX_COMMUNICATION_PARAM_BYTES_SEND     23
#define NVTX_COMMUNICATION_PARAM_BYTES_RECV     24
#define NVTX_COMMUNICATION_PARAM_ELEM_NUM_SEND  25
#define NVTX_COMMUNICATION_PARAM_ELEM_NUM_RECV  26
#define NVTX_COMMUNICATION_PARAM_ELEM_SIZE_SEND 27 /* in bytes */
#define NVTX_COMMUNICATION_PARAM_ELEM_SIZE_RECV 28 /* in bytes */

/**
 * The field represents a bytes/address value. The communication direction might
 * be determined via the API name (NVTX message).
 */
#define NVTX_COMMUNICATION_PARAM_BYTES          29
#define NVTX_COMMUNICATION_PARAM_ADDR           30

/**
 * Expects a value of `NVTX_PAYLOAD_ENTRY_TYPE_*` or a fixed-size C-string
 * (char typename[] “int32_t”).
 */
#define NVTX_COMMUNICATION_PARAM_ELEM_DATATYPE  33

/**
 * Conditional communication operations, e.g. shmem_{test,wait_until}
 */
#define NVTX_COMMUNICATION_PARAM_CMP_VALUE      41
#define NVTX_COMMUNICATION_PARAM_CMP_OP         42
#define NVTX_COMMUNICATION_PARAM_INDEX          43
#define NVTX_COMMUNICATION_PARAM_STATUS         44

/**
 * Signal/notify operations, e.g. shmem_{put_signal,signal_fetch}
 */
#define NVTX_COMMUNICATION_PARAM_SIGNAL_ADDR    45
#define NVTX_COMMUNICATION_PARAM_SIGNAL_OP      46
#define NVTX_COMMUNICATION_PARAM_SIGNAL_VALUE   47

/**
 * Request handle for immediate/asynchronous communication.
 */
#define NVTX_COMMUNICATION_PARAM_REQUEST        48


/**
 * \brief Pair to map a communication parameter type to a payload schema entry.
 */
typedef struct nvtxCommParam_v1
{
    uint64_t payloadSchemaEntryIndex;
    uint64_t type;
} nvtxCommParam_t;


/**
 * \brief Annotate the entries of a binary payload schema with communication
 * parameter types.
 *
 * @param domain NVTX domain handle.
 * @param payloadSchemaId ID of the binary payload schema to be annotated.
 * @param types array of communication parameter types.
 * @param numEntries number annotated parameters/entries
 * @param op communication operation type. The value should be composed
 * (bitwise or) from enum nvtxCommOp_t
 * @param opName Optional name of the communication operation
 */
NVTX_DECLSPEC void NVTX_API nvtxCommParamsRegister(nvtxDomainHandle_t domain,
    uint64_t payloadSchemaId, const nvtxCommParam_t* types,
    size_t numEntries, uint64_t op, const char* opName);

/**
 * \brief Start and end of a local communication operation.
 *
 * If request is 0, a blocking communication operation is assumed. This
 * effectively means that two consecutives communication start or end events
 * with request 0 in the same domain are not valid.
 *
 * In collective communication, each participating process has to trigger the
 * start and end event. A non-blocking communication start may not be completed
 * with an end event. In this case, the request handle cannot be reused.
 *
 * @param size size of payload (parameter set) in bytes
 */
NVTX_DECLSPEC void NVTX_API nvtxCommStart(nvtxDomainHandle_t domain,
    uint64_t payloadSchemaId, void* params, size_t size,
    uint64_t request);
NVTX_DECLSPEC void NVTX_API nvtxCommEnd(nvtxDomainHandle_t domain,
    uint64_t request);


#define NVTX_COMMUNICATION_METADATA_INVALID 0
#define NVTX_COMMUNICATION_METADATA_TEAM    1
#define NVTX_COMMUNICATION_METADATA_LIBRARY 2

/**
 * @brief Pass generic communication metadata to the tool.
 *
 * Use the NVTX binary payload to pass arbitrary metadata to the tool. The
 * function is expected to be called off the critical path of a program.
 *
 * Intended metadata are communication teams and communication library details.
 */
NVTX_DECLSPEC void NVTX_API nvtxCommMetadataRegister(nvtxDomainHandle_t domain,
    const nvtxPayloadData_t* data, uint8_t type);

/**
 * \brief Callback IDs of API functions in the communication extension.
 *
 * The NVTX handler can use these values to register a handler function, similar
 * to the NVTX binary payload extension.
 */
#define NVTX3EXT_CBID_nvtxCommMetadataRegister       0
#define NVTX3EXT_CBID_nvtxCommParamsRegister         1
#define NVTX3EXT_CBID_nvtxCommStart                  2
#define NVTX3EXT_CBID_nvtxCommEnd                    3
#define NVTX3EXT_CBID_COMMUNICATION_FN_NUM           4

#ifdef __GNUC__
#pragma GCC visibility push(internal)
#endif

/* Extension types are required for the implementation and the NVTX handler. */
#define NVTX_EXT_TYPES_GUARD
#include "nvtxExtDetail/nvtxExtTypes.h"
#undef NVTX_EXT_TYPES_GUARD

#ifndef NVTX_NO_IMPL
#define NVTX_EXT_IMPL_COMMUNICATION_GUARD
#include "nvtxExtDetail/nvtxExtImplCommunication_v1.h"
#undef NVTX_EXT_IMPL_COMMUNICATION_GUARD
#endif /*NVTX_NO_IMPL*/

#ifdef __GNUC__
#pragma GCC visibility pop
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* NVTOOLSEXTV3_COMMUNICATION_V1 */
