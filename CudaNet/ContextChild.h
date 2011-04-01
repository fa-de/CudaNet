#pragma once

namespace CudaNet
{
	ref class Context;
	public ref class ContextChild
	{
	protected:
		Context^ parentContext;

	public:
		ContextChild(Context^ parentContext);
		virtual ~ContextChild();
		!ContextChild();
	};
}