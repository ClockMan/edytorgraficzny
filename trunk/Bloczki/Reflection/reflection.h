//---------------------------------------------------------------------------

#ifndef reflectionH
#define reflectionH

#include "../../Program/engine/Block.h"

extern "C" __stdcall __declspec(dllexport) int run(Block *aBlock);
extern "C" __stdcall __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __stdcall __declspec(dllexport) int validate(Block *aBlock);

bool ReflectionHorizontally(Graphics::TBitmap*);
bool ReflectionVertically(Graphics::TBitmap*);

#endif // reflectionH
