#include "SaveImage.h"

#pragma link "freeimage.lib"

bool SaveImage(Graphics::TBitmap* picture, AnsiString path, TYPE bit_per_pixel, int flags)
{
	FIBITMAP *image = FreeImage_Allocate(picture->Width, picture->Height, 32);
	if(!image) return false;
	
	picture->PixelFormat = pf32bit;
	
	if(!WriteImage(image, picture))
	{
		FreeImage_Unload(image);
		return false;
	}

	AnsiString ext((((AnsiString)ExtractFileExt(path))).UpperCase());

	if (ext == ".BMP")
	{
		if(FreeImage_Save(FIF_BMP, BitrateConversion(image,bit_per_pixel), path.c_str(), BMP_DEFAULT))
		{
			FreeImage_Unload(image);
			return true;
		}	
	}	
	else if (ext == ".JPG")
	{
		if(FreeImage_Save(FIF_JPEG, FreeImage_ConvertTo24Bits(image), path.c_str(), flags))
		{
			FreeImage_Unload(image);
			return true;
		}
	}		
	else if (ext == ".TIF")
	{
		if(FreeImage_Save(FIF_TIFF, FreeImage_ConvertTo24Bits(image), path.c_str(), TIFF_DEFAULT))
		{
			FreeImage_Unload(image);
			return true;
		}	
	}
		
	FreeImage_Unload(image);
	return false;
}
//---------------------------------------------------------------------------
bool WriteImage(FIBITMAP* image, Graphics::TBitmap* picture)
{
	RGBQUAD *row1, *row2;
	
	for(int i(0); i < picture->Height; ++i)
	{
		row1 = (RGBQUAD *)FreeImage_GetScanLine(image,i);
		row2 = (RGBQUAD *)picture->ScanLine[picture->Height-1-i];
		
		if(!row1 || !row2) return false;

		for(int j(0); j < picture->Width; ++j)
		{
			row1[j].rgbRed = row2[j].rgbRed;
			row1[j].rgbGreen = row2[j].rgbGreen;
			row1[j].rgbBlue = row2[j].rgbBlue;
		}
	}
	
	return true;
}
//---------------------------------------------------------------------------
FIBITMAP* BitrateConversion(FIBITMAP* image, TYPE bit_per_pixel)
{
	ConvertType convertTab[] =
	{
		FreeImage_ConvertTo4Bits,
		FreeImage_ConvertTo8Bits,
		FreeImage_ConvertTo16Bits555,
		FreeImage_ConvertTo24Bits,
		FreeImage_ConvertTo32Bits
	};
	
	switch (bit_per_pixel)
	{
		case bit_1:
			return FreeImage_Threshold(image,128);
		case bit_4:
			return convertTab[0](image);
		case bit_8:
			return convertTab[1](image);
		case bit_16:
			return convertTab[2](image);
		case bit_24:
			return convertTab[3](image);
		case bit_32:
			return convertTab[4](image);
	}
	
	return 0;
}
