#include "Stdafx.h"
#include "Context.h"
#include "Stream.h"

using namespace CudaNet;

Stream::Stream(Context^ parentContext):ContextChild(parentContext)
{
	pin_ptr<CUstream> pStream = &stream;
	HANDLE(cuStreamCreate(pStream, 0));
	parentContext->streams.Add(this);
}

Stream::~Stream()
{
	this->!Stream();
}

Stream::!Stream()
{
	log("Stream::!Stream");
	HANDLE(cuStreamDestroy(stream));
}