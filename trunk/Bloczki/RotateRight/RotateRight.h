#ifndef _ROTATE_RIGHT_H_
#define _ROTATE_RIGHT_H_

#include "../../Program/engine/Block.h"

extern "C" __stdcall __declspec(dllexport) int run(Block *aBlock);
extern "C" __stdcall __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __stdcall __declspec(dllexport) int validate(Block *aBlock);

bool RotateRight(Graphics::TBitmap* picture);

#endif //_ROTATE_RIGHT_H_

