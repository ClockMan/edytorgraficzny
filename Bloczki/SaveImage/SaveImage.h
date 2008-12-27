//---------------------------------------------------------------------------

#ifndef SaveImageH
#define SaveImageH

#include <Graphics.hpp>
#include "FreeImage.h"

#include "../../Program/engine/Block.h"

extern "C" __declspec(dllexport) int __stdcall run(Block *aBlock);
extern "C" __declspec(dllexport) bool __stdcall showConfig(TComponent *owner, Block *aBlock);
extern "C" __declspec(dllexport) int __stdcall validate(Block *aBlock);


//---------------------------------------------------------------------------
typedef DLL_API FIBITMAP* DLL_CALLCONV (*ConvertType)(FIBITMAP *dib);
enum TYPE {bit_1, bit_4, bit_8, bit_16, bit_24, bit_32};
//---------------------------------------------------------------------------

/* ONLY FOR JPEG IMAGE !!! */

// flags parameter can be :
// JPEG_DEFAULT - Saves with good quality (75:1)
// JPEG_QUALITYBAD - Saves with superb quality (100:1)
// JPEG_QUALITYAVERAGE - Saves with good quality (75:1)
// JPEG_QUALITYNORMAL - Saves with normal quality (50:1)
// JPEG_QUALITYGOOD - Saves with average quality (25:1)
// JPEG_QUALITYSUPERB - Saves with bad quality (10:1)
// Integer X in [0..100] - Save with quality X:1
// JPEG_PROGRESSIVE - Saves as a progressive JPEG file (use | to combine with JPEG quality flags)

/* ONLY FOR TIFF IMAGE !!! */

// flags parameter can be :
// TIFF_DEFAULT - Save using CCITTFAX4 compression for 1-bit bitmaps and LZW compression for any other bitmaps
// TIFF_CMYK - Stores tags for separated CMYK (use | to combine with TIFF compression flags)
// TIFF_PACKBITS - Save using PACKBITS compression
// TIFF_DEFLATE - Save using DEFLATE compression (also known as ZLIB compression)
// TIFF_ADOBE_DEFLATE - Save using ADOBE DEFLATE compression
// TIFF_NONE - Save without any compression
// TIFF_CCITTFAX3 - Save using CCITT Group 3 fax encoding
// TIFF_CCITTFAX4 - Save using CCITT Group 4 fax encoding
// TIFF_LZW - Save using LZW compression
// TIFF_JPEG - Save using JPEG compression (8-bit greyscale and 24-bit only. Default to LZW for other bitdepths)

bool SaveImage(Graphics::TBitmap* picture, AnsiString path, TYPE bit_per_pixel, int flags = 0);
//---------------------------------------------------------------------------
bool WriteImage(FIBITMAP* image, Graphics::TBitmap* picture);
FIBITMAP* BitrateConversion(FIBITMAP* image, TYPE bit_per_pixel);
//---------------------------------------------------------------------------
#endif
