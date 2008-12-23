#include "FadedPicture.h"

bool FadedPicture(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	if(picture->Height < 9 || picture->Width < 9) return false;

	picture->PixelFormat = pf32bit;
	RGBQUAD *row1, *row2, *row3;

	for(int i(1); i < (picture->Height) - 2; ++i)
	{
		row1 = (RGBQUAD *) picture->ScanLine[i];
		if(!row1) return false;
		row2 = (RGBQUAD *) picture->ScanLine[i+1];
		if(!row2) return false;
		row3 = (RGBQUAD *) picture->ScanLine[i+2];
		if(!row3) return false;

		for (int j(1); j < (picture->Width); ++j)
		{
			int R = (int) (((double)row1[j].rgbRed + (double)row2[j].rgbGreen + (double)row3[j].rgbBlue) / (double) 3);
			int G = (int) (((double)row1[j].rgbGreen + (double)row2[j].rgbGreen + (double)row3[j].rgbBlue) / (double) 3);
			int B = (int) (((double)row1[j].rgbBlue + (double)row2[j].rgbGreen + (double)row3[j].rgbBlue) / (double) 3);

			row1[j].rgbRed = static_cast<BYTE>(R);
			row2[j].rgbGreen = static_cast<BYTE>(G);
			row3[j].rgbBlue = static_cast<BYTE>(B);
		}
	}
	
	return true;
}
 