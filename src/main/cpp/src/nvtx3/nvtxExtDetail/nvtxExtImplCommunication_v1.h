/*
* Copyright 2021-2023  NVIDIA Corporation.  All rights reserved.
*
* Licensed under the Apache License v2.0 with LLVM Exceptions.
* See https://llvm.org/LICENSE.txt for license information.
* SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
*/

#ifndef NVTX_EXT_IMPL_COMMUNICATION_GUARD
#error Never include this file directly -- it is automatically included by nvToolsExtCommunication.h (except when NVTX_NO_IMPL is defined).
#endif

#define NVTX_EXT_IMPL_GUARD
#include "nvtxExtImpl.h"
#undef NVTX_EXT_IMPL_GUARD

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NVTX_EXT_COMMUNICATION_VERSIONED_IDENTIFIER_L3(NAME, VERSION, COMPATID) \
    NAME##_v##VERSION##_mem##COMPATID
#define NVTX_EXT_COMMUNICATION_VERSIONED_IDENTIFIER_L2(NAME, VERSION, COMPATID) \
    NVTX_EXT_COMMUNICATION_VERSIONED_IDENTIFIER_L3(NAME, VERSION, COMPATID)
#define NVTX_EXT_COMMUNICATION_VERSIONED_ID(NAME) \
    NVTX_EXT_COMMUNICATION_VERSIONED_IDENTIFIER_L2(NAME, NVTX_VERSION, NVTX_EXT_COMMUNICATION_COMPATID)

#ifdef NVTX_DISABLE

#include "nvtxExtHelperMacros.h"

#define NVTX_EXT_FN_IMPL(ret_val, fn_name, signature, arg_names) \
ret_val fn_name signature { \
    NVTX_EXT_HELPER_UNUSED_ARGS arg_names \
    return ((ret_val)(intptr_t)-1); \
}

#else /*NVTX_DISABLE*/

/*
 * Function slots for the communication extension. First entry is the module
 * state, initialized to `0` (`NVTX_EXTENSION_FRESH`).
 */
NVTX_LINKONCE_DEFINE_GLOBAL intptr_t
NVTX_EXT_COMMUNICATION_VERSIONED_ID(nvtxExtCommSlots)[NVTX3EXT_CBID_COMMUNICATION_FN_NUM + 1]
    = {0};

/* Avoid warnings about missing prototype. */
NVTX_LINKONCE_FWDDECL_FUNCTION void NVTX_EXT_COMMUNICATION_VERSIONED_ID(nvtxExtCommunicationInitOnce)(void);
NVTX_LINKONCE_DEFINE_FUNCTION void NVTX_EXT_COMMUNICATION_VERSIONED_ID(nvtxExtCommunicationInitOnce)()
{
    intptr_t* fnSlots = NVTX_EXT_COMMUNICATION_VERSIONED_ID(nvtxExtCommSlots) + 1;
    nvtxExtModuleSegment_t segment = {
        0, // unused (only one segment)
        NVTX3EXT_CBID_COMMUNICATION_FN_NUM,
        fnSlots
    };

    nvtxExtModuleInfo_t module = {
        NVTX_VERSION, sizeof(nvtxExtModuleInfo_t),
        NVTX_EXT_COMMUNICATION_MODULEID, NVTX_EXT_COMMUNICATION_COMPATID,
        1, &segment, // number of segments, segments
        NULL, NULL
    };

    NVTX_INFO( "%s\n", __FUNCTION__  );

    NVTX_VERSIONED_IDENTIFIER(nvtxExtInitOnce)(&module,
        NVTX_EXT_COMMUNICATION_VERSIONED_ID(nvtxExtCommSlots));
}

#define NVTX_EXT_FN_IMPL(ret_type, fn_name, signature, arg_names) \
typedef ret_type (*fn_name##_impl_fntype)signature; \
/*NVTX_LINKONCE_DEFINE_FUNCTION*/ ret_type fn_name signature { \
    intptr_t slot = NVTX_EXT_COMMUNICATION_VERSIONED_ID(nvtxExtCommSlots)[NVTX3EXT_CBID_##fn_name + 1]; \
    if (slot != NVTX_EXTENSION_DISABLED) { \
        if (slot != NVTX_EXTENSION_FRESH) { \
            return (*(fn_name##_impl_fntype)slot) arg_names; \
        } else { \
            NVTX_EXT_COMMUNICATION_VERSIONED_ID(nvtxExtCommunicationInitOnce)(); \
            /* Re-read function slot after extension initialization. */ \
            slot = NVTX_EXT_COMMUNICATION_VERSIONED_ID(nvtxExtCommSlots)[NVTX3EXT_CBID_##fn_name + 1]; \
            if (slot != NVTX_EXTENSION_DISABLED && slot != NVTX_EXTENSION_FRESH) { \
                return (*(fn_name##_impl_fntype)slot) arg_names; \
            } \
        } \
    } \
    return ((ret_type)(intptr_t)-1); \
}

#endif /*NVTX_DISABLE*/

NVTX_EXT_FN_IMPL(void, nvtxCommMetadataRegister, (nvtxDomainHandle_t domain,
    const nvtxPayloadData_t* data, uint8_t type), (domain, data, type))

NVTX_EXT_FN_IMPL(void, nvtxCommParamsRegister, (nvtxDomainHandle_t domain, uint64_t payloadSchemaId, const nvtxCommParam_t* types, size_t numEntries, uint64_t op, const char* opName), (domain, payloadSchemaId, types, numEntries, op, opName))

NVTX_EXT_FN_IMPL(void, nvtxCommStart, (nvtxDomainHandle_t domain, uint64_t payloadSchemaId, void* params, size_t size, uint64_t request), (domain, payloadSchemaId, params, size, request))

NVTX_EXT_FN_IMPL(void, nvtxCommEnd, (nvtxDomainHandle_t domain, uint64_t request), (domain, request))

#undef NVTX_EXT_FN_IMPL

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */
