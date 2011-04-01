namespace CudaNet
{
	public ref struct CudaExtent
	{
	public:
		int width, height, depth;

		virtual System::String^ ToString() override
		{
			return System::String::Format("{0} {1} {2}", width, height, depth);
		}

	internal: CudaExtent(int* ex)
		{
			this->width = ex[0];
			this->height = ex[1];
			this->depth = ex[2];
		}
	};
}