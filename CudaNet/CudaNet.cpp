#include "stdafx.h"

#include "CudaNet.h"

using namespace CudaNet;

Cuda::Cuda()
{
	log("Cuda::Cuda()");
	if(refCount++ == 0)
	{
		Init();
	}
}

Cuda::~Cuda()
{
	log("Cuda::~Cuda()");
	if(--refCount == 0)
	{
		Cleanup();
	}
}

void Cuda::Init()
{
	cuInit(0);
	log("Cuda::Init()");

	int deviceCount;
	{
		pin_ptr<int> pDeviceCount = &deviceCount;
		HANDLE(cuDeviceGetCount(pDeviceCount));
	}

	for(int i=0; i<deviceCount; ++i)
	{
		Device^ dev = gcnew Device(i);
		_Devices.Add(dev);
	}
}

int Cuda::DriverVersion::get()
{
	int version;
	cuDriverGetVersion(&version);
	return version;
}

void Cuda::Cleanup()
{
	log("Cuda::Cleanup()");
}