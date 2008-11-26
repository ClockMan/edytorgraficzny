#include "IBitmap24bit.h"

Graphics::TBitmap* IBitmap24bit::getBitmap(TypeConfig *type)
{
   if (type->getName()!="Bitmap24bit") return NULL;
   return &(type->getBitmap("bitmapa"));
}

bool IBitmap24bit::setBitmap(TypeConfig *type, Graphics::TBitmap &bitmap)
{
   if (type->getName()!="Bitmap24bit") return false;
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf24bit;
   bmp->Width=bitmap.Width;
   bmp->Height=bitmap.Height;
   bmp->Canvas->Draw(0,0,&bitmap);
   type->setBitmap("bitmapa",*bmp);
   delete bmp;
   return true;
}

TypeConfig* IBitmap24bit::getNew()
{
   TypeConfig *z=new TypeConfig("Bitmap24bit");
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf24bit;
   z->addBitmap("bitmapa",*bmp);
   delete bmp;
   return z;
}
