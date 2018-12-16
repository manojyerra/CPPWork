#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include "libpng/png.h"
#include <stdio.h>
#include <stdlib.h>

int WritePNG(unsigned char* rawData, int width, int height, int bitsPerPixel, const char *savePath)
{
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    png_byte ** row_pointers = NULL;
    unsigned int x=0;
	unsigned int y=0;
	int depth = 8;
	int pixel_size = 3;
	int colorType = PNG_COLOR_TYPE_RGB;

	int status = -1;
	
	if(bitsPerPixel == 32)
	{
		pixel_size = 4;
		colorType = PNG_COLOR_TYPE_RGBA;
	}

	FILE * fp;
    fp = fopen(savePath, "wb");
    if(!fp)	goto fopen_failed;

	png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)	goto png_create_write_struct_failed;
    info_ptr = png_create_info_struct (png_ptr);
	if (info_ptr == NULL)				goto png_create_info_struct_failed;
    if (setjmp (png_jmpbuf (png_ptr)))	goto png_failure;
    
    png_set_IHDR (png_ptr,
                  info_ptr,
                  width,
                  height,
                  depth,
                  colorType,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);
    
    /* Initialize rows of PNG. */
    row_pointers = (png_byte**) png_malloc (png_ptr, height * sizeof (png_byte *));
    
	int index = 0;
	for (y=0; y <height; ++y)
	{
        png_byte* row = (png_byte*) png_malloc (png_ptr, sizeof(unsigned char)*width*pixel_size);
        row_pointers[y] = row;
        
		for (x=0; x<width*pixel_size; ++x)
		{
            *row++ = rawData[index];
			index++;
		}
    }
    
    /* Write the image data to "fp". */

    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    /* The routine has successfully written the file, so we set
       "status" to a value which indicates success. */

    status = 0;
    
    for (y = 0; y < height; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);
    
 png_failure:
 png_create_info_struct_failed: png_destroy_write_struct (&png_ptr, &info_ptr);
 png_create_write_struct_failed: fclose (fp);

 fopen_failed:
    return status;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int width = 100;
	int height = 200;
	int bitsPerPixel = 32;
	unsigned char* rawData = (unsigned char*)malloc(width*height*4);
	memset(rawData, 128, width*height*4);

	WritePNG(rawData, width, height, bitsPerPixel, "NewPNG.png");
}