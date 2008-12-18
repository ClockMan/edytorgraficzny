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
bool BinarizationBalance(Graphics::TBitmap* picture, int limit, int firstColor = clBlack, int secondColor = clWhite);

// rozmycie obrazu
bool MotionBlur(Graphics::TBitmap* picture);

// obrot w prawo - zarezerwowane MP
bool RightRotation(Graphics::TBitmap* picture);

// obrot w lewo - zarezerwowane MP
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

// filtry statystycznie - mediana, erozja, ekspansja, otwarcie, zamkniecie

/*
wszystkie operacje wykonywane sa za pomoca funnkcji bool StatisticsFilter(Graphics::TBitmap* picture, int filter) wywolywanej 
z roznym parametrem 'filter'
mediana - filter = 5
erozja - filter = 1
ekspansja - filter = 9
	
otwarcie - dwukrotne wywolanie funkcji - raz z parametrem 1 drugi raz z 9
zamkniecie - dwukrotne wywolanie funkcji - raz z parametrem 9 drugi raz z 1

w gestii wywolujacego lezy aby argument filter byl poprawny!!!

funkcja StatisticsFilter wykozystuje algorytm Hoare'a ktory z koleii kozysta z funkcji partition. Nezly dolaczyc obydwie definicje.
*/
int med(int *c, int w); // algorytm Hoare'a
int partition(int *c, int a, int b); // funkcja pomocnicza dla algorytmu Hoare'a
bool StatisticsFilter(Graphics::TBitmap* picture, int filter);

// jasnosc(naswietlenie) obrazu

/*
wartosc argumentu limit = od -255 do 255
wartosc domyslna = 0
*/
bool Lightning(Graphics::TBitmap* picture, int limit);

// kontrast

/*
wartosc argumentu limit = od -127 do 127
wartosc domyslna = 0
*/
bool Contrast(Graphics::TBitmap* picture, double limit);

// nasycenie kolorow

/*
wartosc argumentu limit = od -255 do 255
wartosc domyslna = 0
*/
bool Saturation(Graphics::TBitmap* picture, int limit);

// korekcja gamma

/*
wartosc argumentu limit = od 1 do 699
wartosc domyslna = 1;
*/
bool GammaCorrection(Graphics::TBitmap* picture, int limit);

// balans skladowych RGB

/*
wartosc argumentu limit_r, limit_g, limit_b = od -255 do 255
wartosci domyslne = 0
aby zmieniac nasycenie tylko jednej skladowej nalezy pozostale przekazac jako z wartoscia = 0
*/
bool RGBBalance(Graphics::TBitmap* picture, int limit_r, int limit_g, int limit_b);

// filtracje z maska 3/3/3

/*
argument mask jest to tablica 9-u wartosci calkowitoliczbowych. tablica jednowymiarowa wiec jesli mamy maske w postaci
macierzy 3x3 to przed wyslaniem jej do funkcji trzeba zrobic z niej tablice jednowymiarowa (9 elementow)
zapewnienie poprawnego rozmiaru tablicy mask lezy w gestii wywolujacego!!!
*/
bool MaskFilter(Graphics::TBitmap* picture, short* mask);

#endif // GraphFunction