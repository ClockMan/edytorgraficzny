#ifndef GraphFunction
#define GraphFunction

#include <Graphics.hpp>
#include <math.h> // przy <cmath> borland sie pluje!!!

// odbicie poziome - zrobione
bool ReflectionHorizontally(Graphics::TBitmap* picture);

// odbicie pionowe - zrobione
bool ReflectionVertically(Graphics::TBitmap* picture);

// pelna skala szarosci - zrobione
bool GreyScale(Graphics::TBitmap* picture);

// posteryzacja - zrobione
bool GreyBalance(Graphics::TBitmap* picture, int limit);

// odrwacanie kolorów (negatyw)
bool InversionColors(Graphics::TBitmap* picture);

// binaryzacja (obraz monochromatyczny)
bool Binarization(Graphics::TBitmap* picture);

// binaryzacja progowa
bool BinarizationBalance(Graphics::TBitmap* picture, int limit, int firstColor = clBlack, int secondColor = clWhite)

// rozmycie obrazu
bool MotionBlur(Graphics::TBitmap* picture);

// obrot w prawo
bool RightRotation(Graphics::TBitmap* picture);

// obrot w lewo
bool LeftRotation(Graphics::TBitmap* picture);

// szum kolorowy
bool ColorNoise(Graphics::TBitmap* picture, int noise);

// szum bialy (mono)
bool MonoNoise(Graphics::TBitmap* picture, int noise);

// wyplowienie obrazu
bool FadedPicture(Graphics::TBitmap* picture);

// wyrownanie histogramu
bool HistogramEqualization(Graphics::TBitmap* picture);

// rozciagniecie histogramu
bool HistogramStretching(Graphics::TBitmap* picture);


#endif // GraphFunction