#include "RotateLeft.h"


bool RotateLeft(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
 
	picture->PixelFormat = pf32bit;
	RGBQUAD *row1, *row2;

	Graphics::TBitmap* tempPicture = new Graphics::TBitmap;
	tempPicture->PixelFormat=pf32bit;

	tempPicture->Width = picture->Height;
	tempPicture->Height = picture->Width;
	
	unsigned int x = tempPicture->Height;

	for(int i(0); i < tempPicture->Height; ++i)
	{
		row2 = (RGBQUAD *) tempPicture->ScanLine[i];

		x -= 1;

		for (int j(0); j < tempPicture->Width; ++j)
		{
			row1 = (RGBQUAD *) picture->ScanLine[j];
			row2[j].rgbRed = (BYTE) row1[x].rgbRed;
			row2[j].rgbGreen = (BYTE) row1[x].rgbGreen;
			row2[j].rgbBlue = (BYTE) row1[x].rgbBlue;
		}
	}

	picture->Assign(tempPicture);
	tempPicture->Free();

	return true;
}
