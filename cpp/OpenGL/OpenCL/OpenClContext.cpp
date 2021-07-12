#include "OpenClContext.h"

OpenClContextException:: OpenClContextException(const std::string& m)
  : msg(m)
{}

OpenClContextException::OpenClContextException(const std::string& m, cl_int error)
  : msg(m + " (" + getErrorString(error) + ")")
{}

OpenClContextException::~OpenClContextException() throw()
{}

const char* OpenClContextException::what() const throw() {
  return msg.c_str();
}

std::string OpenClContextException::getErrorString(cl_int error) {
  switch(error){
      // run-time and JIT compiler errors
    case CL_SUCCESS:
      return "CL_SUCCESS";
    case CL_DEVICE_NOT_FOUND:
      return "CL_DEVICE_NOT_FOUND";
    case CL_DEVICE_NOT_AVAILABLE:
      return "CL_DEVICE_NOT_AVAILABLE";
    case CL_COMPILER_NOT_AVAILABLE:
      return "CL_COMPILER_NOT_AVAILABLE";
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:
      return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case CL_OUT_OF_RESOURCES:
      return "CL_OUT_OF_RESOURCES";
    case CL_OUT_OF_HOST_MEMORY:
      return "CL_OUT_OF_HOST_MEMORY";
    case CL_PROFILING_INFO_NOT_AVAILABLE:
      return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case CL_MEM_COPY_OVERLAP:
      return "CL_MEM_COPY_OVERLAP";
    case CL_IMAGE_FORMAT_MISMATCH:
      return "CL_IMAGE_FORMAT_MISMATCH";
    case CL_IMAGE_FORMAT_NOT_SUPPORTED:
      return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case CL_BUILD_PROGRAM_FAILURE:
      return "CL_BUILD_PROGRAM_FAILURE";
    case CL_MAP_FAILURE:
      return "CL_MAP_FAILURE";
    case CL_MISALIGNED_SUB_BUFFER_OFFSET:
      return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
      return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case CL_COMPILE_PROGRAM_FAILURE:
      return "CL_COMPILE_PROGRAM_FAILURE";
    case CL_LINKER_NOT_AVAILABLE:
      return "CL_LINKER_NOT_AVAILABLE";
    case CL_LINK_PROGRAM_FAILURE:
      return "CL_LINK_PROGRAM_FAILURE";
    case CL_DEVICE_PARTITION_FAILED:
      return "CL_DEVICE_PARTITION_FAILED";
    case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:
      return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

      // compile-time errors
    case CL_INVALID_VALUE:
      return "CL_INVALID_VALUE";
    case CL_INVALID_DEVICE_TYPE:
      return "CL_INVALID_DEVICE_TYPE";
    case CL_INVALID_PLATFORM:
      return "CL_INVALID_PLATFORM";
    case CL_INVALID_DEVICE:
      return "CL_INVALID_DEVICE";
    case CL_INVALID_CONTEXT:
      return "CL_INVALID_CONTEXT";
    case CL_INVALID_QUEUE_PROPERTIES:
      return "CL_INVALID_QUEUE_PROPERTIES";
    case CL_INVALID_COMMAND_QUEUE:
      return "CL_INVALID_COMMAND_QUEUE";
    case CL_INVALID_HOST_PTR:
      return "CL_INVALID_HOST_PTR";
    case CL_INVALID_MEM_OBJECT:
      return "CL_INVALID_MEM_OBJECT";
    case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:
      return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case CL_INVALID_IMAGE_SIZE:
      return "CL_INVALID_IMAGE_SIZE";
    case CL_INVALID_SAMPLER:
      return "CL_INVALID_SAMPLER";
    case CL_INVALID_BINARY:
      return "CL_INVALID_BINARY";
    case CL_INVALID_BUILD_OPTIONS:
      return "CL_INVALID_BUILD_OPTIONS";
    case CL_INVALID_PROGRAM:
      return "CL_INVALID_PROGRAM";
    case CL_INVALID_PROGRAM_EXECUTABLE:
      return "CL_INVALID_PROGRAM_EXECUTABLE";
    case CL_INVALID_KERNEL_NAME:
      return "CL_INVALID_KERNEL_NAME";
    case CL_INVALID_KERNEL_DEFINITION:
      return "CL_INVALID_KERNEL_DEFINITION";
    case CL_INVALID_KERNEL:
      return "CL_INVALID_KERNEL";
    case CL_INVALID_ARG_INDEX:
      return "CL_INVALID_ARG_INDEX";
    case CL_INVALID_ARG_VALUE:
      return "CL_INVALID_ARG_VALUE";
    case CL_INVALID_ARG_SIZE:
      return "CL_INVALID_ARG_SIZE";
    case CL_INVALID_KERNEL_ARGS:
      return "CL_INVALID_KERNEL_ARGS";
    case CL_INVALID_WORK_DIMENSION:
      return "CL_INVALID_WORK_DIMENSION";
    case CL_INVALID_WORK_GROUP_SIZE:
      return "CL_INVALID_WORK_GROUP_SIZE";
    case CL_INVALID_WORK_ITEM_SIZE:
      return "CL_INVALID_WORK_ITEM_SIZE";
    case CL_INVALID_GLOBAL_OFFSET:
      return "CL_INVALID_GLOBAL_OFFSET";
    case CL_INVALID_EVENT_WAIT_LIST:
      return "CL_INVALID_EVENT_WAIT_LIST";
    case CL_INVALID_EVENT:
      return "CL_INVALID_EVENT";
    case CL_INVALID_OPERATION:
      return "CL_INVALID_OPERATION";
    case CL_INVALID_GL_OBJECT:
      return "CL_INVALID_GL_OBJECT";
    case CL_INVALID_BUFFER_SIZE:
      return "CL_INVALID_BUFFER_SIZE";
    case CL_INVALID_MIP_LEVEL:
      return "CL_INVALID_MIP_LEVEL";
    case CL_INVALID_GLOBAL_WORK_SIZE:
      return "CL_INVALID_GLOBAL_WORK_SIZE";
    case CL_INVALID_PROPERTY:
      return "CL_INVALID_PROPERTY";
    case CL_INVALID_IMAGE_DESCRIPTOR:
      return "CL_INVALID_IMAGE_DESCRIPTOR";
    case CL_INVALID_COMPILER_OPTIONS:
      return "CL_INVALID_COMPILER_OPTIONS";
    case CL_INVALID_LINKER_OPTIONS:
      return "CL_INVALID_LINKER_OPTIONS";
    case CL_INVALID_DEVICE_PARTITION_COUNT:
      return "CL_INVALID_DEVICE_PARTITION_COUNT";

      // extension errors
    case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    default: return "Unknown OpenCL error";
  }
}

PlatformInfo::PlatformInfo(cl_platform_id platformID)  :
  platformID(platformID)
{
  size_t valueSize{0};
  DynBuffer<char> buffer{2048};
  
  clGetPlatformInfo(platformID, CL_PLATFORM_NAME, 0, NULL, &valueSize);
  buffer.ensureSize(valueSize);
  clGetPlatformInfo(platformID, CL_PLATFORM_NAME, buffer.currentSize, buffer.data, NULL);
  name = buffer.data;

  clGetPlatformInfo(platformID, CL_PLATFORM_VENDOR, 0, NULL, &valueSize);
  buffer.ensureSize(valueSize);
  clGetPlatformInfo(platformID, CL_PLATFORM_VENDOR, buffer.currentSize, buffer.data, NULL);
  vendor = buffer.data;

  clGetPlatformInfo(platformID, CL_PLATFORM_VERSION, 0, NULL, &valueSize);
  buffer.ensureSize(valueSize);
  clGetPlatformInfo(platformID, CL_PLATFORM_VERSION, buffer.currentSize, buffer.data, NULL);
  version = buffer.data;
  
  cl_uint count;
  clGetDeviceIDs(platformID, CL_DEVICE_TYPE_ALL, 0, NULL, &count);
  DynBuffer<cl_device_id> deviceBuffer{count};
  clGetDeviceIDs(platformID, CL_DEVICE_TYPE_ALL, cl_uint(deviceBuffer.currentSize), deviceBuffer.data, NULL);

  for (cl_uint i = 0;i<count;++i) {
    devices.push_back(DeviceInfo(deviceBuffer.data[i]));
  }
}

std::string PlatformInfo::toString() const {
  std::stringstream ss;
  ss << "Name:" << name << " Vendor:" << vendor  << " Version:" << version << "\n";
  for (const DeviceInfo& dev : devices) {
    ss << "\t" << dev.toString() << "\n";
  }
  return ss.str();
}

DeviceInfo::DeviceInfo(cl_device_id deviceID) :
  deviceID(deviceID)
{
  size_t valueSize{0};
  DynBuffer<char> buffer{2048};

  clGetDeviceInfo(deviceID, CL_DEVICE_NAME, 0, NULL, &valueSize);
  buffer.ensureSize(valueSize);
  clGetDeviceInfo(deviceID, CL_DEVICE_NAME, buffer.currentSize, buffer.data, NULL);
  name = buffer.data;

  clGetDeviceInfo(deviceID, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
    
  clGetDeviceInfo(deviceID, CL_DEVICE_VERSION, 0, NULL, &valueSize);
  buffer.ensureSize(valueSize);
  clGetDeviceInfo(deviceID, CL_DEVICE_VERSION, buffer.currentSize, buffer.data, NULL);
  deviceVersion = buffer.data;

  clGetDeviceInfo(deviceID, CL_DRIVER_VERSION, 0, NULL, &valueSize);
  buffer.ensureSize(valueSize);
  clGetDeviceInfo(deviceID, CL_DRIVER_VERSION, buffer.currentSize, buffer.data, NULL);
  driverVersion = buffer.data;

  clGetDeviceInfo(deviceID, CL_DEVICE_OPENCL_C_VERSION, 0, NULL, &valueSize);
  buffer.ensureSize(valueSize);
  clGetDeviceInfo(deviceID, CL_DEVICE_OPENCL_C_VERSION, buffer.currentSize, buffer.data, NULL);
  openCLCVersion = buffer.data;

  clGetDeviceInfo(deviceID, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(maxComputeUnits), &maxComputeUnits, NULL);
}

std::string DeviceInfo::toString() const {
  std::stringstream ss;
  ss << "Name:" << name
     << "\tDevice Version: " << deviceVersion
     << "\tDriver Version: " << driverVersion
     << "\tOpenCL C Version: " << openCLCVersion
     << "\tMax Compute Units: " << maxComputeUnits
     << "\tType: ";
  
  switch (type) {
    case CL_DEVICE_TYPE_CPU:
      ss << "CPU";
      break;
    case CL_DEVICE_TYPE_GPU:
      ss << "GPU";
      break;
    case CL_DEVICE_TYPE_ACCELERATOR:
      ss << "Accelerator";
      break;
    case CL_DEVICE_TYPE_DEFAULT:
      ss << "Default";
      break;
  }
  
  return ss.str();
}
