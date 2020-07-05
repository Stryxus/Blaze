#pragma once

using namespace std;

namespace Blaze {

	public ref class ImageProcessor
	{
	public:

		// WebP

		static vector<uint8_t> ConvertToWebP(vector<uint8_t>* data);
		static vector<uint8_t> ResizeWebP(vector<uint8_t>* data);
		static vector<uint8_t> CompressWebP(vector<uint8_t>* data);

	private:

		// AVIF

		static vector<uint8_t> ConvertToAVIF(vector<uint8_t>* data);
		static vector<uint8_t> ResizeAVIF(vector<uint8_t>* data);
		static vector<uint8_t> CompressAVIF(vector<uint8_t>* data);
	};
}
