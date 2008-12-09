#include <vector>
#include <System.hpp>
#include <exception>
#include <Graphics.hpp>
using namespace std;

#ifndef __IBitmap24bit_h__
#define __IBitmap24bit_h__

#include "../../../Program/engine/TypeConfig.h"

class IBitmap24bit
{
	public:
			static const Graphics::TBitmap& getBitmap(TypeConfig *type);
			static bool setBitmap(TypeConfig *type, Graphics::TBitmap &bitmap);
			static TypeConfig* getNew();
};


#endif
