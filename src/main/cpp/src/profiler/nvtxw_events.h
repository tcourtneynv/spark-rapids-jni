#pragma once

#include "nvtxw3.h"
#include "NvtxwEvents.h"


extern int initialize_nvtxw(std::ifstream& in, const std::string& outName, 
  void *& nvtxwModuleHandle,
  nvtxwInterfaceCore_t *&nvtxwInterface,
  nvtxwSessionHandle_t &session,
  nvtxwStreamHandle_t &stream);
