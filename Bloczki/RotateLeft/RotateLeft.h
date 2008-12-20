#ifndef _ROTATE_LEFT_H_
#define _ROTATE_LEFT_H_

#include "../../Program/engine/Block.h"

extern "C" __stdcall __declspec(dllexport) int run(Block *aBlock);
extern "C" __stdcall __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __stdcall __declspec(dllexport) int validate(Block *aBlock);

bool RotateLeft(Graphics::TBitmap* picture);

#endif //_ROTATE_LEFT_H_
 