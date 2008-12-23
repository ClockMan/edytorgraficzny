#ifndef _MOTIONBLUR_H_
#define _MOTIONBLUR_H_

#include "../../Program/engine/Block.h"

extern "C" __stdcall __declspec(dllexport) int run(Block *aBlock);
extern "C" __stdcall __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __stdcall __declspec(dllexport) int validate(Block *aBlock);

bool MotionBlur(Graphics::TBitmap* picture);

#endif //_MOTIONBLUR_H_

