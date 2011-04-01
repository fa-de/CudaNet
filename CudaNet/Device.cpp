#include "stdafx.h"
#include "Device.h"
#include "Context.h"

using namespace CudaNet;

Device::Device(int ordinal)
{
	pin_ptr<CUdevice> pdev = &device;
	HANDLE(cuDeviceGet(pdev, ordinal));

	pin_ptr<unsigned int> pTotalMemory = &_totalMemory;
	HANDLE(cuDeviceTotalMem(pTotalMemory, device));

	_computeCapability = gcnew ComputeCapability(device);
	_deviceProperties = gcnew DeviceProperties(device);
}

Context^ Device::CreateContext()
{
	return gcnew Context(this);
}