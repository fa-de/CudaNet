// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifdef _DEBUG
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#endif

#include <cuda.h>

#include "CudaError.h"

#define HANDLE(v) {cudaError_enum r=v; if(r!=CUDA_SUCCESS) throw gcnew CudaNet::CudaError(r);}

inline void log(const char* text)
{
#ifdef _DEBUG
	//std::cout << text << "\n";
	OutputDebugStringA(text);
	OutputDebugStringA("\n");
#endif
}


