#include "ContextChild.h"

namespace CudaNet
{
	public ref class HostPointer : ContextChild
	{
		internal:
			void* ptr;
			unsigned int size;

			HostPointer(void* ptr, size_t byteSize, Context^ parentContext);
			~HostPointer(){this->!HostPointer();}
			!HostPointer();

		public:
			property unsigned int Size { unsigned int get(){ return size; } }

			generic<typename T> where T:value class
			void Get(array<T>^ dst)
			{
				pin_ptr<void> dH = &dst[0];
				unsigned int dstSize = dst->Length * sizeof(T);
				if(size > dstSize)
				{
					size = dstSize;
					System::Diagnostics::Debug::WriteLine("Unable to copy complete dataset. Destination block is too small.");
				}
				memcpy(dH, ptr, size);
			}

			generic<typename T> where T:value class
			void Set(array<T>^ src)
			{
				pin_ptr<void> dH = &src[0];
				unsigned int size = src->Length * sizeof(T);
				if(size > this->size) //Clamp size to copy to actual size of block on device
				{
					size = this->size;
					System::Diagnostics::Debug::WriteLine("Unable to copy complete dataset. Destination block is too small.");
				}
				memcpy(ptr, dH, size);
			}
	};
}