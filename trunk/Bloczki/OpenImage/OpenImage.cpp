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
		FIBITMAP *image = FreeImage_Load(imgFormat, path.c_str(), 0);
		
		if(image)
		{
			if(LoadImage(FreeImage_ConvertTo32Bits(image), picture))
			{
				FreeImage_Unload(image);
				return true;
			}
			else
			{
				FreeImage_Unload(image);
				return false;
			}
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
}

bool LoadImage(FIBITMAP* image, Graphics::TBitmap* picture)
{
	picture->FreeImage();
	picture->PixelFormat = pf32bit;
	picture->Width = FreeImage_GetWidth(image);
	picture->Height = FreeImage_GetHeight(image);

	RGBQUAD *row1, *row2;

	for(int i(0); i < picture->Height; ++i)
	{
		row1 = (RGBQUAD *)FreeImage_GetScanLine(image,i);
		row2 = (RGBQUAD *)picture->ScanLine[picture->Height-1-i];		
		
		if(!row1 || !row2) return false;
		
		for(int j(0); j < picture->Width; ++j)
		{
			row2[j].rgbRed = row1[j].rgbRed;
			row2[j].rgbGreen = row1[j].rgbGreen;
			row2[j].rgbBlue = row1[j].rgbBlue;
		}
	}
	
	return true;
}

