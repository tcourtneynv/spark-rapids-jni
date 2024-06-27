
#include <string>
#include <fstream>
#include <iostream>

#include <cerrno>
#include <cxxabi.h>
#include <charconv>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#include "nvtxw_events.h"

/// outName: basename of output nsys-rep, without .nsys-rep extension
int initialize_nvtxw(std::ifstream& in, const std::string& outName, 
  void *& nvtxwModuleHandle,
  nvtxwInterfaceCore_t *&nvtxwInterface,
  nvtxwSessionHandle_t &session,
  nvtxwStreamHandle_t &stream) {
  nvtxwResultCode_t result = NVTXW3_RESULT_SUCCESS;
  int errorCode = 0;
  static const char soName[] = "libNvtxwBackend.so";
  nvtxwGetInterface_t getInterfaceFunc = nullptr;
  result = nvtxwInitialize(
      NVTXW3_INIT_MODE_LIBRARY_FILENAME,
      soName,
      &getInterfaceFunc,
      &nvtxwModuleHandle);
  if (result != NVTXW3_RESULT_SUCCESS)
  {
      fprintf(stderr, "nvtxwInitialize failed with code %d\n", (int)result);
      if (result == NVTXW3_RESULT_LIBRARY_NOT_FOUND)
          fprintf(stderr, "Failed to find %s\n", soName);
      return 1;
  }
  if (!getInterfaceFunc)
  {
      fprintf(stderr, "nvtxwInitialize returned null nvtxwGetInterface_t!\n");
      return 1;
  }

  const void* interfaceVoid;
  result = getInterfaceFunc(
      NVTXW3_INTERFACE_ID_CORE_V1,
      &interfaceVoid);
  if (result != NVTXW3_RESULT_SUCCESS)
  {
      fprintf(stderr, "getInterfaceFunc failed with code %d\n", (int)result);
      return 1;
  }
  if (!interfaceVoid)
  {
      fprintf(stderr, "getInterfaceFunc returned null nvtxwInterface pointer!\n");
      return 1;
  }
  nvtxwInterface = reinterpret_cast<nvtxwInterfaceCore_t*>((void*)interfaceVoid);

  // session begin
  char* sessionConfig = nullptr;
  nvtxwSessionAttributes_t sessionAttr = {
      sizeof(nvtxwSessionAttributes_t),
      outName.c_str(),
      sessionConfig
  };
  result = nvtxwInterface->SessionBegin(&session, &sessionAttr);
  free(sessionConfig);
  if (result != NVTXW3_RESULT_SUCCESS)
  {
      fprintf(stderr, "SessionBegin failed with code %d\n", (int)result);
      return 1;
  }
  if (!session.opaque)
  {
      fprintf(stderr, "SessionBegin returned null session handle!\n");
      return 1;
  }

  // stream open
  std::string streamName("Stream1");
  std::string domainName("SparkRAPIDS");
  nvtxwStreamAttributes_t streamAttr = {
      sizeof(nvtxwStreamAttributes_t),
      streamName.c_str(),
      domainName.c_str(),
      "",
      NVTXW3_STREAM_ORDER_INTERLEAVING_NONE,
      NVTXW3_STREAM_ORDERING_TYPE_UNKNOWN,
      NVTXW3_STREAM_ORDERING_SKID_NONE,
      0
  };
  result = nvtxwInterface->StreamOpen(&stream, session, &streamAttr);
  if (result != NVTXW3_RESULT_SUCCESS)
  {
      fprintf(stderr, "StreamOpen failed with code %d\n", (int)result);
      errorCode |= 1;
  }
  if (!stream.opaque)
  {
      fprintf(stderr, "StreamOpen returned null stream handle!\n");
      errorCode |= 1;
  }
  else
  {
      // schema register
      result = nvtxwInterface->SchemaRegister(stream, NvidiaNvtxw::GetNameSchemaAttr());
      if (result != NVTXW3_RESULT_SUCCESS)
      {
          fprintf(stderr, "SchemaRegister failed for 'nameSchema' with code %d\n", (int)result);
          errorCode |= 2;
      }
      result = nvtxwInterface->SchemaRegister(stream, NvidiaNvtxw::GetNvtxSchemaAttr());
      if (result != NVTXW3_RESULT_SUCCESS)
      {
          fprintf(stderr, "SchemaRegister failed with 'nvtxSchema' with code %d\n", (int)result);
          errorCode |= 2;
      }
      result = nvtxwInterface->SchemaRegister(stream, NvidiaNvtxw::GetCuptiApiSchemaAttr());
      if (result != NVTXW3_RESULT_SUCCESS)
      {
          fprintf(stderr, "SchemaRegister failed with 'cuptiApiSchema' with code %d\n", (int)result);
          errorCode |= 2;
      }
      result = nvtxwInterface->SchemaRegister(stream, NvidiaNvtxw::GetCuptiDeviceSchemaAttr());
      if (result != NVTXW3_RESULT_SUCCESS)
      {
          fprintf(stderr, "SchemaRegister failed with 'cuptiDeviceSchema' with code %d\n", (int)result);
          errorCode |= 2;
      }        
      result = nvtxwInterface->SchemaRegister(stream, NvidiaNvtxw::GetCuptiKernelSchemaAttr());
      if (result != NVTXW3_RESULT_SUCCESS)
      {
          fprintf(stderr, "SchemaRegister failed with 'cuptiKernelSchema' with code %d\n", (int)result);
          errorCode |= 2;
      }        
      result = nvtxwInterface->SchemaRegister(stream, NvidiaNvtxw::GetCuptiMemcpySchemaAttr());
      if (result != NVTXW3_RESULT_SUCCESS)
      {
          fprintf(stderr, "SchemaRegister failed with 'cuptiMemcpySchema' with code %d\n", (int)result);
          errorCode |= 2;
      }
      result = nvtxwInterface->SchemaRegister(stream, NvidiaNvtxw::GetCuptiMemsetSchemaAttr());
      if (result != NVTXW3_RESULT_SUCCESS)
      {
          fprintf(stderr, "SchemaRegister failed with 'cuptiMemsetSchema' with code %d\n", (int)result);
          errorCode |= 2;
      }
      result = nvtxwInterface->SchemaRegister(stream, NvidiaNvtxw::GetCuptiOverheadSchemaAttr());
      if (result != NVTXW3_RESULT_SUCCESS)
      {
          fprintf(stderr, "SchemaRegister failed with 'cuptiOverheadSchema' with code %d\n", (int)result);
          errorCode |= 2;
      }        
  }
  return errorCode;
}
