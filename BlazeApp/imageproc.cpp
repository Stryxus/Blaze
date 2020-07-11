#include "pch.h"
#include "imageproc.h"

#include <imageio\image_dec.h>
#include <imageio\imageio_util.h>
#include <src\webp\encode.h>
#include <src\webp\decode.h>
#include <src\webp\mux_types.h>
#include <src\webp\mux.h>
#include <src\webp\demux.h>
#include <src\webp\types.h>
#include <src\webp\format_constants.h>

void convert_to_webp(const char* from, const char* to, int width, int height, float quality)
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