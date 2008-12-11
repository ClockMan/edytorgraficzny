#include <Graphics.hpp>

bool ReflectionHorizontally(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;

	for(int i(0); i < picture->Height; ++i)
	{
		int *line = reinterpret_cast<int*>(picture->ScanLine[i]);

		for(int j = 0; j <= ((picture->Width & (-2)) - 1) / 2; ++j)
		{
			int temp = line[j];
			line[j] = line[picture->Width - j - 1];
			line[picture->Width - j - 1] = temp;
		}
	}
	
	return true;
}

bool ReflectionVertically(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;

	int idx = picture->Width * 4;
	void* Buffer = new int[idx];

	for(int i(0); i <= ((picture->Height & (-2)) - 1) / 2; ++i)
	{
		Move(picture->ScanLine[i], Buffer, idx);
		Move(picture->ScanLine[picture->Height - i - 1], picture->ScanLine[i], idx);
		Move(Buffer, picture->ScanLine[picture->Height - i - 1], idx);
	}
	
	delete []Buffer;
	return true;
}

bool GreyScale(Graphics::TBitmap* picture)
{
  if(picture->Empty) return false;
		
	picture->PixelFormat = pf32bit;
  RGBQUAD* row;

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];

		for (int j(0); j < picture->Width; ++j)
		{
			int k = 0.299*row[j].rgbRed + 0.587*row[j].rgbGreen + 0.114*row[j].rgbBlue;

			row[j].rgbBlue = static_cast<BYTE>(k);
			row[j].rgbGreen = static_cast<BYTE>(k);
			row[j].rgbRed = static_cast<BYTE>(k);
		}
	}
	
	return true;
}

bool GreyBalance(Graphics::TBitmap* picture, int limit)
{
	if(picture->Empty) return false;
    
	RGBQUAD* row;
	picture->PixelFormat = pf32bit;

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];

		for (int j(0); j < picture->Width; ++j)
		{
			int k = 0.299*row[j].rgbRed + 0.587*row[j].rgbGreen + 0.114*row[j].rgbBlue;
			double level = 255 / limit;

			for(int x(1); x <= limit; ++x)
			{
				if(k < static_cast<int>((level*x)))
				{
					if(x==1) k = 0;
					else k = static_cast<int>((level*x));
					break;
				}
			}

			if(k < level) k = 0;
			if(k > static_cast<int>((level*limit))) k = 255;

			row[j].rgbRed = static_cast<BYTE>(k);
			row[j].rgbGreen = static_cast<BYTE>(k);
			row[j].rgbBlue = static_cast<BYTE>(k);
		}
	}
	
	return true;
}