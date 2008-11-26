#include <vector>
#include <System.hpp>
#include <exception>
#include <Graphics.hpp>
using namespace std;

#ifndef __IBitmap1bit_h__
#define __IBitmap1bit_h__

#include "../../../Program/engine/TypeConfig.h"

class IBitmap1bit
{
	public:
			static Graphics::TBitmap* getBitmap(TypeConfig *type);
			static bool setBitmap(TypeConfig *type, Graphics::TBitmap &bitmap);
			static TypeConfig* getNew();
};


#endif
