#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockInput_h__
#define __BlockInput_h__

#include "BlockElement.h"

class BlockInput: public BlockElement
{
		public:
				AnsiString inputType;
		public:
				BlockInput(const AnsiString aName);
				BlockInput(BlockInput &kopia);
				~BlockInput();

				vector<AnsiString> allowedTypes;
				bool connect(const AnsiString aName);
				AnsiString& getConnectedType();
				void disconnect();
};

#endif
