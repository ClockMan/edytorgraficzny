#include "IBitmap1bit.h"

const Graphics::TBitmap& IBitmap1bit::getBitmap(TypeConfig *type)
{
   if (type->getName()!="Bitmap1bit") throw "To nie jest Bitmap1bit";
   return type->getBitmap("bitmapa");
}

bool IBitmap1bit::setBitmap(TypeConfig *type, Graphics::TBitmap &bitmap)
{
   if (type->getName()!="Bitmap1bit") return false;
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf1bit;
   bmp->Width=bitmap.Width;
   bmp->Height=bitmap.Height;
   bmp->Canvas->Draw(0,0,&bitmap);
   type->setBitmap("bitmapa",*bmp);
   delete bmp;
   return true;
}

TypeConfig* IBitmap1bit::getNew()
{
   TypeConfig *z=new TypeConfig("Bitmap1bit");
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf1bit;
   z->addBitmap("bitmapa",*bmp);
   delete bmp;
   return z;
}
