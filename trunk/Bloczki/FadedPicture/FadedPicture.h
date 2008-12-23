#ifndef _FADEDPICTURE_H_
#define _FADEDPICTURE_H_

#include "../../Program/engine/Block.h"

extern "C" __stdcall __declspec(dllexport) int run(Block *aBlock);
extern "C" __stdcall __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __stdcall __declspec(dllexport) int validate(Block *aBlock);

bool FadedPicture(Graphics::TBitmap* picture);

#endif //_FADEDPICTURE_H_

