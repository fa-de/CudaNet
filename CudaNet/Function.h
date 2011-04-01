#pragma once
#include "CudaParameter.h"

namespace CudaNet
{
ref class Stream;
public ref class Function
{
private:
	CUfunction function;
	unsigned __int32 blockWidth, blockHeight, blockDepth;
internal:
	Function(CUfunction function);
public:
	void SetBlockShape(array<unsigned int>^ blockSize);
	void Launch(unsigned int width, unsigned int height, unsigned int depth, array<CudaParameter>^ parameters);
	void Launch(unsigned int width, unsigned int height, unsigned int depth, array<CudaParameter>^ parameters, Stream^ stream);
};
}
