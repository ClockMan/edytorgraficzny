#ifndef FFT_H
#define FFT_H

#include <vcl.h>
#include "../function.hpp"
#include "../../Program/engine/Block.h"

extern "C" __declspec(dllexport) int __stdcall run(Block *aBlock);
extern "C" __declspec(dllexport) bool __stdcall showConfig(TComponent *owner, Block *aBlock);
extern "C" __declspec(dllexport) int __stdcall validate(Block *aBlock);

struct Complex //liczba zespolna
{
        double Re;//czesc rzeczywista
        double Im;//czesc urojona

        Complex(double a, double b) { Re=a; Im=b; }
        Complex() { Re=0; Im=0; }
};

class Fourier    //dla zwiekszenia szybkosci wszsytkie funkcje sa inline
{
        private:
                Complex **Pixel;
                unsigned int Width;
                unsigned int Height;
        public:
                Fourier(unsigned int w, unsigned int h)
                {
                        Width = w;
                        Height = h;
                        
                        Pixel = new Complex*[Width];
                        for(unsigned int i=0;i<Width;i++)
                        {
                                Pixel[i] = new Complex[Height];
                                Pixel[i]->Re=0;
                                Pixel[i]->Im=0;
                        }
                }

                ~Fourier()
                {
                        for(unsigned int i = 0; i < Width; i++)
                                delete[]Pixel[i];
                        delete[] Pixel;
                }

                void SetPixel(unsigned int w, unsigned int h, Complex *set) { Pixel[w][h] = *set; }
                Complex * GetPixel(unsigned int w, unsigned int h){ return &Pixel[w][h]; }
                Graphics::TBitmap* ToBitmap();
                unsigned int GetWidth(void) { return Width; }
                unsigned int GetHeight(void) { return Height; }
};

Graphics::TBitmap** Fimage(Graphics::TBitmap* image);


//MIXFFT
void fft(long n, double xRe[], double xIm[], double yRe[], double yIm[]);
void factorize(long n, long *nFact, long fact[]);
void transTableSetup(long sofar[], long actual[], long remain[], long *nFact, long *nPoints);
void permute(long nPoint, long nFact, long fact[], long remain[], double xRe[], double xIm[], double yRe[], double yIm[]);
void initTrig(long radix);
void fft_4(double aRe[], double aIm[]);
void fft_5(double aRe[], double aIm[]);
void fft_8(void);
void fft_10(void);
void fft_odd(long radix);
void twiddleTransf(long sofarRadix, long radix, long remainRadix, double yRe[], double yIm[]);


#endif//FFT_H
 