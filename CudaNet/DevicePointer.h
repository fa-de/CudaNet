#pragma once
#include "ContextChild.h"
#include "Stream.h"

namespace CudaNet
{
	public ref class DevicePointer : ContextChild
	{
	internal:
		CUdeviceptr ptr;
		unsigned int size;
		bool customAllocated;

		DevicePointer(CUdeviceptr ptr, unsigned int size, bool customAllocated, Context^ parentContext);

	public:
		~DevicePointer() { this->!DevicePointer(); }
		!DevicePointer();

		property unsigned int Size{ unsigned int get(){ return size; } }

		generic<typename T> where T : value class
		void Download(array<T>^ dst)
		{
			pin_ptr<void> dH = &dst[0];
			unsigned int dstSize = dst->Length * sizeof(T);
			//Clamp size to copy to actual size of destination array
			if(this->size < dstSize)
			{
				dstSize = this->size;
				System::Diagnostics::Debug::WriteLine("Unable to copy complete dataset. Destination block is too small.");
			}
			
			HANDLE(cuMemcpyDtoH(dH, ptr, dstSize));
		}

		generic<typename T> where T : value class
		void Upload(array<T>^ src)
		{
			pin_ptr<void> dH = &src[0];
			unsigned int size = src->Length * sizeof(T);
			if(size > this->size) //Clamp size to copy to actual size of block on device
			{
				size = this->size;
				System::Diagnostics::Debug::WriteLine("Unable to copy complete dataset. Destination block is too small.");
			}
			HANDLE(cuMemcpyHtoD(ptr, dH, size));
		}

		void Upload(System::IntPtr src, unsigned int size)
		{
			if(size > this->size) //Clamp size to copy to actual size of block on device
			{
				size = this->size;
				System::Diagnostics::Debug::WriteLine("Unable to copy complete dataset. Destination block is too small.");
			}
			HANDLE(cuMemcpyHtoD(ptr, src.ToPointer(), size));
		}

		void Download(System::IntPtr src, unsigned int size)
		{
			pin_ptr<void> dH = src.ToPointer();
			unsigned int dstSize = size;
			if(this->size < dstSize) //Clamp size to copy to actual size of block on device
			{
				dstSize = this->size;
				System::Diagnostics::Debug::WriteLine("Unable to copy complete dataset. Destination block is too small.");
			}
			HANDLE(cuMemcpyDtoH(dH, ptr, dstSize));
		}
	};
}