#ifndef OpenImageH
#define OpenImageH

#include <Graphics.hpp>
#include "FreeImage.h"

#include "../../Program/engine/Block.h"
#include "../../TypyDanych/Bitmap1bit/Interface/IBitmap1bit.h"
#include "../../TypyDanych/Bitmap4bit/Interface/IBitmap4bit.h"
#include "../../TypyDanych/Bitmap8bit/Interface/IBitmap8bit.h"
#include "../../TypyDanych/Bitmap16bit/Interface/IBitmap16bit.h"
#include "../../TypyDanych/Bitmap24bit/Interface/IBitmap24bit.h"
#include "../../TypyDanych/Bitmap32bit/Interface/IBitmap32bit.h"

extern "C" __declspec(dllexport) int run(Block *aBlock);
extern "C" __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __declspec(dllexport) int validate(Block *aBlock);

bool OpenImage(Graphics::TBitmap*, const AnsiString&);
void LoadImage(FIBITMAP*, Graphics::TBitmap*);

#endif // OpenImageH
