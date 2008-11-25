#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockElement_h__
#define __BlockElement_h__

#include "BlockConfig.h"

class BlockElement
{
		private:
			string description;
			int errorCode;
			string errorDescription;
			PIWO::BlockConfig object;
			string name;

		public:
			BlockElement(string aName);
			string getDescription();
			int getErrorCode();
			string geErrorDescription();
			string getName();
			PIWO::BlockConfig getObject();
			bool setDescription(string aDescription);
			bool setErrorCode(int aError);
			bool setObject(PIWO::BlockConfig aData);
};


#endif
