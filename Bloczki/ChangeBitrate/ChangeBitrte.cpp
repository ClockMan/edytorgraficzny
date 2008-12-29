#include "ChangeBitrate.h"

bool Monochrome(Graphics::TBitmap* image)
{
	if(image->Empty) return false;
    image->PixelFormat=pf32bit;
    Graphics::TBitmap* picture = new Graphics::TBitmap();
    picture->Height=image->Height;
    picture->Width=image->Width;
    picture->PixelFormat=pf8bit;
        
	for(int i=0; i < image->Height; i++)
	{

                RGBQUAD *row = (RGBQUAD *) image->ScanLine[i];
                if(!row) return false;
				BYTE *r2 = (BYTE *) picture->ScanLine[i];
                if(!r2) return false;

				for (int j=0; j < image->Width; ++j)
				{
                        int k = 0.299*row[j].rgbRed + 0.587*row[j].rgbGreen + 0.114*row[j].rgbBlue;  //konieczna binaryzacja
						k>128?r2[j]=255:r2[j]=0;
				}
	}
    image->Assign(picture);
    image->Monochrome=true;
    image->PixelFormat=pf1bit;

	delete picture;

	return true;
}
 