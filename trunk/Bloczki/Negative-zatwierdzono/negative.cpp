//---------------------------------------------------------------------------


#pragma hdrstop

#include "negative.h"   
#include <Graphics.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool Negative(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;    
	RGBQUAD *row;

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];
		if(!row) return false;

		for (int j(0); j < picture->Width; ++j)
		{
			row[j].rgbRed = (BYTE)~row[j].rgbRed;
			row[j].rgbGreen = (BYTE)~row[j].rgbGreen;
			row[j].rgbBlue = (BYTE)~row[j].rgbBlue;
		}
	}
    
	return true;
}