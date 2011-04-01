#include "stdafx.h"
#include "Context.h"
#include "Module.h"
#include "Function.h"
#include < vcclr.h >

using namespace CudaNet;

Module::Module(CUmodule module, Context^ parentContext) : module(module), ContextChild(parentContext)
{
	
}

Module::!Module()
{
	log("Module::!Module");
	HANDLE(cuModuleUnload(module));
}

Function^ Module::GetFunction(System::String^ Name)
{
	//Convert String^ to const char*
	pin_ptr<const wchar_t> wch = PtrToStringChars(Name);
	size_t convertedChars = 0;
	size_t  sizeInBytes = ((Name->Length + 1) * 2);
	errno_t err = 0;
	char *ch = (char *)malloc(sizeInBytes);
	err = wcstombs_s(&convertedChars, ch, sizeInBytes, wch, sizeInBytes);
	if (err != 0) throw gcnew System::Exception("invalid name for source file. Only ASCII is supported atm.");

	CUfunction function;
	pin_ptr<CUfunction> pFunction = &function;
	HANDLE(cuModuleGetFunction(pFunction, module, ch));

	return gcnew Function(function);
}

DevicePointer^ Module::GetGlobal(System::String^ Name)
{
	//Convert String^ to const char*
	pin_ptr<const wchar_t> wch = PtrToStringChars(Name);
	size_t convertedChars = 0;
	size_t  sizeInBytes = ((Name->Length + 1) * 2);
	errno_t err = 0;
	char *ch = (char *)malloc(sizeInBytes);
	err = wcstombs_s(&convertedChars, ch, sizeInBytes, wch, sizeInBytes);
	if (err != 0) throw gcnew System::Exception("invalid name for source file. Only ASCII is supported atm.");

	CUdeviceptr global;
	pin_ptr<CUdeviceptr> pGlobal = &global;

	unsigned int size = 0;
	pin_ptr<unsigned int> pSize = &size;
	HANDLE(cuModuleGetGlobal(pGlobal, pSize, module, ch));

	return gcnew DevicePointer(global, size, false, parentContext);
}