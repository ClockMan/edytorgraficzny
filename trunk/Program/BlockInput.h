#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockInput_h__
#define __BlockInput_h__

#include "Block.h"
#include "BlockElement.h"

class BlockInput: public PIWO::BlockElement
{
		private:
				string inputType;
		public:
				vector<string> allowedTypes;
				bool connect(string aName);
				bool disconnect();
};

#endif
