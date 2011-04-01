using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace managedCuda
{
	class Program
	{
		static void Main(string[] args)
		{
			try
			{
				CudaNet.Cuda cuda = new CudaNet.Cuda();
				Console.WriteLine("CUDA driver-version: {0}", cuda.DriverVersion);

				Console.WriteLine("Devices:");
				foreach (var dev in cuda.Devices)
				{
					Console.WriteLine(dev.Name);
					Console.WriteLine("\tMemory: {0} MiB", dev.TotalMemory >> 20);
					Console.WriteLine("\tCaps: {0}", dev.Capability);
					Console.WriteLine("\tClockRate: {0}", dev.Properties.ClockRate);
					Console.WriteLine("\tMaxThreadsPerBlock: {0}", dev.Properties.MaxThreadsPerBlock);
					Console.WriteLine("\tMaxThreadsDim: {0}", dev.Properties.MaxThreadsDim);
					Console.WriteLine("\tMaxGridSize: {0}", dev.Properties.MaxGridSize);
					Console.WriteLine("\tSharedMemPerBlock: {0}", dev.Properties.SharedMemPerBlock);
					Console.WriteLine("\tTotalConstantMemory: {0}", dev.Properties.TotalConstantMemory);
					Console.WriteLine("\tSIMDWidth: {0}", dev.Properties.SIMDWidth);
					Console.WriteLine("\tMemPitch: {0}", dev.Properties.MemPitch);
					Console.WriteLine("\tRegsPerBlock: {0}", dev.Properties.RegsPerBlock);
					Console.WriteLine("\tTextureAlign: {0}", dev.Properties.TextureAlign);
				}

				//return;
				//Load a test function on the first device
				using (CudaNet.Context ctx = cuda.Devices[0].CreateContext())
				{
					var stream1 = ctx.CreateStream();
					var module = ctx.LoadModule("functions.ptx");
					var f1 = module.GetFunction("GetDistanceField");

					return;

					var constant = module.GetGlobal("fabi");
					byte[] input = new byte[] { 8, 16, 42, 13 };
					constant.Upload(input);

					//Load source bitmap into GPU memory
					var b = new System.Drawing.Bitmap("D:\\test.bmp");
					var bData = b.LockBits(new System.Drawing.Rectangle(0, 0, b.Width, b.Height), System.Drawing.Imaging.ImageLockMode.ReadWrite, System.Drawing.Imaging.PixelFormat.Format32bppRgb);
					
					var devmem = ctx.MallocDevice((uint)(b.Width * b.Height * 4));
					devmem.Upload(bData.Scan0, devmem.Size);

					//Allocate destination memory set on GPU
					var dstMem = ctx.MallocDevice(devmem.Size);

					CudaNet.CudaParameter[] prms = new CudaNet.CudaParameter[]{ devmem, dstMem, bData.Stride / 4 };
					//Run kernel
					f1.SetBlockShape(new uint[]{16, 16, 1});
					//f1.LaunchGrid((uint)b.Width / 16, (uint)b.Height / 16, stream1);
					f1.Launch((uint)b.Width / 16, (uint)b.Height / 16, 1, prms);

					//var host = ctx.MallocHost(16);
					byte[] output = new byte[dstMem.Size];
					devmem.Download(output);
					//Save results from GPU to disk
					dstMem.Download(bData.Scan0, dstMem.Size);
					b.UnlockBits(bData);
					b.Save("D:\\tets2.bmp");
				}
			}
			catch (CudaNet.CudaError e)
			{
				Console.WriteLine("CUDA ERROR: " + e.Message);
			}
			return;
		}
	}
}
