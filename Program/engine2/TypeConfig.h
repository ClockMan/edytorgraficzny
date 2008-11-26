#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __TypeConfig_h__
#define __TypeConfig_h__

#include "BlockConfig.h"

class TypeConfig: public BlockConfig
{
		protected:
				 AnsiString nazwa;
		public:
				 TypeConfig(const AnsiString aName);
				 TypeConfig(TypeConfig &kopia);
				 TypeConfig(TStream &stream);
				 ~TypeConfig();
				 bool saveToStream(TStream &aWhere);
				 bool loadFromStream(TStream &aFrom);
				 AnsiString& getName();
};

#endif
