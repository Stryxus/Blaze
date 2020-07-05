#pragma once

using namespace std;

using namespace System;

namespace Blaze {

	public ref class BlazeCore
	{
	public:

		// WebP

		static vector<uint8_t> ConvertToWebP(vector<uint8_t>* data);
		static vector<uint8_t> ResizeWebP(vector<uint8_t>* data);
		static vector<uint8_t> CompressWebP(vector<uint8_t>* data);

		// FFmpeg

	private:

		// AVIF

		static vector<uint8_t> ConvertToAVIF(vector<uint8_t>* data);
		static vector<uint8_t> ResizeAVIF(vector<uint8_t>* data);
		static vector<uint8_t> CompressAVIF(vector<uint8_t>* data);
	};
}
