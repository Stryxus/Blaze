using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Security;

namespace Blaze
{
    public sealed class WebP : IDisposable
    {
        private const int WEBP_MAX_DIMENSION = 16383;

        public Bitmap Decode(byte[] rawWebP)
        {
            int outputSize;
            Bitmap bmp = null;
            BitmapData bmpData = null;
            GCHandle pinnedWebP = GCHandle.Alloc(rawWebP, GCHandleType.Pinned);
            try
            {
                IntPtr ptrData = pinnedWebP.AddrOfPinnedObject();
                if (UnsafeNativeMethods.WebPGetInfo(ptrData, rawWebP.Length, out int imgWidth, out int imgHeight) == 0) throw new Exception("Can´t get information of WebP");
#pragma warning disable CA2000 // Dispose objects before losing scope
                bmp = new Bitmap(imgWidth, imgHeight, PixelFormat.Format24bppRgb);
#pragma warning restore CA2000 // Dispose objects before losing scope
                bmpData = bmp.LockBits(new Rectangle(0, 0, imgWidth, imgHeight), ImageLockMode.WriteOnly, bmp.PixelFormat);
                outputSize = bmpData.Stride * imgHeight;
                if (UnsafeNativeMethods.WebPDecodeBGRInto(ptrData, rawWebP.Length, bmpData.Scan0, outputSize, bmpData.Stride) == 0) throw new Exception("Can´t decode WebP");
                return bmp;
            }
            catch (Exception ex) { throw new Exception(ex.Message + "\r\nIn WebP.Decode"); }
            finally
            {
                if (bmpData != null) bmp.UnlockBits(bmpData);
                if (pinnedWebP.IsAllocated) pinnedWebP.Free();
            }
        }

        [System.Diagnostics.CodeAnalysis.SuppressMessage("Maintainability", "CA1507:Use nameof to express symbol names", Justification = "<Pending>")]
        public byte[] Encode(Bitmap bmp, int quality = 75)
        {
            if (bmp.Width == 0 || bmp.Height == 0) throw new ArgumentException("Bitmap contains no data.", "bmp");
            if (bmp.Width > WEBP_MAX_DIMENSION || bmp.Height > WEBP_MAX_DIMENSION) throw new NotSupportedException("Bitmap's dimension is too large. Max is " + WEBP_MAX_DIMENSION + "x" + WEBP_MAX_DIMENSION + " pixels.");
            BitmapData bmpData = null;
            IntPtr unmanagedData = IntPtr.Zero;
            int size;
            try
            {
                bmpData = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadOnly, bmp.PixelFormat);
                size = UnsafeNativeMethods.WebPEncodeBGRA(bmpData.Scan0, bmp.Width, bmp.Height, bmpData.Stride, quality, out unmanagedData);
                if (size == 0) throw new Exception("Can´t encode WebP");
                byte[] rawWebP = new byte[size];
                Marshal.Copy(unmanagedData, rawWebP, 0, size);
                return rawWebP;
            }
            catch (Exception ex) { throw new Exception(ex.Message + "\r\nIn WebP.Encode"); }
            finally
            {
                if (bmpData != null) bmp.UnlockBits(bmpData);
                if (unmanagedData != IntPtr.Zero) UnsafeNativeMethods.WebPFree(unmanagedData);
            }
        }

        public string GetVersion()
        {
            try
            {
                uint v = (uint)UnsafeNativeMethods.WebPGetDecoderVersion();
                var revision = v % 256;
                var minor = (v >> 8) % 256;
                var major = (v >> 16) % 256;
                return major + "." + minor + "." + revision;
            }
            catch (Exception ex) { throw new Exception(ex.Message + "\r\nIn WebP.GetVersion"); }
        }

        public void GetInfo(byte[] rawWebP, out int width, out int height, out bool hasAlpha, out bool hasAnimation, out string format)
        {
            VP8StatusCode result;
            GCHandle pinnedWebP = GCHandle.Alloc(rawWebP, GCHandleType.Pinned);
            try
            {
                IntPtr ptrRawWebP = pinnedWebP.AddrOfPinnedObject();
                WebPBitstreamFeatures features = new WebPBitstreamFeatures();
                result = UnsafeNativeMethods.WebPGetFeatures(ptrRawWebP, rawWebP.Length, ref features);
                if (result != 0) throw new Exception(result.ToString());
                width = features.width;
                height = features.height;
                if (features.has_alpha == 1) hasAlpha = true; else hasAlpha = false;
                if (features.has_animation == 1) hasAnimation = true; else hasAnimation = false;
                format = features.format switch
                {
                    1 => "lossy",
                    2 => "lossless",
                    _ => "undefined",
                };
            }
            catch (Exception ex) { throw new Exception(ex.Message + "\r\nIn WebP.GetInfo"); }
            finally
            {
                if (pinnedWebP.IsAllocated) pinnedWebP.Free();
            }
        }

        private delegate int MyWriterDelegate([In()] IntPtr data, UIntPtr data_size, ref WebPPicture picture);

        [StructLayout(LayoutKind.Sequential)]
        private struct MemoryWriter
        {
            public int size;
            public byte[] data;
        }

        public void Dispose()
        {
            GC.SuppressFinalize(this);
        }
    }

    [SuppressUnmanagedCodeSecurity]
    internal static class UnsafeNativeMethods
    {
        private const int WEBP_DECODER_ABI_VERSION = 0x0208;

        public static VP8StatusCode WebPGetFeatures(IntPtr rawWebP, int data_size, ref WebPBitstreamFeatures features)
        {
            return IntPtr.Size switch
            {
                8 => WebPGetFeaturesInternal_x64(rawWebP, (UIntPtr)data_size, ref features, WEBP_DECODER_ABI_VERSION),
                _ => throw new InvalidOperationException("Invalid platform. Can not find proper function"),
            };
        }
        [DllImport("libwebp_x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "WebPGetFeaturesInternal")]
        private static extern VP8StatusCode WebPGetFeaturesInternal_x64([In()] IntPtr rawWebP, UIntPtr data_size, ref WebPBitstreamFeatures features, int WEBP_DECODER_ABI_VERSION);

        public static int WebPGetInfo(IntPtr data, int data_size, out int width, out int height)
        {
            return IntPtr.Size switch
            {
                8 => WebPGetInfo_x64(data, (UIntPtr)data_size, out width, out height),
                _ => throw new InvalidOperationException("Invalid platform. Can not find proper function"),
            };
        }
        [DllImport("libwebp_x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "WebPGetInfo")]
        private static extern int WebPGetInfo_x64([In()] IntPtr data, UIntPtr data_size, out int width, out int height);

        public static int WebPDecodeBGRInto(IntPtr data, int data_size, IntPtr output_buffer, int output_buffer_size, int output_stride)
        {
            return IntPtr.Size switch
            {
                8 => WebPDecodeBGRInto_x64(data, (UIntPtr)data_size, output_buffer, output_buffer_size, output_stride),
                _ => throw new InvalidOperationException("Invalid platform. Can not find proper function"),
            };
        }
        [DllImport("libwebp_x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "WebPDecodeBGRInto")]
        private static extern int WebPDecodeBGRInto_x64([In()] IntPtr data, UIntPtr data_size, IntPtr output_buffer, int output_buffer_size, int output_stride);

        public static int WebPEncodeBGR(IntPtr bgr, int width, int height, int stride, float quality_factor, out IntPtr output)
        {
            return IntPtr.Size switch
            {
                8 => WebPEncodeBGR_x64(bgr, width, height, stride, quality_factor, out output),
                _ => throw new InvalidOperationException("Invalid platform. Can not find proper function"),
            };
        }
        [DllImport("libwebp_x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "WebPEncodeBGR")]
        private static extern int WebPEncodeBGR_x64([In()] IntPtr bgr, int width, int height, int stride, float quality_factor, out IntPtr output);

        public static int WebPEncodeBGRA(IntPtr bgr, int width, int height, int stride, float quality_factor, out IntPtr output)
        {
            return IntPtr.Size switch
            {
                8 => WebPEncodeBGRA_x64(bgr, width, height, stride, quality_factor, out output),
                _ => throw new InvalidOperationException("Invalid platform. Can not find proper function"),
            };
        }
        [DllImport("libwebp_x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "WebPEncodeBGRA")]
        private static extern int WebPEncodeBGRA_x64([In()] IntPtr bgr, int width, int height, int stride, float quality_factor, out IntPtr output);

        public static void WebPFree(IntPtr p)
        {
            switch (IntPtr.Size)
            {
                case 8:
                    WebPFree_x64(p);
                    break;
                default:
                    throw new InvalidOperationException("Invalid platform. Can not find proper function");
            }
        }
        [DllImport("libwebp_x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "WebPFree")]
        private static extern void WebPFree_x64(IntPtr p);

        public static int WebPGetDecoderVersion()
        {
            return IntPtr.Size switch
            {
                8 => WebPGetDecoderVersion_x64(),
                _ => throw new InvalidOperationException("Invalid platform. Can not find proper function"),
            };
        }
        [DllImport("libwebp_x64.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "WebPGetDecoderVersion")]
        private static extern int WebPGetDecoderVersion_x64();
    }

#pragma warning disable CA1707 // Identifiers should not contain underscores
#pragma warning disable CA1051 // Do not declare visible instance fields
#pragma warning disable CA1815 // Override equals and operator equals on value types
    public enum VP8StatusCode
    {
        VP8_STATUS_OK = 0,
        VP8_STATUS_OUT_OF_MEMORY,
        VP8_STATUS_INVALID_PARAM,
        VP8_STATUS_BITSTREAM_ERROR,
        VP8_STATUS_UNSUPPORTED_FEATURE,
        VP8_STATUS_SUSPENDED,
        VP8_STATUS_USER_ABORT,
        VP8_STATUS_NOT_ENOUGH_DATA,
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct WebPBitstreamFeatures
    {
        public int width;
        public int height;
        public int has_alpha;
        public int has_animation;
        public int format;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5, ArraySubType = UnmanagedType.U4)]
        private readonly uint[] pad;
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct WebPPicture: IDisposable
    {
        public int use_argb;
        public UInt32 colorspace;
        public int width;
        public int height;
        public IntPtr y;
        public IntPtr u;
        public IntPtr v;
        public int y_stride;
        public int uv_stride;
        public IntPtr a;
        public int a_stride;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.U4)]
        private readonly uint[] pad1;
        public IntPtr argb;
        public int argb_stride;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3, ArraySubType = UnmanagedType.U4)]
        private readonly uint[] pad2;
        public IntPtr writer;  
        public IntPtr custom_ptr;
        public int extra_info_type;
        public IntPtr extra_info;
        public IntPtr stats;        
        public UInt32 error_code;   
        public IntPtr progress_hook;
        public IntPtr user_data;  
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 13, ArraySubType = UnmanagedType.U4)]
        private readonly uint[] pad3;
        private readonly IntPtr memory_;     
        private readonly IntPtr memory_argb_;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2, ArraySubType = UnmanagedType.U4)]
        private readonly uint[] pad4;

        public void Dispose()
        {
            GC.SuppressFinalize(this);
        }
    };
#pragma warning restore CA1815 // Override equals and operator equals on value types
#pragma warning restore CA1051 // Do not declare visible instance fields
#pragma warning restore CA1707 // Identifiers should not contain underscores
}
