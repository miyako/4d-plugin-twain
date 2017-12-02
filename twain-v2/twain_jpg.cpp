#include "twain_jpg.h"

void JPG::my_error_exit(j_common_ptr cinfo)
{
	
}

void JPG::my_output_message (j_common_ptr cinfo)
{
	
}

boolean JPG::jpeg_memory_empty_output_buffer (j_compress_ptr cinfo)
{
	jpeg_memory_destination_ptr dest = (jpeg_memory_destination_ptr) cinfo->dest;
	unsigned char *newbuf;
	/* abort if incsize is 0 (no expansion of buffer allowed) */
	if (dest->incsize == 0) return _false;
	/* otherwise, try expanding buffer... */
	newbuf = (unsigned char *)realloc(dest->buf,dest->bufsize + dest->incsize);
	if (!newbuf) return _false;
	dest->pub.next_output_byte = newbuf + dest->bufsize;
	dest->pub.free_in_buffer = dest->incsize;
	dest->buf = newbuf;
	dest->bufsize += dest->incsize;
	dest->incsize *= 2;
	return _true;
}

void JPG::jpeg_memory_init_destination (j_compress_ptr cinfo)
{
	jpeg_memory_destination_ptr dest = (jpeg_memory_destination_ptr) cinfo->dest;
	dest->pub.next_output_byte = dest->buf;
	dest->pub.free_in_buffer = dest->bufsize;
}

void JPG::jpeg_memory_term_destination (j_compress_ptr cinfo)
{
	jpeg_memory_destination_ptr dest = (jpeg_memory_destination_ptr) cinfo->dest;
	*dest->buf_ptr = dest->buf;
	*dest->bufsize_ptr = dest->bufsize - dest->pub.free_in_buffer;
}

void JPG::jpeg_memory_dest (j_compress_ptr cinfo, unsigned char **bufptr, size_t *bufsizeptr, size_t incsize)
{
	jpeg_memory_destination_ptr dest;
	
	/* allocate destination manager object for compress object, if needed */
	if (!cinfo->dest) {
		cinfo->dest = (struct jpeg_destination_mgr *)
		(*cinfo->mem->alloc_small) ( (j_common_ptr) cinfo,
																JPOOL_PERMANENT,
																sizeof(jpeg_memory_destination_mgr) );
	}
	
	dest = (jpeg_memory_destination_ptr)cinfo->dest;
	
	dest->buf_ptr = bufptr;
	dest->buf = *bufptr;
	dest->bufsize_ptr = bufsizeptr;
	dest->bufsize = *bufsizeptr;
	dest->incsize = incsize;
	
	dest->pub.init_destination = jpeg_memory_init_destination;
	dest->pub.empty_output_buffer = jpeg_memory_empty_output_buffer;
	dest->pub.term_destination = jpeg_memory_term_destination;
}

void jpg_write_blob(C_BLOB &data, C_BLOB &picture,
										int width,
										int height,
										int depth,
										int bytes_per_line,
										J_COLOR_SPACE color,
										int dpi_x,
										int dpi_y,
										int quality)
{
	struct jpeg_compress_struct cinfo;
	struct JPG::my_error_mgr jcerr;
	
	/* initialize compression object */
	cinfo.err = jpeg_std_error(&jcerr.pub);
	jpeg_create_compress(&cinfo);
	jcerr.pub.error_exit = JPG::my_error_exit;
	jcerr.pub.output_message = JPG::my_output_message;
	jcerr.jump_set = 0;
	
	if (setjmp(jcerr.setjmp_buffer))
	{
		/* error handler for compress failures */
		jpeg_abort_compress(&cinfo);
		jcerr.jump_set=0;
	} else {
		jcerr.jump_set=1;
	}
	
	size_t outbuffersize = data.getBytesLength() + 32768;
	unsigned char *outbuffer = (unsigned char *)malloc(outbuffersize);
	
	if(outbuffer)
	{
		JPG::jpeg_memory_dest(&cinfo, &outbuffer, &outbuffersize, 65536);
		
		cinfo.in_color_space = color;
		cinfo.input_components = (color == JCS_RGB) ? 3 : 1;
		cinfo.image_width = width;
		cinfo.image_height = height;
		jpeg_set_defaults(&cinfo);
		//jpeg_set_defaults overrides density
		cinfo.density_unit = 1;   /* Inches */
		cinfo.X_density = dpi_x;
		cinfo.Y_density = dpi_y;
		cinfo.write_JFIF_header = _true;
		jpeg_set_quality(&cinfo, quality, _true);
		jpeg_simple_progression(&cinfo);
		cinfo.optimize_coding = _true;
		jpeg_start_compress(&cinfo, _true);
		
		unsigned char *p = (unsigned char *)data.getBytesPtr();
		
		JSAMPLE *jpegbuf = (JSAMPLE *)malloc(bytes_per_line);
		
		if(jpegbuf)
		{
			for(int y = 0; y < height; y++)
			{
				if(depth == 1)
				{
					JSAMPLE *buf8 = (JSAMPLE *)malloc(bytes_per_line * 8);
					for(int col1 = 0; col1 < bytes_per_line; col1++)
					{
						for(int col8 = 0; col8 < 8; col8++)
						{
							buf8[col1 * 8 + col8] = p[col1] & (1 << (8 - col8 - 1)) ? 0 : 0xff;
						}
					}
					jpeg_write_scanlines(&cinfo, &buf8, 1);
					free(buf8);
				}else
				{
					memcpy(jpegbuf, p, bytes_per_line);
					jpeg_write_scanlines(&cinfo, &jpegbuf, 1);
				}
				p += bytes_per_line;
			}//height
			free(jpegbuf);
		}
		
		jpeg_finish_compress(&cinfo);
		jpeg_destroy_compress(&cinfo);
		
		picture.addBytes((const uint8_t *)&outbuffersize, sizeof(outbuffersize));
		picture.addBytes((const uint8_t *)outbuffer, (unsigned int)outbuffersize);
		
		free(outbuffer);
	}//outbuffer
}
