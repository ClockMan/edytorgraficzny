//---------------------------------------------------------------------------


#pragma hdrstop

#include "OpenImage.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#pragma link "FreeImage.lib"

bool OpenImage(Graphics::TBitmap* picture, const AnsiString& path)
{
	FREE_IMAGE_FORMAT imgFormat;

	imgFormat = FreeImage_GetFileType(path.c_str(), 0);

	if(imgFormat != FIF_UNKNOWN)
	{
		FIBITMAP *image, *tempImage;
		tempImage = FreeImage_Load(imgFormat, path.c_str(), 0);
		image = FreeImage_ConvertTo32Bits(tempImage);
		FreeImage_Unload(tempImage);

		if(image)
		{
			LoadImage(image, picture);
			FreeImage_Unload(image);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

void LoadImage(FIBITMAP* image, Graphics::TBitmap* picture)
{
	RGBQUAD *row1, *row2;
	
	picture->FreeImage();
	picture->PixelFormat = pf32bit;
	picture->Width = FreeImage_GetWidth(image);
	picture->Height = FreeImage_GetHeight(image);
	
	for(int i(0); i < picture->Height; ++i)
	{
		row1 = (RGBQUAD *)FreeImage_GetScanLine(image,i);
		row2 = (RGBQUAD *)picture->ScanLine[picture->Height-1-i];		
		
		for(int j(0); j < picture->Width; ++j)
		{
			row2[j].rgbRed = row1[j].rgbRed;
			row2[j].rgbGreen = row1[j].rgbGreen;
			row2[j].rgbBlue = row1[j].rgbBlue;
		}
	}
}

