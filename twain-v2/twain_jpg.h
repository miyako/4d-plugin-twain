#ifndef _TWAIN_JPG_H__
#define _TWAIN_JPG_H__ 1

#include "twain_dsm.h"

#include "jpeglib.h"

#include "C_BLOB.h"

#define JPG_DEFAULT_RESOLUTION 300

#ifdef __cplusplus
extern "C" {
#endif
	
	namespace JPG
	{
		
		struct my_error_mgr
		{
			struct jpeg_error_mgr pub;
			jmp_buf setjmp_buffer;
			int     jump_set;
		};
		
		typedef struct my_error_mgr *my_error_ptr;
		
		typedef struct
		{
			struct jpeg_destination_mgr pub;
			
			unsigned char **buf_ptr;
			size_t *bufsize_ptr;
			size_t incsize;
			
			unsigned char *buf;
			size_t bufsize;
			
		} jpeg_memory_destination_mgr;
		
		typedef jpeg_memory_destination_mgr *jpeg_memory_destination_ptr;
		void my_error_exit(j_common_ptr cinfo);
		void my_output_message (j_common_ptr cinfo);
		boolean jpeg_memory_empty_output_buffer (j_compress_ptr cinfo);
		void jpeg_memory_init_destination (j_compress_ptr cinfo);
		void jpeg_memory_term_destination (j_compress_ptr cinfo);
		void jpeg_memory_dest (j_compress_ptr cinfo, unsigned char **bufptr, size_t *bufsizeptr, size_t incsize);
		
	}
	
	void jpg_write_blob(C_BLOB &data, C_BLOB &picture,
											int width,
											int height,
											int depth,
											int bytes_per_line,
											J_COLOR_SPACE color,
											int dpi_x = JPG_DEFAULT_RESOLUTION,
											int dpi_y = JPG_DEFAULT_RESOLUTION,
											int quality = 100);
	
#ifdef __cplusplus
}
#endif

#endif
