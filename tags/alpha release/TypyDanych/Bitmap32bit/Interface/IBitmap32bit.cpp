#include "IBitmap32bit.h"

const Graphics::TBitmap& IBitmap32bit::getBitmap(TypeConfig *type)
{
   if (type->getName()!="Bitmap32bit") throw "To nie jest Bitmap32bit";;
   return (type->getBitmap("bitmapa"));
}

bool IBitmap32bit::setBitmap(TypeConfig *type, Graphics::TBitmap &bitmap)
{
   if (type->getName()!="Bitmap32bit") return false;
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf32bit;
   bmp->Width=bitmap.Width;
   bmp->Height=bitmap.Height;
   bmp->Canvas->Draw(0,0,&bitmap);
   type->setBitmap("bitmapa",*bmp);
   delete bmp;
   return true;
}

TypeConfig* IBitmap32bit::getNew()
{
   TypeConfig *z=new TypeConfig("Bitmap32bit");
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf32bit;
   z->addBitmap("bitmapa",*bmp);
   delete bmp;
   return z;
}
