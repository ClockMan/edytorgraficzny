#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __Item_h__
#define __Item_h__

#include "BlockConfig.h"

namespace PIWO
{
	class BlockConfig;
	class Item;
}

namespace PIWO
{
	class Item
	{
		private: string name;
		private: string* wsk;
		private: string type;
		std::vector<PIWO::BlockConfig*> map;

		public: string getName();

		public: void getObject();

		public: string getType();

		public:  Item(string aName, string* aObiekt, string aTyp);
	};
}

#endif
