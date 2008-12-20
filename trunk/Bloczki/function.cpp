#include <function.hpp>

// odbicie poziome - zrobione
bool ReflectionHorizontally(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;

	for(int i(0); i < picture->Height; ++i)
	{
		int *line = reinterpret_cast<int*>(picture->ScanLine[i]);
		if(!line) return false;

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
		if(!row) return false;

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
		if(!row) return false;

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

// odrwacanie kolorów (negatyw) - zarezerwowane
bool InversionColors(Graphics::TBitmap* picture)
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

// binaryzacja (obraz monochromatyczny)
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

// obrot w prawo - zarezerwowane MP
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
		if(!row2) return false;

		unsigned int x = tempPicture->Width-1;

		for (int j(0); j < tempPicture->Width; ++j)
		{
			row1 = (RGBQUAD *) picture->ScanLine[x];
			if(!row1) return false;
			
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

// obrot w lewo - zarezerwowane MP
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
		if(!row2) return false;

		x -= 1;

		for (int j(0); j < tempPicture->Width; ++j)
		{
			row1 = (RGBQUAD *) picture->ScanLine[j];
			if(!row1) return false;
			
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
		if(!row) return false;

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
		if(!row) return false;

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
		if(!row) return false;

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
		if(!row) return false;

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
		if(!row) return false;

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
		if(!row) return false;

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

// filtry statystycznie - mediana, erozja, ekspansja, otwarcie, zamkniecie 
// OPIS W function.hpp
int partition(int *c, int a, int b)
{
	int e,tmp;
	e = c[a]; // elemennt dzielacy
	
	while (a < b)
	{
		while ((a < b) && (c[b] >= e)) b--;
	
		while ((a < b) && (c[a] < e)) a++;
			
		if (a < b)
		{
			tmp = c[a];
			c[a] = c[b];
			c[b] = tmp;
		}
	}

	return a;
}
//---------------------------------------------------------------------------
int med(int *c, int w)
{
	// algorytm Hoare'a
	int i = 0;
	int j = 8;
	int k;
	
	while (i!=j)
	{
		k = partition(c,i,j);
		k += -i+1;
    
		if (k >= w) j = i + k - 1;

		if (k < w)
		{
			w -= k;
			i += k;
		}
	}
	
	return c[i];
}

bool StatisticsFilter(Graphics::TBitmap* picture, int filter)
{
	if(picture->Empty) return false;
	if(picture->Height < 9 || picture->Width < 9) return false;
	
	picture->PixelFormat = pf32bit;
	
	RGBQUAD *row1, *row2, *row3, *row4;
	
	Graphics::TBitmap* tempPicture = new Graphics::TBitmap();
	tempPicture->PixelFormat = pf32bit;
	tempPicture->Assign(picture);

	int mediana_R[9];
	int mediana_G[9];
	int mediana_B[9];

	for(int i(1); i < (picture->Height) -1; ++i)
	{
		row1 = (RGBQUAD *) picture->ScanLine[i-1];
		if(!row1) return false;
		row2 = (RGBQUAD *) picture->ScanLine[i];
		if(!row2) return false;
		row3 = (RGBQUAD *) picture->ScanLine[i+1];
		if(!row3) return false;
		row4 = (RGBQUAD *) tempPicture->ScanLine[i];
		if(!row4) return false;

		for (int j(1); j < (picture->Width) -1; ++j)
		{
			mediana_R[0] = row1[j-1].rgbRed;
			mediana_R[1] = row1[j].rgbRed;
			mediana_R[2] = row1[j+1].rgbRed;
			mediana_R[3] = row2[j-1].rgbRed;
			mediana_R[4] = row2[j].rgbRed;
			mediana_R[5] = row2[j+1].rgbRed;
			mediana_R[6] = row3[j-1].rgbRed;
			mediana_R[7] = row3[j].rgbRed;
			mediana_R[8] = row3[j+1].rgbRed;
			int R = med(mediana_R, filter);

			mediana_G[0] = row1[j-1].rgbGreen;
			mediana_G[1] = row1[j].rgbGreen;
			mediana_G[2] = row1[j+1].rgbGreen;
			mediana_G[3] = row2[j-1].rgbGreen;
			mediana_G[4] = row2[j].rgbGreen;
			mediana_G[5] = row2[j+1].rgbGreen;
			mediana_G[6] = row3[j-1].rgbGreen;
			mediana_G[7] = row3[j].rgbGreen;
			mediana_G[8] = row3[j+1].rgbGreen;
			int G = med(mediana_G, filter);

			mediana_B[0] = row1[j-1].rgbBlue;
			mediana_B[1] = row1[j].rgbBlue;
			mediana_B[2] = row1[j+1].rgbBlue;
			mediana_B[3] = row2[j-1].rgbBlue;
			mediana_B[4] = row2[j].rgbBlue;
			mediana_B[5] = row2[j+1].rgbBlue;
			mediana_B[6] = row3[j-1].rgbBlue;
			mediana_B[7] = row3[j].rgbBlue;
			mediana_B[8] = row3[j+1].rgbBlue;
			int B = med(mediana_B, filter);

			R = (R > 255) ? 255 : (R < 0) ? 0 : R;
			G = (G > 255) ? 255 : (G < 0) ? 0 : G;
			B = (B > 255) ? 255 : (B < 0) ? 0 : B;

			row4[j].rgbRed = static_cast<BYTE>(R);
			row4[j].rgbGreen = static_cast<BYTE>(G);
			row4[j].rgbBlue = static_cast<BYTE>(B);
		}
	}

	picture->Assign(tempPicture);
	tempPicture->Free();
	
	return true;
}

// jasnosc(naswietlenie) obrazu
bool Lightning(Graphics::TBitmap* picture, int limit)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;
	
	limit = (limit>255) ? 255 : (limit<(-255)) ? -255 : limit;
	RGBQUAD* row;

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];
		if(!row) return false;

		for (int j(0); j < picture->Width; ++j)
		{
			int B = row[j].rgbBlue;
			int G = row[j].rgbGreen;
			int R = row[j].rgbRed;

			B += limit;
			B = (B>255) ? 255 : (B<0) ? 0 : B;

			G += limit;
			G = (G>255) ? 255 : (G<0) ? 0 : G;

			R += limit;
			R = (R>255) ? 255 : (R<0) ? 0 : R;

			row[j].rgbBlue = static_cast<BYTE>(B);
			row[j].rgbGreen = static_cast<BYTE>(G);
			row[j].rgbRed = static_cast<BYTE>(R);
		}
	}
	
	return true;
}

// kontrast
bool Contrast(Graphics::TBitmap* picture, double limit)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;
	
	limit = (limit>127) ? 127 : (limit<(-127)) ? -127 : limit;	
	RGBQUAD* row;
	
	double x = limit * 1.2725;
	double v1 = 255/(255 - 2 * x);
	
	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];
		if(!row) return false;

		for (int j(0); j < picture->Width; ++j)
		{
			int B = row[j].rgbBlue;
			int G = row[j].rgbGreen;
			int R = row[j].rgbRed;

			if(x > 0)
			{
				R = (R < x) ? 0 : (R > 255 - x) ? 255 : v1 * (R - x);
				G = (G < x) ? 0 : (G > 255 - x) ? 255 : v1 * (G - x);
				B = (B < x) ? 0 : (B > 255 - x) ? 255 : v1 * (B - x);
			}
			else if(x < 0)
			{
				R = v1 * (R - x);
				G = v1 * (G - x);
				B = v1 * (B - x);
			}

			R = (R > 255) ? 255 : (R < 0) ? 0: R;
			G = (G > 255) ? 255 : (G < 0) ? 0: G;
			B = (B > 255) ? 255 : (B < 0) ? 0: B;

			row[j].rgbBlue = static_cast<BYTE>(B);
			row[j].rgbGreen = static_cast<BYTE>(G);
			row[j].rgbRed = static_cast<BYTE>(R);
		}
	}
	
	return true;
}

// nasycenie kolorow
bool Saturation(Graphics::TBitmap* picture, int limit)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;
	
	limit = (limit>255) ? 255 : (limit<(-255)) ? -255 : limit;
	RGBQUAD* row;

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];
		if(!row) return false;

		for (int j(0); j < picture->Width; ++j)
		{
			int k = 0.299*row[j].rgbRed + 0.587*row[j].rgbGreen + 0.114*row[j].rgbBlue;

			int B = (k + (((row[j].rgbBlue - k) * (255 + limit)) / 255));
			int G = (k + (((row[j].rgbGreen - k) * (255 + limit)) / 255));
			int R = (k + (((row[j].rgbRed - k) * (255 + limit)) / 255));

			R = (R>255) ? 255 : (R<0) ? 0 : R;
			G = (G>255) ? 255 : (G<0) ? 0 : G;
			B = (B>255) ? 255 : (B<0) ? 0 : B;

			row[j].rgbBlue = static_cast<BYTE>(B);
			row[j].rgbGreen = static_cast<BYTE>(G);
			row[j].rgbRed = static_cast<BYTE>(R);
		}
	}
		
	return true;
}

// korekcja gamma
bool GammaCorrection(Graphics::TBitmap* picture, int limit)
{
	if(picture->Empty) return false;

	picture->PixelFormat = pf32bit;
	
	limit = (limit>699) ? 699 : (limit<1) ? 1 : limit;
	RGBQUAD* row;
	
	unsigned char lut [256];
	double gamma = ((double)limit * 6.99) / (double)699;

	// tablica LUT z korekcj¹ gamma
	for (int i(0); i < 256; ++i)
	{
		int lut_idx = 255*pow(i/255.0,1/gamma);
	
		if (lut_idx > 255)
			lut_idx = 255;
		
		lut[i] = lut_idx;
	}

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];
		if(!row) return false;

		for (int j(0); j < picture->Width; ++j)
		{
			int B = row[j].rgbBlue;
			int G = row[j].rgbGreen;
			int R = row[j].rgbRed;

			row[j].rgbBlue = static_cast<BYTE>(lut[B]);
			row[j].rgbGreen = static_cast<BYTE>(lut[G]);
			row[j].rgbRed = static_cast<BYTE>(lut[R]);       
		}	
	}
	
	return true;
}

// balans skladowych RGB
bool RGBBalance(Graphics::TBitmap* picture, int limit_r, int limit_g, int limit_b)
{
	if(picture->Empty) return false;
	
	picture->PixelFormat = pf32bit;
	
	limit_r = (limit_r>255) ? 255 : (limit_r<(-255)) ? -255 : limit_r;
	limit_g = (limit_g>255) ? 255 : (limit_g<(-255)) ? -255 : limit_g;
	limit_b = (limit_b>255) ? 255 : (limit_b<(-255)) ? -255 : limit_b;
	RGBQUAD* row;

	for(int i(0); i < picture->Height; ++i)
	{
		row = (RGBQUAD *) picture->ScanLine[i];
		if(!row) return false;

		for (int j(0); j < picture->Width; ++j)
		{
			int B = row[j].rgbBlue;
			int G = row[j].rgbGreen;
			int R = row[j].rgbRed;

			B += limit_b;
			B = (B>255) ? 255 : (B<0) ? 0 : B;

			G += limit_g;
			G = (G>255) ? 255 : (G<0) ? 0 : G;

			R += limit_r;
			R = (R>255) ? 255 : (R<0) ? 0 : R;

			row[j].rgbBlue = static_cast<BYTE>(B);
			row[j].rgbGreen = static_cast<BYTE>(G);
			row[j].rgbRed = static_cast<BYTE>(R);
		}
	}
	
	return true;
}

// filtry z maska 3x3
bool MaskFilter(Graphics::TBitmap* picture, short* mask)
{
	if(picture->Empty) return false;
	if(picture->Height < 9 || picture->Width < 9) return false;
    
	picture->PixelFormat = pf32bit;

	RGBQUAD *row1, *row2, *row3, *row4;
	Graphics::TBitmap* tempPicture = new Graphics::TBitmap();
	tempPicture->PixelFormat=pf32bit;
	tempPicture->Assign(picture);
	short maskSum(0);
	
	for(int i(0); i < 9; ++i) maskSum += mask[i];
	if(maskSum == 0) maskSum = 1;

	for(int i(1); i < (picture->Height) -1; ++i)
	{
		row1 = (RGBQUAD *) picture->ScanLine[i-1];
		if(!row1) return false;
		row2 = (RGBQUAD *) picture->ScanLine[i];
		if(!row2) return false;
		row3 = (RGBQUAD *) picture->ScanLine[i+1];
		if(!row3) return false;
		row4 = (RGBQUAD *) tempPicture->ScanLine[i];
		if(!row4) return false;

		for (int j(1); j < (picture->Width) -1; ++j)
		{
			int R = (row1[j-1].rgbRed*mask[0] + row1[j].rgbRed*mask[1] + row1[j+1].rgbRed*mask[2] +
					row2[j-1].rgbRed*mask[3] + row2[j].rgbRed*mask[4] + row2[j+1].rgbRed*mask[5] +
					row3[j-1].rgbRed*mask[6] + row3[j].rgbRed*mask[7] + row3[j+1].rgbRed*mask[8]) / maskSum;
					
			int G = (row1[j-1].rgbGreen*mask[0] + row1[j].rgbGreen*mask[1] + row1[j+1].rgbGreen*mask[2] +
					row2[j-1].rgbGreen*mask[3] + row2[j].rgbGreen*mask[4] + row2[j+1].rgbGreen*mask[5] +
					row3[j-1].rgbGreen*mask[6] + row3[j].rgbGreen*mask[7] + row3[j+1].rgbGreen*mask[8]) / maskSum;
					
			int B = (row1[j-1].rgbBlue*mask[0] + row1[j].rgbBlue*mask[1] + row1[j+1].rgbBlue*mask[2] +
					row2[j-1].rgbBlue*mask[3] + row2[j].rgbBlue*mask[4] + row2[j+1].rgbBlue*mask[5] +
					row3[j-1].rgbBlue*mask[6] + row3[j].rgbBlue*mask[7] + row3[j+1].rgbBlue*mask[8]) / maskSum;
					
			R = (R > 255) ? 255 : (R < 0) ? 0 : R;
			G = (G > 255) ? 255 : (G < 0) ? 0 : G;
			B = (B > 255) ? 255 : (B < 0) ? 0 : B;
			
			row4[j].rgbRed = static_cast<BYTE>(R);
			row4[j].rgbGreen = static_cast<BYTE>(G);
			row4[j].rgbBlue = static_cast<BYTE>(B);
		}
	}		
		picture->Assign(tempPicture);
		tempPicture->Free();
	
	return true;
}