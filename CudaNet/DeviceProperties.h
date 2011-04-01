#include "CudaExtent.h"
namespace CudaNet
{
public ref struct DeviceProperties
{
private:
	CUdevprop* props;
internal:
	DeviceProperties(CUdevice device)
	{
		props = new CUdevprop;
		pin_ptr<CUdevprop> pProps = props;
		HANDLE(cuDeviceGetProperties(pProps, device));
	}
	~DeviceProperties() { this->!DeviceProperties(); }
	!DeviceProperties()
	{
		delete props;
	}
public:
	/*
	Specifies the clock rate in kHz
	*/
	property int ClockRate { int get(){ return props->clockRate; } }
	property int MaxThreadsPerBlock { int get(){ return props->maxThreadsPerBlock; } }
	property CudaExtent^ MaxThreadsDim { CudaExtent^ get(){ CudaExtent^ ex = gcnew CudaExtent(props->maxThreadsDim); return ex; } }
	property CudaExtent^ MaxGridSize { CudaExtent^ get(){ return gcnew CudaExtent(props->maxGridSize); } }
	property int SharedMemPerBlock { int get(){ return props->sharedMemPerBlock; } }
	property int TotalConstantMemory { int get(){ return props->totalConstantMemory; } }
	property int SIMDWidth { int get(){ return props->SIMDWidth; } }
	property int MemPitch { int get(){ return props->memPitch; } }
	property int RegsPerBlock { int get(){ return props->regsPerBlock; } }
	property int TextureAlign { int get(){ return props->textureAlign; } }
};
}