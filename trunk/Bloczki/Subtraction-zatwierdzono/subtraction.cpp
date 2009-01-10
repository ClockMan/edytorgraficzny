//---------------------------------------------------------------------------


#pragma hdrstop

#include "subtraction.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool Subtraction(Graphics::TBitmap* picture1, Graphics::TBitmap* picture2)
{
	if(picture1->Empty) return false;
	if(picture2->Empty) return false;

	picture1->PixelFormat = pf32bit;
	picture2->PixelFormat = pf32bit;
	RGBQUAD *row1;
	RGBQUAD *row2;
	int result;
	for(int i(0); i < picture1->Height && i < picture2->Height; ++i)
	{
		row1 = (RGBQUAD *) picture1->ScanLine[i];
		row2 = (RGBQUAD *) picture2->ScanLine[i];
		if(!row1) return false;
		if(!row2) return false;

		for (int j(0); j < picture1->Width && j < picture2->Width; ++j)
		{
			// wersja z zabronionym wyjœciem poza zakres <0,255>
			result = (int)row1[j].rgbRed-(int)row2[j].rgbRed;
			if(result < 0) result = 0;
			row1[j].rgbRed = (BYTE)result;

			result = (int)row1[j].rgbGreen-(int)row2[j].rgbGreen;
			if(result < 0) result = 0;
			row1[j].rgbGreen = (BYTE)result;

			result = (int)row1[j].rgbBlue-(int)row2[j].rgbBlue;
			if(result < 0) result = 0;
			row1[j].rgbBlue = (BYTE)result;

			/* wersja ze skalowaniem
			row1[j].rgbRed = (BYTE)((((float)row1[j].rgbRed-(float)row2[j].rgbRed))/2.+128);
			row1[j].rgbGreen = (BYTE)((((float)row1[j].rgbGreen-(float)row2[j].rgbGreen))/2.+128);
			row1[j].rgbBlue = (BYTE)((((float)row1[j].rgbBlue-(float)row2[j].rgbBlue))/2.+128);
			*/
		}
	}

	return true;
}