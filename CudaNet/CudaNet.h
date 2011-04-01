#pragma once
#include "Device.h"

namespace CudaNet {

	public ref class Cuda
	{
	private:
		static size_t refCount = 0;

		static void Init();
		static void Cleanup();

		static System::Collections::Generic::List<Device^> _Devices;

	public:

		property System::Collections::ObjectModel::ReadOnlyCollection<Device^>^ Devices
		{
			System::Collections::ObjectModel::ReadOnlyCollection<Device^>^ get()
			{
				return _Devices.AsReadOnly();
			}
		}

		property int DriverVersion
		{
			int get();
		}

		Cuda();
		~Cuda();
		!Cuda(){this->~Cuda();}
		// TODO: Add your methods for this class here.
	};
}
