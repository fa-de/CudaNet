#include "Stdafx.h"
#include "DevicePointer.h"

using namespace CudaNet;

DevicePointer::DevicePointer(CUdeviceptr ptr, unsigned int size, bool customAllocated, Context^ parentContext) : ptr(ptr), size(size), customAllocated(customAllocated), ContextChild(parentContext)
{
}

DevicePointer::!DevicePointer()
{
	if(customAllocated)	//Don't attempt to free constants etc.
	{
		HANDLE(cuMemFree(ptr));
		ptr = NULL;
	}
}