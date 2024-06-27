#pragma once

#include <stdint.h>
#include <nvtx3/nvToolsExtPayload.h>

namespace NvidiaNvtxw 
{

namespace PayloadSchemaId 
{
    const uint64_t nameId          = 0xefefef00;
    const uint64_t nvtxId          = 0xefefef01;
    const uint64_t cuptiApiId      = 0xefefef02;
    const uint64_t cuptiMemcpyId   = 0xefefef03;
    const uint64_t cuptiMemsetId   = 0xefefef04;
    const uint64_t cuptiDeviceId   = 0xefefef05;
    const uint64_t cuptiKernelId   = 0xefefef06;
    const uint64_t cuptiOverheadId = 0xefefef07;
};

const nvtxPayloadSchemaAttr_t* GetNameSchemaAttr();

struct nvtxEvent {
    uint64_t time_start;
    uint64_t time_stop;
    const char* name;
    const char* domain;
    uint32_t process_id;
    uint32_t thread_id;
    uint32_t color;
};
const nvtxPayloadSchemaAttr_t* GetNvtxSchemaAttr();

//table ApiActivity {
//  kind:ApiKind = Runtime;
//  cbid:uint32;
//  start:uint64;
//  end:uint64;
//  process_id:uint32;
//  thread_id:uint32;
//  correlation_id:uint32;
//  return_value:uint32 = 0;
struct cuptiApiEvent {
    uint64_t time_start;
    uint64_t time_stop;
    uint32_t kind;
    uint32_t cbid;
    uint32_t process_id;
    uint32_t thread_id;
    uint32_t correlation_id;
    uint32_t return_value;
};
const nvtxPayloadSchemaAttr_t* GetCuptiApiSchemaAttr();

//table DeviceActivity {
//  global_memory_bandwidth:uint64;
//  global_memory_size:uint64;
//  constant_memory_size:uint32;
//  l2_cache_size:uint32;
//  num_threads_per_warp:uint32;
//  core_clock_rate:uint32;
//  num_memcpy_engines:uint32;
//  num_multiprocessors:uint32;
//  max_ipc:uint32;
//  max_warps_per_multiprocessor:uint32;
//  max_blocks_per_multiprocessor:uint32;
//  max_shared_memory_per_multiprocessor:uint32;
//  max_registers_per_multiprocessor:uint32;
//  max_registers_per_block:uint32;
//  max_shared_memory_per_block:uint32;
//  max_threads_per_block:uint32;
//  max_block_dim_x:uint32;
//  max_block_dim_y:uint32;
//  max_block_dim_z:uint32;
//  max_grid_dim_x:uint32;
//  max_grid_dim_y:uint32;
//  max_grid_dim_z:uint32;
//  compute_capability_major:uint32;
//  compute_capability_minor:uint32;
//  id:uint32;
//  ecc_enabled:uint32;
//  name:string;
//}
struct cuptiDevice {
    uint64_t global_memory_bandwidth;
    uint64_t global_memory_size;
    uint32_t constant_memory_size;
    uint32_t l2_cache_size;
    uint32_t num_threads_per_warp;
    uint32_t core_clock_rate;
    uint32_t num_memcpy_engines;
    uint32_t num_multiprocessors;
    uint32_t max_ipc;
    uint32_t max_warps_per_multiprocessor;
    uint32_t max_blocks_per_multiprocessor;
    uint32_t max_shared_memory_per_multiprocessor;
    uint32_t max_registers_per_multiprocessor;
    uint32_t max_registers_per_block;
    uint32_t max_shared_memory_per_block;
    uint32_t max_threads_per_block;
    uint32_t max_block_dim_x;
    uint32_t max_block_dim_y;
    uint32_t max_block_dim_z;
    uint32_t max_grid_dim_x;
    uint32_t max_grid_dim_y;
    uint32_t max_grid_dim_z;
    uint32_t compute_capability_major;
    uint32_t compute_capability_minor;
    uint32_t id;
    uint32_t ecc_enabled;
    const char* name;
};
const nvtxPayloadSchemaAttr_t* GetCuptiDeviceSchemaAttr();

// table KernelActivity {
//   requested:uint8;
//   executed:uint8;
//   shared_memory_config:uint8;
//   registers_per_thread:uint16;
//   partitioned_global_cache_requested:PartitionedGlobalCacheConfig;
//   partitioned_global_cache_executed:PartitionedGlobalCacheConfig;
//   start:uint64;
//   end:uint64;
//   completed:uint64 = 0;
//   device_id:uint32;
//   context_id:uint32;
//   stream_id:uint32;
//   process_id:uint32;
//   grid_x:int32;
//   grid_y:int32;
//   grid_z:int32;
//   block_x:int32;
//   block_y:int32;
//   block_z:int32;
//   static_shared_memory:int32;
//   dynamic_shared_memory:int32;
//   local_memory_per_thread:uint32;
//   local_memory_total:uint32;
//   correlation_id:uint32;
//   grid_id:int64;
//   name:string;
//   queued:uint64 = 0;
//   submitted:uint64 = 0;
//   launch_type:LaunchType = Regular;
//   is_shared_memory_carveout_requested:uint8;
//   shared_memory_carveout_requested:uint8;
//   shared_memory_executed:uint32;
//   graph_node_id:uint64 = 0;
//   shmem_limit_config:ShmemLimitConfig = Default;
//   graph_id:uint32 = 0;
//   //access_policy_window:???;
//   channel_id:uint32;
//   channel_type:ChannelType;
//   cluster_x:uint32;
//   cluster_y:uint32;
//   cluster_z:uint32;
//   cluster_scheduling_policy:uint32;
//   local_memory_total_v2:uint64;
// }
struct cuptiKernelEvent {
    uint64_t time_start;
    uint64_t time_stop;
    uint64_t completed;
    uint64_t grid_id;
    uint64_t queued;
    uint64_t submitted;
    uint64_t graph_node_id;
    uint64_t local_memory_total_v2;
    const char * name;
    uint32_t device_id;
    uint32_t context_id;
    uint32_t stream_id;
    //TODO new field
    //uint32_t process_id;  //NEW
    uint32_t grid_x;
    uint32_t grid_y;
    uint32_t grid_z;
    uint32_t block_x;
    uint32_t block_y;
    uint32_t block_z;
    uint32_t static_shared_memory;
    uint32_t dynamic_shared_memory;
    uint32_t local_memory_per_thread;
    uint32_t local_memory_total;
    uint32_t correlation_id;
    uint32_t shared_memory_executed;
    uint32_t graph_id;
    uint32_t channel_id;
    uint32_t cluster_x;
    uint32_t cluster_y;
    uint32_t cluster_z;
    uint32_t cluster_scheduling_policy;
    uint16_t registers_per_thread;
    uint8_t requested;
    uint8_t executed;
    uint8_t shared_memory_config;
    uint8_t partitioned_global_cache_requested;
    uint8_t partitioned_global_cache_executed;
    uint8_t launch_type;
    uint8_t is_shared_memory_carveout_requested;
    uint8_t shared_memory_carveout_requested;
    uint8_t shmem_limit_config;
    uint8_t channel_type;
};
const nvtxPayloadSchemaAttr_t* GetCuptiKernelSchemaAttr();

//table MemcpyActivity {
//  copy_kind:MemcpyKind;
//  src_kind:MemoryKind;
//  dst_kind:MemoryKind;
//  flags:MemcpyFlags;
//  bytes:uint64;
//  start:uint64;
//  end:uint64;
//  device_id:uint32;
//  context_id:uint32;
//  stream_id:uint32;
//  correlation_id:uint32;
//  runtime_correlation_id:uint32;
//  graph_node_id:uint64 = 0;
//  graph_id:uint32 = 0;
//  channel_id:uint32;
//  channel_type:ChannelType;
struct cuptiMemcpyEvent {
    uint64_t time_start;
    uint64_t time_stop;
    uint64_t bytes;
    uint64_t graph_node_id;
    uint32_t device_id;
    uint32_t context_id;
    uint32_t stream_id;
    //TODO new field
    //uint32_t process_id;  //NEW
    uint32_t correlation_id;
    uint32_t runtime_correlation_id;
    uint32_t graph_id;
    uint32_t channel_id;
    uint8_t channelType;
    uint8_t copy_kind;
    uint8_t src_kind;
    uint8_t dst_kind;
};
const nvtxPayloadSchemaAttr_t* GetCuptiMemcpySchemaAttr();

//table MemsetActivity {
//  value:uint32;
//  bytes:uint64;
//  start:uint64;
//  end:uint64;
//  device_id:uint32;
//  context_id:uint32;
//  stream_id:uint32;
//  correlation_id:uint32;
//  flags:MemsetFlags;
//  memory_kind:MemoryKind;
//  graph_node_id:uint64 = 0;
//  graph_id:uint32 = 0;
//  channel_id:uint32;
//  channel_type:ChannelType;
//}
struct cuptiMemsetEvent {
    uint64_t time_start;
    uint64_t time_stop;
    uint64_t bytes;
    uint64_t graph_node_id;    
    uint32_t device_id;
    uint32_t context_id;
    uint32_t stream_id;
    //TODO new field
    //uint32_t process_id;  //NEW
    uint32_t correlation_id;
    uint32_t graph_id;
    uint32_t channel_id;
    uint32_t value;
    uint8_t channelType;
    uint8_t mem_kind;
    uint8_t flags;
};
const nvtxPayloadSchemaAttr_t* GetCuptiMemsetSchemaAttr();

//table OverheadActivity {
//  overhead_kind:OverheadKind;
//  object_id:ActivityObjectId;
//  start:uint64;
//  end:uint64;
//}
struct cuptiOverheadEvent {
    uint64_t time_start;
    uint64_t time_stop;
    uint32_t process_id;
    uint32_t thread_id;
    uint8_t overhead_kind;
};
const nvtxPayloadSchemaAttr_t* GetCuptiOverheadSchemaAttr();

}
