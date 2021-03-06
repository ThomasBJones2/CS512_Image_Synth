#include <jpeglib.h>
#include <stdio.h>

void save(char filename[128]){

	unsigned char image[WIDTH * HEIGHT * 3];
	glReadPixels(0, 0, WIDTH, 
		HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, image);

	if( remove( filename ) != 0 )
    		cout << "Error Deleting file\n";
  	else
    		cout << "File successfully deleted\n";

	FILE* outfile = fopen(filename, "wb");
 
	if (!outfile)
		Shut_Down(1);

/*  Code taken from http://www.andrewewhite.net/wordpress/2008/09/02/very-simple-jpeg-writer-in-c-c/
*/
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr       jerr;
 
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);
 
	cinfo.image_width      = WIDTH;
	cinfo.image_height     = HEIGHT;
	cinfo.input_components = 3;
	cinfo.in_color_space   = JCS_RGB;		


	jpeg_set_defaults(&cinfo);
	/*set the quality [0..100]  */
	jpeg_set_quality (&cinfo, 100, true);
	jpeg_start_compress(&cinfo, true);

	JSAMPROW row_pointer;          /* pointer to a single row */
 
	while (cinfo.next_scanline < cinfo.image_height) {
		row_pointer = (JSAMPROW) &image[HEIGHT*WIDTH*3 - cinfo.next_scanline*3*WIDTH];
		jpeg_write_scanlines(&cinfo, &row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);

	cout << "saved!\n";
}
