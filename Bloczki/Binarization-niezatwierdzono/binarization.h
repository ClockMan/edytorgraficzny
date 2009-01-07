//---------------------------------------------------------------------------

#ifndef binarizationH
#define binarizationH

#include "../../Program/engine/Block.h"

extern "C" __stdcall __declspec(dllexport) int run(Block *aBlock);
extern "C" __stdcall __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __stdcall __declspec(dllexport) int validate(Block *aBlock);

bool Binarization(Graphics::TBitmap*);
bool BinarizationBalance(Graphics::TBitmap*, int, int, int);

//---------------------------------------------------------------------------
#endif
