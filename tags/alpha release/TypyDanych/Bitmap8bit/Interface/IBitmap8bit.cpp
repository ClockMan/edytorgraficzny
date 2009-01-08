#include "IBitmap8bit.h"

const Graphics::TBitmap& IBitmap8bit::getBitmap(TypeConfig *type)
{
   if (type->getName()!="Bitmap8bit") throw "To nie jest Bitmap8bit";;
   return (type->getBitmap("bitmapa"));
}

bool IBitmap8bit::setBitmap(TypeConfig *type, Graphics::TBitmap &bitmap)
{
   if (type->getName()!="Bitmap8bit") return false;
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf8bit;
   bmp->Width=bitmap.Width;
   bmp->Height=bitmap.Height;
   bmp->Canvas->Draw(0,0,&bitmap);
   type->setBitmap("bitmapa",*bmp);
   delete bmp;
   return true;
}

TypeConfig* IBitmap8bit::getNew()
{
   TypeConfig *z=new TypeConfig("Bitmap8bit");
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf8bit;
   z->addBitmap("bitmapa",*bmp);
   delete bmp;
   return z;
}
