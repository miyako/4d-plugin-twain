#include "twain_png.h"

void PNG::write_data_fn(png_structp png_ptr, png_bytep buf, png_size_t size)
{
	C_BLOB *blob = (C_BLOB *)png_get_io_ptr(png_ptr);
	blob->addBytes((const uint8_t *)buf, (uint32_t)size);
}

void PNG::output_flush_fn(png_structp png_ptr)
{
	
}

void png_write_blob(C_BLOB &data, C_BLOB &picture,
										int width,
										int height,
										int depth,
										int bytes_per_line,
										int color,
										int dpi_x,
										int dpi_y)
{
	C_BLOB png;
	png_structp png_ptr;
	png_infop info_ptr;
	
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png_ptr)
	{
		info_ptr = png_create_info_struct(png_ptr);
		if(info_ptr)
		{
			if(setjmp(png_jmpbuf(png_ptr)))
			{
				png_destroy_write_struct(&png_ptr, &info_ptr);
			}else{
				
				png_set_write_fn(png_ptr, (png_voidp)&png, PNG::write_data_fn, PNG::output_flush_fn);
				
				png_set_IHDR(png_ptr, info_ptr,
										 width, //pixels_per_line
										 height,//lines
										 depth,
										 color,
										 PNG_INTERLACE_NONE,
										 PNG_COMPRESSION_TYPE_DEFAULT,
										 PNG_FILTER_TYPE_DEFAULT);
				
				png_set_pHYs(png_ptr, info_ptr,
										 dpi_x * INCHES_PER_METER,
										 dpi_y * INCHES_PER_METER,
										 PNG_RESOLUTION_METER);
				
				//TODO:support icc_profile
				
				png_write_info(png_ptr, info_ptr);
				
				unsigned char *p = (unsigned char *)data.getBytesPtr();
				
				/*
				 //takes as much time, with no way to yield
				 std::vector<png_byte *>rows(height);
				 for(int y = 0; y < height; y++)
				 {
				 rows[y] = p;
				 p += bytes_per_line;
				 }//height
				 png_write_image(png_ptr, &rows[0]);
				 */
				
				for(int y = 0; y < height; y++)
				{
					//byteswap for depth 16
					if (depth == 16)
					{
						unsigned char *byte_l, *byte_h, *ptr;
						ptr = p;
						for (int j = 0; j < bytes_per_line; j += 2)
						{
							byte_l = ptr;
							byte_h = ptr + 1;
							unsigned char b = *byte_l;
							*byte_l = *byte_h;
							*byte_h = b;
							ptr += 2;
						}
					}
					
					png_write_row(png_ptr, p);
					p += bytes_per_line;
				}//height
				
				png_write_end(png_ptr, info_ptr);
				png_destroy_write_struct(&png_ptr, &info_ptr);
				
				size_t outbuffersize = png.getBytesLength();
				picture.addBytes((const uint8_t *)&outbuffersize, sizeof(outbuffersize));
			}
		}
	}
}
