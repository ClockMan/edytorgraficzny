#ifndef _CHANGEBITRATE_H_
#define _CHANGEBITRATE_H_

#include "../../Program/engine/Block.h"

extern "C" __declspec(dllexport) int __stdcall run(Block *aBlock);
extern "C"  __declspec(dllexport) bool __stdcall showConfig(TComponent *owner, Block *aBlock);
extern "C" __declspec(dllexport) int __stdcall validate(Block *aBlock);

bool Monochrome(Graphics::TBitmap* image);

#endif //_CHANGEBITRATE_H_
