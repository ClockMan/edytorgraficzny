//---------------------------------------------------------------------------

#ifndef negativeH
#define negativeH

#include "../../Program/engine/Block.h"

extern "C" __stdcall __declspec(dllexport) int run(Block *aBlock);
extern "C" __stdcall __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __stdcall __declspec(dllexport) int validate(Block *aBlock);

bool Negative(Graphics::TBitmap*);

#endif
