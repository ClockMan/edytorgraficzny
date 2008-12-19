#include "RotateRight.h"

bool RotateRight(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
    
	picture->PixelFormat = pf32bit;
	RGBQUAD *row1, *row2;

	Graphics::TBitmap* tempPicture = new Graphics::TBitmap();
	tempPicture->PixelFormat=pf32bit;

	tempPicture->Width = picture->Height;
	tempPicture->Height = picture->Width;


	for(int i(0); i < tempPicture->Height; ++i)
	{
		row2 = (RGBQUAD *) tempPicture->ScanLine[i];

		unsigned int x = tempPicture->Width-1;

		for (int j(0); j < tempPicture->Width; ++j)
		{
			row1 = (RGBQUAD *) picture->ScanLine[x];
			row2[j].rgbRed = (BYTE) row1[i].rgbRed;
			row2[j].rgbGreen = (BYTE) row1[i].rgbGreen;
			row2[j].rgbBlue = (BYTE) row1[i].rgbBlue;
			x--;
		}		
	}
	
	picture->Assign(tempPicture);
	tempPicture->Free();
	
	return true;
}
 