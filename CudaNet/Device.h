#pragma once
#include "ComputeCapability.h"
#include "DeviceProperties.h"

namespace CudaNet
{
ref class Context;
public ref class Device
{
private:
	unsigned int _totalMemory;
	ComputeCapability^ _computeCapability;
	DeviceProperties^ _deviceProperties;

internal:
	CUdevice device;
	Device(int ordinal);

public:
	Context^ CreateContext();

	//Properties:

	property unsigned int TotalMemory { unsigned int get() {return _totalMemory;} }
	property ComputeCapability^ Capability { ComputeCapability^ get() {return _computeCapability;} }
	property DeviceProperties^ Properties { DeviceProperties^ get() {return _deviceProperties;} }

	property System::String^ Name
	{
		System::String^ get ()
		{
			char name[32];
			cuDeviceGetName(name, 32, device);
			return gcnew System::String(name);
		}
	}

	virtual System::String^ ToString() override
	{
		return gcnew System::String("CUDA Device: ") + Name;
	}
};
}