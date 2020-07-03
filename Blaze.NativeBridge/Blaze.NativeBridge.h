#pragma once

using namespace std;

using namespace System;

namespace Blaze {

	public ref class NativeBridge
	{
	public:

		// WebP

		vector<uint8_t> ConvertToWebP(vector<uint8_t> *data);
		vector<uint8_t> ResizeWebP(vector<uint8_t> *data);
		vector<uint8_t> CompressWebP(vector<uint8_t> *data);

		// FFmpeg

	private:

		// AVIF

		vector<uint8_t> ConvertToAVIF(vector<uint8_t> *data);
		vector<uint8_t> ResizeAVIF(vector<uint8_t> *data);
		vector<uint8_t> CompressAVIF(vector<uint8_t> *data);
	};
}
