#include "motionblur.h"

bool MotionBlur(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	if(picture->Height < 9 || picture->Width < 9) return false;

	picture->PixelFormat = pf32bit;
	RGBQUAD *row1, *row2, *row3;

	for(int i(1); i < (picture->Height) -1; ++i)
	{
		row1 = (RGBQUAD *) picture->ScanLine[i-1];
		if(!row1) return false;
		row2 = (RGBQUAD *) picture->ScanLine[i];
		if(!row2) return false;
		row3 = (RGBQUAD *) picture->ScanLine[i+1];
		if(!row3) return false;

		for (int j(1); j < (picture->Width) -1; ++j)
		{
			int R = (row1[j-1].rgbRed + row1[j].rgbRed + row1[j+1].rgbRed + row2[j-1].rgbRed + 
					 row2[j].rgbRed + row2[j+1].rgbRed + row3[j-1].rgbRed + row3[j].rgbRed + row3[j+1].rgbRed) / 9;
			int G = (row1[j-1].rgbGreen + row1[j].rgbGreen + row1[j+1].rgbGreen + row2[j-1].rgbGreen + 
					 row2[j].rgbGreen + row2[j+1].rgbGreen + row3[j-1].rgbGreen + row3[j].rgbGreen + row3[j+1].rgbGreen) / 9;
			int B = (row1[j-1].rgbBlue + row1[j].rgbBlue + row1[j+1].rgbBlue + row2[j-1].rgbBlue + 
					 row2[j].rgbBlue + row2[j+1].rgbBlue + row3[j-1].rgbBlue + row3[j].rgbBlue + row3[j+1].rgbBlue) / 9;
					 
			row1[j-1].rgbRed = (BYTE) R;
			row1[j].rgbRed = (BYTE) R;
			row1[j+1].rgbRed = (BYTE) R;
			row2[j-1].rgbRed = (BYTE) R;
			row2[j].rgbRed = (BYTE) R;
			row2[j+1].rgbRed = (BYTE) R;
			row3[j-1].rgbRed = (BYTE) R;
			row3[j].rgbRed = (BYTE) R;
			row3[j+1].rgbRed = (BYTE) R;
			
			row1[j-1].rgbGreen = (BYTE) G;
			row1[j].rgbGreen = (BYTE) G;
			row1[j+1].rgbGreen = (BYTE) G;
			row2[j-1].rgbGreen = (BYTE) G;
			row2[j].rgbGreen = (BYTE) G;
			row2[j+1].rgbGreen = (BYTE) G;
			row3[j-1].rgbGreen = (BYTE) G;
			row3[j].rgbGreen = (BYTE) G;
			row3[j+1].rgbGreen = (BYTE) G;
			
			row1[j+1].rgbBlue = (BYTE) B;
			row1[j].rgbBlue = (BYTE) B;
			row1[j+1].rgbBlue = (BYTE) B;
			row2[j-1].rgbBlue = (BYTE) B;
			row2[j].rgbBlue = (BYTE) B;
			row2[j+1].rgbBlue = (BYTE) B;
			row3[j-1].rgbBlue = (BYTE) B;
			row3[j].rgbBlue = (BYTE) B;
			row3[j+1].rgbBlue = (BYTE) B;
		}
	}
	
	return true;
}
 