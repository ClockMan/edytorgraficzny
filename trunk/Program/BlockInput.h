#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockInput_h__
#define __BlockInput_h__

#include "Block.h"
// #include "BlockElement.h"

namespace PIWO
{
	class Block;
	class BlockElement;
	class BlockInput;
}

namespace PIWO
{
	class BlockInput: public PIWO::BlockElement
	{
		private: string inputType;
		public: vector<string> allowedTypes;
		std::vector<PIWO::Block*> input;

		public: bool connect(string aName);

		public: bool disconnect();
	};
}

#endif
