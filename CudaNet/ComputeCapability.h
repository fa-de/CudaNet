public ref struct ComputeCapability
{
private:
	int _major, _minor;
public:
	property int Major { int get(){ return _major; } }
	property int Minor { int get(){ return _minor; } }
	virtual System::String^ ToString() override
	{
		return System::String::Format("{0}.{1}", _major, _minor);
	}
internal:
	ComputeCapability(CUdevice device)
	{
		pin_ptr<int> pMajorCapability = &_major;
		pin_ptr<int> pMinorCapability = &_minor;
		HANDLE(cuDeviceComputeCapability(pMajorCapability, pMinorCapability, device));
	}
};