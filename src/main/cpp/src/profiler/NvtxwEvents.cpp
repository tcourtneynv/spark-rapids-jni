
#include <type_traits>

#include "NvtxwEvents.h"

namespace NvidiaNvtxw
{

#define PAYLOAD_ENTRY_SIMPLE(flags, type, name) \
    { (flags), (type), (name), nullptr, 0, 0, nullptr, nullptr }

// The C string containing the event's name must be provided in a special way.
static const nvtxPayloadSchemaEntry_t nameSchema[] = {
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_EVENT_MESSAGE | NVTX_PAYLOAD_ENTRY_FLAG_ARRAY_ZERO_TERMINATED,
        NVTX_PAYLOAD_ENTRY_TYPE_CSTRING,
        "name"
    )
};
static const nvtxPayloadSchemaAttr_t nameSchemaAttr{
        /*.fieldMask = */
        NVTX_PAYLOAD_SCHEMA_ATTR_TYPE |
        NVTX_PAYLOAD_SCHEMA_ATTR_FLAGS |
        NVTX_PAYLOAD_SCHEMA_ATTR_ENTRIES |
        NVTX_PAYLOAD_SCHEMA_ATTR_NUM_ENTRIES |
        NVTX_PAYLOAD_SCHEMA_ATTR_SCHEMA_ID,
        /*.name = */
        nullptr,
        /*.type = */
        NVTX_PAYLOAD_SCHEMA_TYPE_DYNAMIC,
        /*.flags = */
        NVTX_PAYLOAD_SCHEMA_FLAG_REFERENCED,
        /*.entries = */
        nameSchema,
        /*.numEntries = */
        std::extent<decltype(nameSchema)>::value,
        /*.payloadStaticSize = */
        0,
        /*.packAlign = */
        0,
        /*.schemaId = */
        NvidiaNvtxw::PayloadSchemaId::nameId,
        /*.extension = */
        nullptr
    };

static const nvtxPayloadSchemaEntry_t nvtxSchema[] = {
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_BEGIN | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_start"
    ),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_END | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_stop"
    ),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_EVENT_MESSAGE | NVTX_PAYLOAD_ENTRY_FLAG_POINTER,
        NVTX_PAYLOAD_ENTRY_TYPE_CSTRING,
        "name"
    ),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_POINTER, NVTX_PAYLOAD_ENTRY_TYPE_CSTRING,
        "domain"
    ),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "process_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "thread_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "color")    
};
// TimeBase = Relative
static const nvtxPayloadSchemaAttr_t nvtxSchemaAttr = {
    NVTX_PAYLOAD_SCHEMA_ATTR_NAME | NVTX_PAYLOAD_SCHEMA_ATTR_TYPE |
    NVTX_PAYLOAD_SCHEMA_ATTR_ENTRIES | NVTX_PAYLOAD_SCHEMA_ATTR_NUM_ENTRIES |
    NVTX_PAYLOAD_SCHEMA_ATTR_STATIC_SIZE | NVTX_PAYLOAD_SCHEMA_ATTR_SCHEMA_ID,
    "NVTX Event",
    NVTX_PAYLOAD_SCHEMA_TYPE_STATIC,
    NVTX_PAYLOAD_SCHEMA_FLAG_NONE,
    nvtxSchema,
    std::extent<decltype(nvtxSchema)>::value,
    sizeof(struct NvidiaNvtxw::nvtxEvent),
    0,
    NvidiaNvtxw::PayloadSchemaId::nvtxId,
    nullptr
};
static const nvtxPayloadSchemaEntry_t cuptiApiSchema[] = {
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_BEGIN | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_start"
    ),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_END | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_stop"
    ),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "kind"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "cbid"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "process_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "thread_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "correlation_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "return_value")
};
static const nvtxPayloadSchemaAttr_t cuptiApiSchemaAttr = {
    NVTX_PAYLOAD_SCHEMA_ATTR_NAME | NVTX_PAYLOAD_SCHEMA_ATTR_TYPE |
    NVTX_PAYLOAD_SCHEMA_ATTR_ENTRIES | NVTX_PAYLOAD_SCHEMA_ATTR_NUM_ENTRIES |
    NVTX_PAYLOAD_SCHEMA_ATTR_STATIC_SIZE | NVTX_PAYLOAD_SCHEMA_ATTR_SCHEMA_ID,
    "CUPTI API Activity",
    NVTX_PAYLOAD_SCHEMA_TYPE_STATIC,
    NVTX_PAYLOAD_SCHEMA_FLAG_NONE,
    cuptiApiSchema,
    std::extent<decltype(cuptiApiSchema)>::value,
    sizeof(struct NvidiaNvtxw::cuptiApiEvent),
    0,
    NvidiaNvtxw::PayloadSchemaId::cuptiApiId,
    nullptr
};
static const nvtxPayloadSchemaEntry_t cuptiMemcpySchema[] = {
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_BEGIN | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_start"
    ),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_END | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_stop"
    ),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "bytes"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "graph_node_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "device_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "context_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "stream_id"),
    //TODO new field
    //PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "process_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "correlation_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "runtime_correlation_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "graph_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "channel_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "channel_type"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "copy_kind"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "src_kind"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "dst_kind")
};
static const nvtxPayloadSchemaAttr_t cuptiMemcpySchemaAttr = {
    NVTX_PAYLOAD_SCHEMA_ATTR_NAME | NVTX_PAYLOAD_SCHEMA_ATTR_TYPE |
    NVTX_PAYLOAD_SCHEMA_ATTR_ENTRIES | NVTX_PAYLOAD_SCHEMA_ATTR_NUM_ENTRIES |
    NVTX_PAYLOAD_SCHEMA_ATTR_STATIC_SIZE | NVTX_PAYLOAD_SCHEMA_ATTR_SCHEMA_ID,
    "CUPTI Memcpy",
    NVTX_PAYLOAD_SCHEMA_TYPE_STATIC,
    NVTX_PAYLOAD_SCHEMA_FLAG_NONE,
    cuptiMemcpySchema,
    std::extent<decltype(cuptiMemcpySchema)>::value,
    sizeof(struct NvidiaNvtxw::cuptiMemcpyEvent),
    0,
    NvidiaNvtxw::PayloadSchemaId::cuptiMemcpyId,
    nullptr
};
static const nvtxPayloadSchemaEntry_t cuptiMemsetSchema[] = {
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_BEGIN | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_start"
    ),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_END | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_stop"
    ),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "bytes"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "graph_node_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "device_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "context_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "stream_id"),
    //TODO new field
    //PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "process_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "correlation_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "graph_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "channel_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "value"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "channel_type"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "mem_kind"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "flags")
};
static const nvtxPayloadSchemaAttr_t cuptiMemsetSchemaAttr = {
    NVTX_PAYLOAD_SCHEMA_ATTR_NAME | NVTX_PAYLOAD_SCHEMA_ATTR_TYPE |
    NVTX_PAYLOAD_SCHEMA_ATTR_ENTRIES | NVTX_PAYLOAD_SCHEMA_ATTR_NUM_ENTRIES |
    NVTX_PAYLOAD_SCHEMA_ATTR_STATIC_SIZE | NVTX_PAYLOAD_SCHEMA_ATTR_SCHEMA_ID,
    "CUPTI Memset",
    NVTX_PAYLOAD_SCHEMA_TYPE_STATIC,
    NVTX_PAYLOAD_SCHEMA_FLAG_NONE,
    cuptiMemsetSchema,
    std::extent<decltype(cuptiMemsetSchema)>::value,
    sizeof(struct NvidiaNvtxw::cuptiMemsetEvent),
    0,
    NvidiaNvtxw::PayloadSchemaId::cuptiMemsetId,
    nullptr
};
static const nvtxPayloadSchemaEntry_t cuptiDeviceSchema[] = {
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "global_memory_bandwidth"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "global_memory_size"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "constant_memory_size"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "l2_cache_size"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "num_threads_per_warp"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "core_clock_rate"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "num_memcpy_engines"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "num_multiprocessors"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_ipc"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_warps_per_multiprocessor"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_blocks_per_multiprocessor"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_shared_memory_per_multiprocessor"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_registers_per_multiprocessor"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_registers_per_block"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_shared_memory_per_block"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_threads_per_block"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_block_dim_x"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_block_dim_y"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_block_dim_z"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_grid_dim_x"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_grid_dim_y"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "max_grid_dim_z"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "compute_capability_major"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "compute_capability_minor"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "ecc_enabled"),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_EVENT_MESSAGE | NVTX_PAYLOAD_ENTRY_FLAG_POINTER,
        NVTX_PAYLOAD_ENTRY_TYPE_CSTRING,
        "name"
    )   
};
static const nvtxPayloadSchemaAttr_t cuptiDeviceSchemaAttr = {
    NVTX_PAYLOAD_SCHEMA_ATTR_NAME | NVTX_PAYLOAD_SCHEMA_ATTR_TYPE |
    NVTX_PAYLOAD_SCHEMA_ATTR_ENTRIES | NVTX_PAYLOAD_SCHEMA_ATTR_NUM_ENTRIES |
    NVTX_PAYLOAD_SCHEMA_ATTR_STATIC_SIZE | NVTX_PAYLOAD_SCHEMA_ATTR_SCHEMA_ID,
    "CUPTI Device",
    NVTX_PAYLOAD_SCHEMA_TYPE_STATIC,
    NVTX_PAYLOAD_SCHEMA_FLAG_NONE,
    cuptiDeviceSchema,
    std::extent<decltype(cuptiDeviceSchema)>::value,
    sizeof(struct NvidiaNvtxw::cuptiDevice),
    0,
    NvidiaNvtxw::PayloadSchemaId::cuptiDeviceId,
    nullptr
};
static const nvtxPayloadSchemaEntry_t cuptiKernelSchema[] = {
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_BEGIN | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_start"
    ),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_END | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_stop"
    ),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "completed"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "grid_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "queued"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "submitted"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "graph_node_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT64, "local_memory_total_v2"),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_EVENT_MESSAGE | NVTX_PAYLOAD_ENTRY_FLAG_POINTER,
        NVTX_PAYLOAD_ENTRY_TYPE_CSTRING,
        "name"
    ),    
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "device_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "context_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "stream_id"),
    //TODO new field
    //PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "process_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "grid_x"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "grid_y"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "grid_z"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "block_x"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "block_y"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "block_z"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "static_shared_memory"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "dynamic_shared_memory"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "local_memory_per_thread"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "local_memory_total"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "correlation_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "shared_memory_executed"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "graph_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "channel_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "cluster_x"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "cluster_y"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "cluster_z"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "cluster_scheduling_policy"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT16, "registers_per_thread"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "requested"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "executed"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "shared_memory_config"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "partitioned_global_cache_requested"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "partitioned_global_cache_executed"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "launch_type"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "is_shared_memory_carveout_requested"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "shared_memory_carveout_requested"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "shmem_limit_config"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "channel_type")
};
static const nvtxPayloadSchemaAttr_t cuptiKernelSchemaAttr = {
    NVTX_PAYLOAD_SCHEMA_ATTR_NAME | NVTX_PAYLOAD_SCHEMA_ATTR_TYPE |
    NVTX_PAYLOAD_SCHEMA_ATTR_ENTRIES | NVTX_PAYLOAD_SCHEMA_ATTR_NUM_ENTRIES |
    NVTX_PAYLOAD_SCHEMA_ATTR_STATIC_SIZE | NVTX_PAYLOAD_SCHEMA_ATTR_SCHEMA_ID,
    "CUPTI Kernel",
    NVTX_PAYLOAD_SCHEMA_TYPE_STATIC,
    NVTX_PAYLOAD_SCHEMA_FLAG_NONE,
    cuptiKernelSchema,
    std::extent<decltype(cuptiKernelSchema)>::value,
    sizeof(struct NvidiaNvtxw::cuptiKernelEvent),
    0,
    NvidiaNvtxw::PayloadSchemaId::cuptiKernelId,
    nullptr
};
static const nvtxPayloadSchemaEntry_t cuptiOverheadSchema[] = {
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_BEGIN | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_start"
    ),
    PAYLOAD_ENTRY_SIMPLE(
        NVTX_PAYLOAD_ENTRY_FLAG_RANGE_END | NVTX_PAYLOAD_ENTRY_FLAG_EVENT_TIMESTAMP,
        NVTX_PAYLOAD_ENTRY_TYPE_UINT64,
        "time_stop"
    ),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "process_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT32, "thread_id"),
    PAYLOAD_ENTRY_SIMPLE(0, NVTX_PAYLOAD_ENTRY_TYPE_UINT8, "overhead_kind"),
};
static const nvtxPayloadSchemaAttr_t cuptiOverheadSchemaAttr = {
    NVTX_PAYLOAD_SCHEMA_ATTR_NAME | NVTX_PAYLOAD_SCHEMA_ATTR_TYPE |
    NVTX_PAYLOAD_SCHEMA_ATTR_ENTRIES | NVTX_PAYLOAD_SCHEMA_ATTR_NUM_ENTRIES |
    NVTX_PAYLOAD_SCHEMA_ATTR_STATIC_SIZE | NVTX_PAYLOAD_SCHEMA_ATTR_SCHEMA_ID,
    "CUPTI Overhead",
    NVTX_PAYLOAD_SCHEMA_TYPE_STATIC,
    NVTX_PAYLOAD_SCHEMA_FLAG_NONE,
    cuptiOverheadSchema,
    std::extent<decltype(cuptiOverheadSchema)>::value,
    sizeof(struct NvidiaNvtxw::cuptiOverheadEvent),
    0,
    NvidiaNvtxw::PayloadSchemaId::cuptiOverheadId,
    nullptr
};
#undef PAYLOAD_ENTRY_SIMPLE

const nvtxPayloadSchemaAttr_t* GetNameSchemaAttr()
{
    return &nameSchemaAttr;
}
const nvtxPayloadSchemaAttr_t* GetNvtxSchemaAttr()
{
    return &nvtxSchemaAttr;
}
const nvtxPayloadSchemaAttr_t* GetCuptiApiSchemaAttr()
{
    return &cuptiApiSchemaAttr;
}
const nvtxPayloadSchemaAttr_t* GetCuptiDeviceSchemaAttr()
{
    return &cuptiDeviceSchemaAttr;
}
const nvtxPayloadSchemaAttr_t* GetCuptiKernelSchemaAttr()
{
    return &cuptiKernelSchemaAttr;
}
const nvtxPayloadSchemaAttr_t* GetCuptiMemcpySchemaAttr()
{
    return &cuptiMemcpySchemaAttr;
}
const nvtxPayloadSchemaAttr_t* GetCuptiMemsetSchemaAttr()
{
    return &cuptiMemsetSchemaAttr;
}
const nvtxPayloadSchemaAttr_t* GetCuptiOverheadSchemaAttr()
{
    return &cuptiOverheadSchemaAttr;
}
}