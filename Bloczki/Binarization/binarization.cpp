//---------------------------------------------------------------------------
#pragma hdrstop

#include "bibarization.h"
#include <Graphics.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool Binarization(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;

	picture->PixelFormat = pf32bit;
	RGBQUAD* row;

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];
		if(!row) return false;

		for (int j(0); j < picture->Width; ++j)
		{
			int k = 0.299*row[j].rgbRed + 0.587*row[j].rgbGreen + 0.114*row[j].rgbBlue;

			if (k>128) k = 255;
			else k = 0;

			row[j].rgbRed = static_cast<BYTE>(k);
			row[j].rgbGreen = static_cast<BYTE>(k);
			row[j].rgbBlue = static_cast<BYTE>(k);
		}
	}

	return true;
}

bool BinarizationBalance(Graphics::TBitmap* picture, int limit, int firstColor, int secondColor)
{
	if(picture->Empty) return false;

	picture->PixelFormat = pf32bit;
	RGBQUAD* row;

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];
		if(!row) return false;

		for (int j(0); j < picture->Width; ++j)
		{
			int k = 0.299*row[j].rgbRed + 0.587*row[j].rgbGreen + 0.114*row[j].rgbBlue;

			if (k>=limit) k = firstColor; else k = secondColor;

			int R = GetRValue((TColor)k);
			int G = GetGValue((TColor)k);
			int B = GetBValue((TColor)k);

			row[j].rgbRed = static_cast<BYTE>(R);
			row[j].rgbGreen = static_cast<BYTE>(G);
			row[j].rgbBlue = static_cast<BYTE>(B);
		}
	}

	return true;
}
