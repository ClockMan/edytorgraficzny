#include <vector>
#include <System.hpp>
#include <exception>
#include <Graphics.hpp>
using namespace std;

#ifndef __IBitmap8bit_h__
#define __IBitmap8bit_h__

#include "../../../Program/engine/TypeConfig.h"

class IBitmap8bit
{
	public:
			static const Graphics::TBitmap& getBitmap(TypeConfig *type);
			static bool setBitmap(TypeConfig *type, Graphics::TBitmap &bitmap);
			static TypeConfig* getNew();
};


#endif
