#include "pch.h"
#include "imageproc.h"

#include <imageio\image_dec.h>
#include <imageio\imageio_util.h>
#include <src\webp\mux.h>
#include <src\webp\encode.h>

vector<char> convert_to_webp(const char* filepath, int width, int height, float quality)
{
	WebPAnimEncoder* enc = NULL;
	WebPAnimEncoderOptions anim_config;
	WebPConfig config;
	WebPPicture pic;
	WebPData webp_data;

	WebPDataInit(&webp_data);
	WebPAnimEncoderOptionsInit(&anim_config);
	WebPConfigInit(&config);
	WebPPictureInit(&pic);
	WebPValidateConfig(&config);
	pic.use_argb = 1;
	config.lossless = 1;

	const uint8_t* data = NULL;
	size_t data_size = 0;
	WebPImageReader reader = nullptr;
	ImgIoUtilReadFile(filepath, &data, &data_size);
	reader = WebPGuessImageReader(data, data_size);
	reader(data, data_size, &pic, 1, NULL);
	free((void*)data);

	enc = WebPAnimEncoderNew(width, height, &anim_config);

	WebPAnimEncoderAdd(enc, &pic, 0, &config);

	WebPPictureFree(&pic);

	WebPAnimEncoderAssemble(enc, &webp_data);

	vector<char> res{};
	res.reserve(webp_data.size);
	memcpy(&res, &webp_data.bytes, webp_data.size);
	return res;
}