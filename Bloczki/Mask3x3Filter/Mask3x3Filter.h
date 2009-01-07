#ifndef Mask3x3FilterH
#define Mask3x3FilterH

#include "../../Program/engine/Block.h"
#include "../function.hpp"

extern "C"  __declspec(dllexport) int __stdcall run(Block *aBlock);
extern "C"  __declspec(dllexport) bool __stdcall showConfig(TComponent *owner, Block *aBlock);
extern "C"  __declspec(dllexport) int __stdcall validate(Block *aBlock);

#endif //Mask3x3FilterH

