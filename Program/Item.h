#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __Item_h__
#define __Item_h__

#include "BlockConfig.h"

class Item
{
		private: string name;
				 void* wsk;
				 string type;

		public: string getName();
				void getObject();
				string getType();
				Item(string aName, void* aObiekt, string aTyp);
};


#endif
