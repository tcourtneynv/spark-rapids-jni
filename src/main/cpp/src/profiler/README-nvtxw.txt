1. NvtxwEvents.h, NvtxwEvents.cpp are copied from Nsight Systems source code. They need to be kept in sync between this project and Nsight Systems.

2. Need to have the host directory a current build of Nsight Systems in LD_LIBRARY_PATH:
   For example:
   > export LD_LIBRARY_PATH=/opt/nvidia/nsight-systems/2024.6.0/host-linux-x64

3. Run like this:
   > ./target/cmake-build/spark_rapids_profile_converter  -w -o file3021460.nsys-rep rapids-profile-3021460@jlowe-lcedt-driver.bin

4. Load into nsight systems UI: nsys-ui file3021460.nsys-rep

5. I identified one improvement to the FlatBuffer binary format. I added a "TODO" to the profiler.fbs file and spark_rapids_profile_converter.cpp. 
   This field should be set to the PID of the process that is using the GPU and generating the CUPTI activity callbacks. It is not a field that 
   CUPTI populates via the callback parameters.

   In the current code, we implemented a work-around within the NVTXW backend code. Because we know this application will send API activity data
   first, we save the PID from the CUDA API activity events, and use add it to the event data for the GPU kernel, memcpy and memset events. Once the PID
   is added to the binary file, we can remove this work-around and use it directly.