#include "Stdafx.h"
#include "HostPointer.h"

using namespace CudaNet;

HostPointer::HostPointer(void* ptr, size_t byteSize, Context^ parentContext) : ptr(ptr), size(byteSize), ContextChild(parentContext)
{
}

HostPointer::!HostPointer()
{
	HANDLE(cuMemFreeHost(ptr));
}