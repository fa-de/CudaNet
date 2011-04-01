#pragma once
#include "DevicePointer.h"
namespace CudaNet
{
public value struct CudaParameter
{
typedef size_t ptrType;
private:
	ptrType data;	//HACK? Assume every parameter is 32 bits in size
	unsigned int size;
public:
	CudaParameter(float v):data(*((ptrType*)&v)),size(sizeof(float)) {}
	CudaParameter(int v):data((ptrType)v),size(sizeof(int)) {}
	CudaParameter(DevicePointer^ v):data((ptrType)(v->ptr)),size(sizeof(void*)) {}

	static operator CudaParameter (int v)  { return CudaParameter(v); }
	static operator CudaParameter (float v)  { return CudaParameter(v); }
	static operator CudaParameter (DevicePointer^ v) { return CudaParameter(v); }
};
}