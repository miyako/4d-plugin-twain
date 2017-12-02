#ifndef _TWAIN_PNG_H__
#define _TWAIN_PNG_H__ 1

#include "png.h"

#include "C_BLOB.h"

#define PNG_DEFAULT_RESOLUTION 300

#define INCHES_PER_METER (100.0/2.54)

#define PNG_COLOR_TYPE_UNKNOWN -1

#ifdef __cplusplus
extern "C" {
#endif
	
	namespace PNG
	{
		void write_data_fn(png_structp png_ptr, png_bytep buf, png_size_t size);
		void output_flush_fn(png_structp png_ptr);
	}
	
	void png_write_blob(C_BLOB &data,
											C_BLOB &picture,
											int width,
											int height,
											int depth,
											int bytes_per_line,
											int color,
											int dpi_x = PNG_DEFAULT_RESOLUTION,
											int dpi_y = PNG_DEFAULT_RESOLUTION);
	
#ifdef __cplusplus
}
#endif

#endif
