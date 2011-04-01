#include "Stdafx.h"
#include < vcclr.h >

#include "Device.h"
#include "DevicePointer.h"
#include "HostPointer.h"
#include "Context.h"

using namespace CudaNet;

Context::Context(Device^ device) : context(NULL)
{
	this->device = device;
	pin_ptr<CUcontext> pContext = &context;
	HANDLE(cuCtxCreate(pContext, CU_CTX_SCHED_AUTO, device->device));
	int i=0;
}

Context::~Context()
{
	System::GC::SuppressFinalize(this);
	log("Context::~Context");

	//Delete any remaining children
	for(int i=0; i<streams.Count; ++i)
	{
		delete streams[i];
	}
	streams.Clear();

	while(children.Count > 0)
	{
		try
		{
			delete children[children.Count-1];
		}
		catch(...)
		{
		}
	}
	children.Clear();

	HANDLE(cuCtxDestroy(context));

}

Context::!Context()
{
	log("Context::!Context");
	throw gcnew CudaError("Context not disposed. Use Dispose() manually on Contexts!");
	return;
}

Module^ Context::LoadModule(System::String^ SourceFile)
{
	//Convert String^ to const char*
	pin_ptr<const wchar_t> wch = PtrToStringChars(SourceFile);
	size_t convertedChars = 0;
	size_t  sizeInBytes = ((SourceFile->Length + 1) * 2);
	errno_t err = 0;
	char *ch = (char *)malloc(sizeInBytes);
	err = wcstombs_s(&convertedChars, ch, sizeInBytes, wch, sizeInBytes);
	if (err != 0) throw gcnew System::Exception("invalid name for source file. Only ASCII is supported now.");

	//Check if module matches host address_size (32 vs. 64 bit)
	System::IO::StreamReader^ fileReader = gcnew System::IO::StreamReader(SourceFile);
	for(int i=0; i<2; i++) fileReader->ReadLine();	//Skip .version and .target
	System::String^ line = fileReader->ReadLine();
	//Match to ".address_size xx"
	int address_size = 32;
	if(line->Contains(".address_size")) address_size = System::Int32::Parse(line->Substring(14));

	if(address_size / 8 != sizeof(void*)) throw gcnew System::Exception(System::String::Format("Incompatible address_size. The ptx to load is compiled for {0} bit systems.", address_size));

	//Load module
	CUmodule module;
	pin_ptr<CUmodule> pModule = &module;
	HANDLE(cuModuleLoad(pModule, ch));

	Module^ m = gcnew Module(module, this);
	return m;
}

Stream^ Context::CreateStream()
{
	return gcnew Stream(this);
}

DevicePointer^ Context::MallocDevice(unsigned int byteSize)
{
	CUdeviceptr p;
	pin_ptr<CUdeviceptr> pp = &p;
	HANDLE(cuMemAlloc(pp, byteSize));
	//
	return gcnew DevicePointer(p, byteSize, true, this);
}

HostPointer^ Context::MallocHost(unsigned int byteSize)
{
	void* ptr;
	pin_ptr<void*> pPtr = &ptr;
	HANDLE(cuMemAllocHost(pPtr, byteSize));

	return gcnew HostPointer(ptr, byteSize, this);
}