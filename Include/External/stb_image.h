/* stb_image - v2.19 - public domain image loader - http://nothings.org/stb
no warranty implied; use at your own risk

Do this:
#define STB_IMAGE_IMPLEMENTATION
before you include this file in *one* C or C++ file to create the implementation.

// i.e. it should look like this:
#include ...
#include ...
#include ...
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

You can #define STBI_ASSERT(x) before the #include to avoid using assert.h.
And #define STBI_MALLOC, STBI_REALLOC, and STBI_FREE to avoid using malloc,realloc,free


QUICK NOTES:
Primarily of interest to game developers and other people who can
avoid problematic images and only need the trivial interface

JPEG baseline & progressive (12 bpc/arithmetic not supported, same as stock IJG lib)
PNG 1/2/4/8/16-bit-per-channel

TGA (not sure what subset, if a subset)
BMP non-1bpp, non-RLE
PSD (composited view only, no extra channels, 8/16 bit-per-channel)

GIF (*comp always reports as 4-channel)
HDR (radiance rgbE format)
PIC (Softimage PIC)
PNM (PPM and PGM binary only)

Animated GIF still needs a proper API, but here's one way to do it:
http://gist.github.com/urraka/685d9a6340b26b830d49

- decode from memory or through FILE (define STBI_NO_STDIO to remove code)
- decode from arbitrary I/O callbacks
- SIMD acceleration on x86/x64 (SSE2) and ARM (NEON)

Full documentation under "DOCUMENTATION" below.


LICENSE

See end of file for license information.

RECENT REVISION HISTORY:

2.19  (2018-02-11) fix warning
2.18  (2018-01-30) fix warnings
2.17  (2018-01-29) bugfix, 1-bit BMP, 16-bitness query, fix warnings
2.16  (2017-07-23) all functions have 16-bit variants; optimizations; bugfixes
2.15  (2017-03-18) fix png-1,2,4; all Imagenet JPGs; no runtime SSE detection on GCC
2.14  (2017-03-03) remove deprecated STBI_JPEG_OLD; fixes for Imagenet JPGs
2.13  (2016-12-04) experimental 16-bit API, only for PNG so far; fixes
2.12  (2016-04-02) fix typo in 2.11 PSD fix that caused crashes
2.11  (2016-04-02) 16-bit PNGS; enable SSE2 in non-gcc x64
RGB-format JPEG; remove white matting in PSD;
allocate large structures on the stack;
correct channel count for PNG & BMP
2.10  (2016-01-22) avoid warning introduced in 2.09
2.09  (2016-01-16) 16-bit TGA; comments in PNM files; STBI_REALLOC_SIZED

See end of file for full revision history.


============================    Contributors    =========================

Image formats                          Extensions, features
Sean Barrett (jpeg, png, bmp)          Jetro Lauha (stbi_info)
Nicolas Schulz (hdr, psd)              Martin "SpartanJ" Golini (stbi_info)
Jonathan Dummer (tga)                  James "moose2000" Brown (iPhone PNG)
Jean-Marc Lienher (gif)                Ben "Disch" Wenger (io callbacks)
Tom Seddon (pic)                       Omar Cornut (1/2/4-bit PNG)
Thatcher Ulrich (psd)                  Nicolas Guillemot (vertical flip)
Ken Miller (pgm, ppm)                  Richard Mitton (16-bit PSD)
github:urraka (animated gif)           Junggon Kim (PNM comments)
Christopher Forseth (animated gif)     Daniel Gibson (16-bit TGA)
socks-the-fox (16-bit PNG)
Jeremy Sawicki (handle all ImageNet JPGs)
Optimizations & bugfixes                  Mikhail Morozov (1-bit BMP)
Fabian "ryg" Giesen                    Anael Seghezzi (is-16-bit query)
Arseny Kapoulkine
John-Mark Allen

Bug & warning fixes
Marc LeBlanc            David Woo          Guillaume George   Martins Mozeiko
Christpher Lloyd        Jerry Jansson      Joseph Thomson     Phil Jordan
Dave Moore              Roy Eltham         Hayaki Saito       Nathan Reed
Won Chun                Luke Graham        Johan Duparc       Nick Verigakis
the Horde3D community   Thomas Ruf         Ronny Chevalier    github:rlyeh
Janez Zemva             John Bartholomew   Michal Cichon      github:romigrou
Jonathan Blow           Ken Hamada         Tero Hanninen      github:svdijk
Laurent Gomila          Cort Stratton      Sergio Gonzalez    github:snagar
Aruelien Pocheville     Thibault Reuille   Cass Everitt       github:Zelex
Ryamond Barbiero        Paul Du Bois       Engin Manap        github:grim210
Aldo Culquicondor       Philipp Wiesemann  Dale Weiler        github:sammyhw
Oriol Ferrer Mesia      Josh Tobin         Matthew Gregan     github:phprus
Julian Raschke          Gregory Mullen     Baldur Karlsson    github:poppolopoppo
Christian Floisand      Kevin Schmidt                         github:darealshinji
Blazej Dariusz Roszkowski                                     github:Michaelangel007
*/

#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STBI_INCLUDE_STB_IMAGE_H

#ifndef STBI_NO_STDIO
#include <stdio.h>
#endif // STBI_NO_STDIO

#define STBI_VERSION 1

enum
{
	STBI_default = 0, // only used for desired_channels

	STBI_grey = 1,
	STBI_grey_alpha = 2,
	STBI_rgb = 3,
	STBI_rgb_alpha = 4
};

typedef unsigned char stbi_uc;
typedef unsigned short stbi_us;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STB_IMAGE_STATIC
#define STBIDEF static
#else
#define STBIDEF extern
#endif

	//////////////////////////////////////////////////////////////////////////////
	//
	// PRIMARY API - works on images of any type
	//

	//
	// load image by filename, open file, or memory buffer
	//

	typedef struct
	{
		int(*read)  (void *user, char *data, int size);   // fill 'data' with 'size' bytes.  return number of bytes actually read
		void(*skip)  (void *user, int n);                 // skip the next 'n' bytes, or 'unget' the last -n bytes if negative
		int(*eof)   (void *user);                       // returns nonzero if we are at end of file/data
	} stbi_io_callbacks;

	////////////////////////////////////
	//
	// 8-bits-per-channel interface
	//

	STBIDEF stbi_uc *stbi_load_from_memory(stbi_uc           const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);
	STBIDEF stbi_uc *stbi_load_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *channels_in_file, int desired_channels);
#ifndef STBI_NO_GIF
	STBIDEF stbi_uc *stbi_load_gif_from_memory(stbi_uc const *buffer, int len, int **delays, int *x, int *y, int *z, int *comp, int req_comp);
#endif


#ifndef STBI_NO_STDIO
	STBIDEF stbi_uc *stbi_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
	STBIDEF stbi_uc *stbi_load_from_file(FILE *f, int *x, int *y, int *channels_in_file, int desired_channels);
	// for stbi_load_from_file, file pointer is left pointing immediately after image
#endif

	////////////////////////////////////
	//
	// 16-bits-per-channel interface
	//

	STBIDEF stbi_us *stbi_load_16_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);
	STBIDEF stbi_us *stbi_load_16_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *channels_in_file, int desired_channels);

#ifndef STBI_NO_STDIO
	STBIDEF stbi_us *stbi_load_16(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
	STBIDEF stbi_us *stbi_load_from_file_16(FILE *f, int *x, int *y, int *channels_in_file, int desired_channels);
#endif

	////////////////////////////////////
	//
	// float-per-channel interface
	//
#ifndef STBI_NO_LINEAR
	STBIDEF float *stbi_loadf_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *channels_in_file, int desired_channels);
	STBIDEF float *stbi_loadf_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *channels_in_file, int desired_channels);

#ifndef STBI_NO_STDIO
	STBIDEF float *stbi_loadf(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
	STBIDEF float *stbi_loadf_from_file(FILE *f, int *x, int *y, int *channels_in_file, int desired_channels);
#endif
#endif

#ifndef STBI_NO_HDR
	STBIDEF void   stbi_hdr_to_ldr_gamma(float gamma);
	STBIDEF void   stbi_hdr_to_ldr_scale(float scale);
#endif // STBI_NO_HDR

#ifndef STBI_NO_LINEAR
	STBIDEF void   stbi_ldr_to_hdr_gamma(float gamma);
	STBIDEF void   stbi_ldr_to_hdr_scale(float scale);
#endif // STBI_NO_LINEAR

	// stbi_is_hdr is always defined, but always returns false if STBI_NO_HDR
	STBIDEF int    stbi_is_hdr_from_callbacks(stbi_io_callbacks const *clbk, void *user);
	STBIDEF int    stbi_is_hdr_from_memory(stbi_uc const *buffer, int len);
#ifndef STBI_NO_STDIO
	STBIDEF int      stbi_is_hdr(char const *filename);
	STBIDEF int      stbi_is_hdr_from_file(FILE *f);
#endif // STBI_NO_STDIO


	// get a VERY brief reason for failure
	// NOT THREADSAFE
	STBIDEF const char *stbi_failure_reason(void);

	// free the loaded image -- this is just free()
	STBIDEF void     stbi_image_free(void *retval_from_stbi_load);

	// get image dimensions & components without fully decoding
	STBIDEF int      stbi_info_from_memory(stbi_uc const *buffer, int len, int *x, int *y, int *comp);
	STBIDEF int      stbi_info_from_callbacks(stbi_io_callbacks const *clbk, void *user, int *x, int *y, int *comp);
	STBIDEF int      stbi_is_16_bit_from_memory(stbi_uc const *buffer, int len);
	STBIDEF int      stbi_is_16_bit_from_callbacks(stbi_io_callbacks const *clbk, void *user);

#ifndef STBI_NO_STDIO
	STBIDEF int      stbi_info(char const *filename, int *x, int *y, int *comp);
	STBIDEF int      stbi_info_from_file(FILE *f, int *x, int *y, int *comp);
	STBIDEF int      stbi_is_16_bit(char const *filename);
	STBIDEF int      stbi_is_16_bit_from_file(FILE *f);
#endif



	// for image formats that explicitly notate that they have premultiplied alpha,
	// we just return the colors as stored in the file. set this flag to force
	// unpremultiplication. results are undefined if the unpremultiply overflow.
	STBIDEF void stbi_set_unpremultiply_on_load(int flag_true_if_should_unpremultiply);

	// indicate whether we should process iphone images back to canonical format,
	// or just pass them through "as-is"
	STBIDEF void stbi_convert_iphone_png_to_rgb(int flag_true_if_should_convert);

	// flip the image vertically, so the first pixel in the output array is the bottom left
	STBIDEF void stbi_set_flip_vertically_on_load(int flag_true_if_should_flip);

	// ZLIB client - used by PNG, available for other purposes

	STBIDEF char *stbi_zlib_decode_malloc_guesssize(const char *buffer, int len, int initial_size, int *outlen);
	STBIDEF char *stbi_zlib_decode_malloc_guesssize_headerflag(const char *buffer, int len, int initial_size, int *outlen, int parse_header);
	STBIDEF char *stbi_zlib_decode_malloc(const char *buffer, int len, int *outlen);
	STBIDEF int   stbi_zlib_decode_buffer(char *obuffer, int olen, const char *ibuffer, int ilen);

	STBIDEF char *stbi_zlib_decode_noheader_malloc(const char *buffer, int len, int *outlen);
	STBIDEF int   stbi_zlib_decode_noheader_buffer(char *obuffer, int olen, const char *ibuffer, int ilen);


#ifdef __cplusplus
}
#endif

//
//
////   end header file   /////////////////////////////////////////////////////
#endif // STBI_INCLUDE_STB_IMAGE_H