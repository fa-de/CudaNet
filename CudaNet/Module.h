#pragma once
#include "ContextChild.h"

namespace CudaNet
{
ref class Function;
ref class DevicePointer;

public ref class Module : ContextChild
{
private:
	CUmodule module;

internal:
	Module(CUmodule module, Context^ parentContext);

public:
	Function^ GetFunction(System::String^ Name);
	DevicePointer^ GetGlobal(System::String^ Name);

	~Module(){ this->!Module(); }
	!Module();
};
}