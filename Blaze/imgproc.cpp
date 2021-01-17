#include "pch.h"
#include "imgproc.h"

#include <image_dec.h>
#include <imageio_util.h>

#include <webp\encode.h>
#include <webp\decode.h>
#include <webp\mux_types.h>
#include <webp\mux.h>
#include <webp\demux.h>
#include <webp\types.h>
#include <webp\format_constants.h>

void convert_png_to_webp(const char* from, const char* to, int width, int height, float quality)
{
	WebPConfig config;
	WebPPicture pic;
	WebPConfigPreset(&config, WEBP_PRESET_DEFAULT, quality);
	WebPPictureInit(&pic);
	pic.use_argb = 1;
	WebPPictureAlloc(&pic);

	char* fileData = NULL;
	const uint8_t* data{};
	size_t data_size = 0;

	ifstream fileIn(string(from), ios_base::binary);
	fileIn.seekg(0, ios_base::end);
	data_size = fileIn.tellg();
	fileIn.seekg(0, ios_base::beg);
	fileData = (char*)malloc(data_size + 1);
	fileIn.read(fileData, data_size);
	fileIn.close();

	data = reinterpret_cast<uint8_t*>(fileData);
	ReadPNG(data, data_size, &pic, 1, NULL);
	free((void*)data);

	WebPMemoryWriter writer{};
	WebPMemoryWriterInit(&writer);
	pic.writer = WebPMemoryWrite;
	pic.custom_ptr = &writer;

	WebPPictureRescale(&pic, width, height);
	WebPEncode(&config, &pic);
	WebPPictureFree(&pic);

	ofstream fileOut(string(to), ios_base::binary);
	fileOut.write((char*)writer.mem, writer.size);
	fileOut.close();
}

void convert_png_to_avif(const char* from, const char* to, int width, int height, float quality)
{

}