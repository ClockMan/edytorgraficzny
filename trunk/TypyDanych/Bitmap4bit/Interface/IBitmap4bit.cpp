#include "IBitmap4bit.h"

Graphics::TBitmap* IBitmap4bit::getBitmap(TypeConfig *type)
{
   if (type->getName()!="Bitmap4bit") return NULL;
   return &(type->getBitmap("bitmapa"));
}

bool IBitmap4bit::setBitmap(TypeConfig *type, Graphics::TBitmap &bitmap)
{
   if (type->getName()!="Bitmap4bit") return false;
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf4bit;
   bmp->Width=bitmap.Width;
   bmp->Height=bitmap.Height;
   bmp->Canvas->Draw(0,0,&bitmap);
   type->setBitmap("bitmapa",*bmp);
   delete bmp;
   return true;
}

TypeConfig* IBitmap4bit::getNew()
{
   TypeConfig *z=new TypeConfig("Bitmap4bit");
   Graphics::TBitmap *bmp=new Graphics::TBitmap();
   bmp->PixelFormat=pf4bit;
   z->addBitmap("bitmapa",*bmp);
   delete bmp;
   return z;
}
