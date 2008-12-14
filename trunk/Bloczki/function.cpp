#include <function.hpp>

// odbicie poziome - zrobione
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

// odbicie pionowe - zrobione
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


// pelna skala szarosci - zrobione
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

// posteryzacja - zrobione
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

// odrwacanie kolorów (negatyw)
bool InversionColors(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;    
	RGBQUAD *row;

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];

		for (int j(0); j < picture->Width; ++j)
		{
			row[j].rgbRed = (BYTE)~row[j].rgbRed;
			row[j].rgbGreen = (BYTE)~row[j].rgbGreen;
			row[j].rgbBlue = (BYTE)~row[j].rgbBlue;
		}
	}
    
	return true;
}

// binaryzacja (obraz monochromatyczny)
bool Binarization(Graphics::TBitmap* picture)
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

			if (k>128) k = 255; else k = 0;

			row[j].rgbRed = static_cast<BYTE>(k);
			row[j].rgbGreen = static_cast<BYTE>(k);
			row[j].rgbBlue = static_cast<BYTE>(k);
		}
	}

	return true;
}

// binaryzacja progowa
bool BinarizationBalance(Graphics::TBitmap* picture, int limit, int firstColor, int secondColor)
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

// rozmycie obrazu
bool MotionBlur(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	if(picture->Height < 9 || picture->Width < 9) return false;

	picture->PixelFormat = pf32bit;
	RGBQUAD *row1, *row2, *row3;

	for(int i(1); i < (picture->Height) -1; ++i)
	{
		row1 = (RGBQUAD *) picture->ScanLine[i-1];
		row2 = (RGBQUAD *) picture->ScanLine[i];
		row3 = (RGBQUAD *) picture->ScanLine[i+1];

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

// obrot w prawo
bool RightRotation(Graphics::TBitmap* picture)
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

// obrot w lewo
bool LeftRotation(Graphics::TBitmap* picture)
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

// szum kolorowy
bool ColorNoise(Graphics::TBitmap* picture, int noise)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;
	RGBQUAD* row;

	randomize();

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];

		for (int j(0); j < picture->Width; ++j)
		{
			int B = (row[j].rgbBlue + (int)random(noise) +1);
			int G = (row[j].rgbGreen + (int)random(noise) +1);
			int R = (row[j].rgbRed + (int)random(noise) +1);

			B = (B>255) ? 255 : (B<0) ? 0 : B;
			G = (G>255) ? 255 : (G<0) ? 0 : G;
			R = (R>255) ? 255 : (R<0) ? 0 : R;

			row[j].rgbBlue = (BYTE) B;
			row[j].rgbGreen = (BYTE) G;
			row[j].rgbRed = (BYTE) R;
		}
	}
	
	return true;
}

// szum bialy (mono)
bool MonoNoise(Graphics::TBitmap* picture, int noise)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;
	RGBQUAD *row;
	
	randomize();

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];

		for (int j(0); j < picture->Width; ++j)
		{
			int _noise = (int)random(noise) +1;
	
			int B = row[j].rgbBlue + _noise;
			int G = row[j].rgbGreen + _noise;
			int R = row[j].rgbRed + _noise;
	
			B = (B>255) ? 255 : (B<0) ? 0 : B;
			G = (G>255) ? 255 : (G<0) ? 0 : G;
			R = (R>255) ? 255 : (R<0) ? 0 : R;

			row[j].rgbRed = static_cast<BYTE>(R);
			row[j].rgbGreen = static_cast<BYTE>(G);
			row[j].rgbBlue = static_cast<BYTE>(B);
		}
	}

	return true;
}

// wyplowienie obrazu
bool FadedPicture(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	if(picture->Height < 9 || picture->Width < 9) return false;

	picture->PixelFormat = pf32bit;
	RGBQUAD *row1, *row2, *row3;

	for(int i(1); i < (picture->Height) - 2; ++i)
	{
		row1 = (RGBQUAD *) picture->ScanLine[i];
		row2 = (RGBQUAD *) picture->ScanLine[i+1];
		row3 = (RGBQUAD *) picture->ScanLine[i+2];

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

// wyrownanie histogramu
bool HistogramEqualization(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;
	
	unsigned int pix_count_R [256];
	unsigned int pix_count_G [256];
	unsigned int pix_count_B [256];
	unsigned char lut_R [256];
	unsigned char lut_G [256];
	unsigned char lut_B [256];
	long double D_R [256];
	long double D_G [256];
	long double D_B [256];
	
	RGBQUAD* row;

	for (int i = 0; i < 256; i++)
	{
		pix_count_R[i] = 0;
		pix_count_G[i] = 0;
		pix_count_B[i] = 0;
	}

	// obliczenie czêstotliwoœci wystêpowania poszczególnych sk³adowych RGB
	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];

		for(int j(0); j < picture->Width; ++j)
		{
			int R = row[j].rgbRed;
			int G = row[j].rgbGreen;
			int B = row[j].rgbBlue;
			pix_count_R[R]++;
			pix_count_G[G]++;
			pix_count_B[B]++;
		}
	}

	long double k = picture->Width * picture->Height;
	k = 1/k;
		
	// obliczenie dystrybuanty dla poszczególnych sk³adowych
	int sum_R = 0;
	int sum_G = 0;
	int sum_B = 0;

	for (int i(0); i < 256; ++i)
	{
		sum_R += pix_count_R[i];
		sum_G += pix_count_G[i];
		sum_B += pix_count_B[i];
		D_R[i] = sum_R * k;
		D_G[i] = sum_G * k;
		D_B[i] = sum_B * k;
	}
	
	// obliczenie D0 dla poszczególnych sk³adowych
	int i = 0;
	
	while (D_R[i] == 0)
		i++;
  
	long double D0_R = D_R[i];
	i = 0;
  
	while (D_G[i] == 0)
		i++;
  
	long double D0_G = D_G[i];
	i = 0;
	
	while (D_B[i] == 0)
		i++;
	
	long double D0_B = D_B[i];
	
	// obliczenie nowych tablic LUT
	for (int i(0); i < 256; ++i)
	{
		lut_R[i] = (unsigned char)floor (((D_R[i] - D0_R)/(1-D0_R)*(256-1) + 0.5));
		lut_G[i] = (unsigned char)floor (((D_G[i] - D0_G)/(1-D0_G)*(256-1) + 0.5));
		lut_B[i] = (unsigned char)floor (((D_B[i] - D0_B)/(1-D0_B)*(256-1) + 0.5));
	}
	
	// przeliczenie danych obrazu wg nowej tablicy LUT
	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];

		for(int j(0); j < picture->Width; ++j)
		{
			int R = row[j].rgbRed;
			int G = row[j].rgbGreen;
			int B = row[j].rgbBlue;
			row[j].rgbBlue = (BYTE)lut_B[B];
			row[j].rgbGreen = (BYTE)lut_G[G];
			row[j].rgbRed = (BYTE)lut_R[R];
		}	
	}
	
	return true;
}

// rozciagniecie histogramu
bool HistogramStretching(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;
	
	unsigned int lut_R [256];
	unsigned int lut_G [256];
	unsigned int lut_B [256];
	int R_Max = 1;
	int G_Max = 1;
	int B_Max = 1;
	int R_Min = 255;
	int G_Min = 255;
	int B_Min = 255;
	
	RGBQUAD *row;
	
	//Oblicznaie maks i min dla wszytskich skladowych (rgb)
	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];

		for(int j(0); j < picture->Width; ++j)
		{
			if(row[j].rgbRed > R_Max) R_Max = row[j].rgbRed;
			if(row[j].rgbGreen > G_Max) G_Max = row[j].rgbGreen;
			if(row[j].rgbBlue > B_Max) B_Max = row[j].rgbBlue;
			
			if(row[j].rgbRed < R_Min) R_Min = row[j].rgbRed;
			if(row[j].rgbGreen < G_Min) G_Min = row[j].rgbGreen;
			if(row[j].rgbBlue < B_Min) B_Min = row[j].rgbBlue;
		}
	}
	
	//Obliczamy tablice LUT
	for(int i(0); i < 256; ++i)
	{
		if (((255.0 / (R_Max - R_Min)) * (i - R_Min)) > 255) lut_R[i] = 255;
		else if (((255.0 / (R_Max - R_Min)) * (i - R_Min)) < 0) lut_R[i] = 0;
		else lut_R[i] = ((255.0 / (R_Max - R_Min)) * (i - R_Min));

		if (((255.0 / (G_Max - G_Min)) * (i - G_Min)) > 255) lut_G[i] = 255;
		else if (((255.0 / (G_Max - G_Min)) * (i - G_Min)) < 0) lut_G[i] = 0;
		else lut_G[i] = ((255.0 / (G_Max - G_Min)) * (i - G_Min));

		if (((255.0 / (B_Max - B_Min)) * (i - B_Min)) > 255) lut_B[i] = 255;
		else if (((255.0 / (B_Max - B_Min)) * (i - B_Min)) < 0) lut_B[i] = 0;
		else lut_B[i] = ((255.0 / (B_Max - B_Min)) * (i - B_Min));
	}
	
	// przeliczenie danych obrazu wg nowej tablicy LUT
	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];

		for(int j(0); j < picture->Width; ++j)
		{
			int R = row[j].rgbRed;
			int G = row[j].rgbGreen;
			int B = row[j].rgbBlue;
			row[j].rgbRed = (BYTE)lut_R[R];
			row[j].rgbGreen = (BYTE)lut_G[G];
			row[j].rgbBlue = (BYTE)lut_B[B];
		}
	}
	
	return true;
}