//---------------------------------------------------------------------------

#ifndef reflectionH
#define reflectionH

#include "../../Program/engine/Block.h"
#include "../function.hpp"

extern "C" __declspec(dllexport) int __stdcall run(Block *aBlock);
extern "C"  __declspec(dllexport) bool __stdcall showConfig(TComponent *owner, Block *aBlock);
extern "C" __declspec(dllexport) int __stdcall validate(Block *aBlock);

#endif // reflectionH
