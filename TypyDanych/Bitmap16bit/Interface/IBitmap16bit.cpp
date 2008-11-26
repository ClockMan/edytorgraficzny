#include "IBitmap16bit.h"

Graphics::TBitmap* IBitmap16bit::getBitmap(TypeConfig *type)
{
   if (type->getName()!="Bitmap16bit") return NULL;
   return &(type->getBitmap("bitmapa"));
}

bool IBitmap16bit::setBitmap(TypeConfig *type, Graphics::TBitmap &bitmap)
{
   if (type->getName()!="Bitmap16bit") return false;
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf16bit;
   bmp->Width=bitmap.Width;
   bmp->Height=bitmap.Height;
   bmp->Canvas->Draw(0,0,&bitmap);
   type->setBitmap("bitmapa",*bmp);
   delete bmp;
   return true;
}

TypeConfig* IBitmap16bit::getNew()
{
   TypeConfig *z=new TypeConfig("Bitmap16bit");
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf16bit;
   z->addBitmap("bitmapa",*bmp);
   delete bmp;
   return z;
}
