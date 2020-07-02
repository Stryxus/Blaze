#ifndef PCH_H
#define PCH_H

#include "webp/decode.h"
#include "webp/encode.h"
#include "webp/types.h"

extern "C" {
	#include <libavutil/imgutils.h>
	#include <libavcodec/avcodec.h>
	#include <libswscale/swscale.h>
}

#endif
