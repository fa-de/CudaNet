#include "StdAfx.h"
#include "Function.h"
#include "Stream.h"

using namespace CudaNet;

Function::Function(CUfunction function):function(function)
{
	blockWidth = 1;
	blockHeight = 1;
	blockDepth = 1;
	//TODO Save as properties
	int sharedSize, localSize, constSize, numRegs;
	pin_ptr<int> pShared = &sharedSize;
	pin_ptr<int> pLocal = &localSize;
	pin_ptr<int> pConst = &constSize;
	pin_ptr<int> pRegs = &numRegs;
	cuFuncGetAttribute(pShared, CU_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES, function);
	cuFuncGetAttribute(pLocal, CU_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES, function);
	cuFuncGetAttribute(pConst, CU_FUNC_ATTRIBUTE_CONST_SIZE_BYTES, function);
	cuFuncGetAttribute(pRegs, CU_FUNC_ATTRIBUTE_NUM_REGS, function);
}

void Function::SetBlockShape(array<unsigned int>^ blockSize)
{
	blockWidth = blockSize[0];
	blockHeight = blockSize[1];
	blockDepth = blockSize[2];
}

void Function::Launch(unsigned int width, unsigned int height, unsigned int depth, array<CudaParameter>^ parameters)
{
	const unsigned int sharedMemory = 0;
	pin_ptr<void> data = &parameters[0];
	void* debug = data;
	unsigned int size = parameters->Length * 4;

	void *extra[] = {
		CU_LAUNCH_PARAM_BUFFER_POINTER, data,
        CU_LAUNCH_PARAM_BUFFER_SIZE, &size,
        CU_LAUNCH_PARAM_END
	};

	HANDLE(cuLaunchKernel(function, width, height, depth, blockWidth, blockHeight, blockDepth, sharedMemory, NULL, NULL, extra));
}

void Function::Launch(unsigned int width, unsigned int height, unsigned int depth, array<CudaParameter>^ parameters, Stream^ stream)
{
	const unsigned int sharedMemory = 0;
	pin_ptr<void> data = &parameters[0];
	void* debug = data;
	unsigned int size = parameters->Length * 4;

	void *extra[] = {
		CU_LAUNCH_PARAM_BUFFER_POINTER, data,
        CU_LAUNCH_PARAM_BUFFER_SIZE, &size,
        CU_LAUNCH_PARAM_END
	};

	HANDLE(cuLaunchKernel(function, width, height, depth, blockWidth, blockHeight, blockDepth, sharedMemory, stream->stream, NULL, extra));
}