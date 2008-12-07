//---------------------------------------------------------------------------


#pragma hdrstop

#include "reflection.h"
#include <Graphics.hpp>

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool ReflectionHorizontally(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	picture->PixelFormat = pf32bit;

	for(int i(0); i < picture->Height; ++i)
	{
		int *Line = (int*) picture->ScanLine[i];

		for(int j = 0; j <= ((picture->Width & (-2)) - 1) / 2; ++j)
		{
			int temp = Line[j];
			Line[j] = Line[picture->Width - j - 1];
			Line[picture->Width - j - 1] = temp;
		}
	}
	return true;
}

bool ReflectionVertically(Graphics::TBitmap* picture)
{
	if(picture->Empty) return false;
	picture->PixelFormat = pf32bit;

	int idx = picture->Width * 4;
	void *Buffer = new int[idx];

	for(int i(0); i <= ((picture->Height & (-2)) - 1) / 2; ++i)
	{
		Move(picture->ScanLine[i], Buffer, idx);
		Move(picture->ScanLine[picture->Height - i - 1], picture->ScanLine[i], idx);
		Move(Buffer, picture->ScanLine[picture->Height - i - 1], idx);
	}
	delete []Buffer;
	return true;
}
