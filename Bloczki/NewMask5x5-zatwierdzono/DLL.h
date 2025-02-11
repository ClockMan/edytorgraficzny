//---------------------------------------------------------------------------

#ifndef DLLH
#define DLLH

#include "../../Program/engine/Block.h"
#include "../../TypyDanych/Mask5x5/Interface/IMask5x5.h"

extern "C" __declspec(dllexport) int __stdcall run(Block *aBlock);
extern "C" __declspec(dllexport) bool __stdcall showConfig(TComponent *owner, Block *aBlock);
extern "C" __declspec(dllexport) int __stdcall validate(Block *aBlock);
//---------------------------------------------------------------------------
#endif
