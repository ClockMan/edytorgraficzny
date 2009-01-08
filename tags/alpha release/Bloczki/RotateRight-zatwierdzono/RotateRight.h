#ifndef _ROTATE_RIGHT_H_
#define _ROTATE_RIGHT_H_

#include "../../Program/engine/Block.h"
#include "../function.hpp"

extern "C"  __declspec(dllexport) int __stdcall run(Block *aBlock);
extern "C"  __declspec(dllexport) bool __stdcall showConfig(TComponent *owner, Block *aBlock);
extern "C"  __declspec(dllexport) int __stdcall validate(Block *aBlock);

#endif //_ROTATE_RIGHT_H_

