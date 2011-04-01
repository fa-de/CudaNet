#pragma once

namespace CudaNet
{

inline const char* GetErrorName(cudaError_enum error)
{
	switch(error)
	{
		case CUDA_SUCCESS: return "CUDA_SUCCESS";
		case CUDA_ERROR_INVALID_VALUE: return "CUDA_ERROR_INVALID_VALUE";
		case CUDA_ERROR_OUT_OF_MEMORY: return "CUDA_ERROR_OUT_OF_MEMORY";
		case CUDA_ERROR_NOT_INITIALIZED: return "NOT_INITIALIZED";
		case CUDA_ERROR_DEINITIALIZED: return "NOT_INITIALIZED";
		case CUDA_ERROR_NO_DEVICE: return "NO_DEVICE";
		case CUDA_ERROR_INVALID_DEVICE:	return "INVALID_DEVICE";
		case CUDA_ERROR_INVALID_IMAGE: return "INVALID_IMAGE";
		case CUDA_ERROR_INVALID_CONTEXT: return "INVALID_CONTEXT";
		case CUDA_ERROR_CONTEXT_ALREADY_CURRENT: return "CONTEXT_ALREADY_CURRENT";
		case CUDA_ERROR_MAP_FAILED: return "MAP_FAILED";
		case CUDA_ERROR_UNMAP_FAILED: return "UNMAP_FAILED";
		case CUDA_ERROR_ARRAY_IS_MAPPED: return "ARRAY_IS_MAPPED";
		case CUDA_ERROR_ALREADY_MAPPED: return "ALREADY_MAPPED";
		case CUDA_ERROR_NO_BINARY_FOR_GPU: return "NO_BINARY_FOR_GPU";
		case CUDA_ERROR_ALREADY_ACQUIRED: return "ALREADY_ACQUIRED";
		case CUDA_ERROR_NOT_MAPPED: return "NOT_MAPPED";
		case CUDA_ERROR_INVALID_SOURCE: return "INVALID_SOURCE";
		case CUDA_ERROR_FILE_NOT_FOUND: return "FILE_NOT_FOUND";
		case CUDA_ERROR_INVALID_HANDLE: return "INVALID_HANDLE";
		case CUDA_ERROR_NOT_FOUND: return "NOT_FOUND";
		case CUDA_ERROR_NOT_READY: return "NOT_READY";
		case CUDA_ERROR_LAUNCH_FAILED: return "LAUNCH_FAILED";
		case CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES: return "LAUNCH_OUT_OF_RESOURCES";
		case CUDA_ERROR_LAUNCH_TIMEOUT: return "LAUNCH_TIMEOUT";
		case CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING: return "LAUNCH_INCOMPATIBLE_TEXTURING"; 
		case CUDA_ERROR_UNKNOWN:
		default: return "UNKNOWN";
	}
};

public ref class CudaError : public System::Exception
{
private:
	cudaError_enum reason;
public:
	CudaError(System::String^ reason) : System::Exception(reason), reason(CUDA_SUCCESS) {}
	CudaError(cudaError_enum reason) : System::Exception(gcnew System::String(GetErrorName(reason))), reason(reason){}
};
}