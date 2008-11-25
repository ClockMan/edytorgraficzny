#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __TypeConfig_h__
#define __TypeConfig_h__

// #include "BlockConfig.h"

namespace PIWO
{
	class BlockConfig;
	class TypeConfig;
}

namespace PIWO
{
	class TypeConfig: public PIWO::BlockConfig
	{
		private: string name;

		public:  TypeConfig(string aName);

		public: bool saveToStream(TStream aWhere);

		public: bool loadFromStream(TStream aFrom);

		public: string getName();
	};
}

#endif
