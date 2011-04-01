#include "Stdafx.h"
#include "ContextChild.h"
#include "Context.h"

using namespace CudaNet;

ContextChild::ContextChild(Context^ parentContext) : parentContext(parentContext)
{
	parentContext->children.Add(this);
}

ContextChild::~ContextChild()
{
	System::GC::SuppressFinalize(this);
	this->!ContextChild();
}

ContextChild::!ContextChild()
{
	parentContext->children.Remove(this);
}