#pragma once
#include <list>
#include "Module.h"
#include "Stream.h"

namespace CudaNet
{
ref class DevicePointer;
ref class HostPointer;
ref class ContextChild;
ref class Device;
public ref class Context : public System::IDisposable
{
private:
	CUcontext context;
	Device^ device;

internal:
	Context(Device^ device);

	//List of active modules
	//System::Collections::Generic::List<Module^> modules;
	System::Collections::Generic::List<Stream^> streams;
	//std::list<ContextChild^>* children;
	System::Collections::Generic::List<ContextChild^> children;

public:
	Module^ LoadModule(System::String^ SourceFile);
	Stream^ CreateStream();
	DevicePointer^ MallocDevice(unsigned int byteSize);
	HostPointer^ MallocHost(unsigned int byteSize);

	~Context();
	!Context();
};
}