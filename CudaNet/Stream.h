#pragma once
#include "ContextChild.h"

namespace CudaNet
{
	public ref class Stream : ContextChild
	{
	public:
		~Stream();
		!Stream();

	internal:
		Stream(Context^ parentContext);
		operator CUstream () { return stream; }

		CUstream stream;
	};
}