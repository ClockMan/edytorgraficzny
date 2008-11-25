#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __TypeConfig_h__
#define __TypeConfig_h__

#include "BlockConfig.h"

class TypeConfig: public PIWO::BlockConfig
{
		private: string name;
		public:  TypeConfig(string aName);
				 bool saveToStream(TStream aWhere);
				 bool loadFromStream(TStream aFrom);
				 string getName();
};

#endif
