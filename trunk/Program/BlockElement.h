#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockElement_h__
#define __BlockElement_h__

#include "BlockConfig.h"

class BlockElement
{
		protected:
			AnsiString description;
			int errorCode;
			AnsiString errorDescription;
			BlockConfig *object;
			AnsiString name;

		public:
			BlockElement(const AnsiString aName);
			BlockElement(BlockElement &block);
			~BlockElement();

			AnsiString& getDescription();
			int getErrorCode();
			AnsiString& geErrorDescription();
			AnsiString& getName();
			BlockConfig* getObject();
			void setDescription(const AnsiString aDescription);
			void setErrorDescription(const AnsiString aErrorDescription);
			void setErrorCode(int aError);
			void setObject(BlockConfig &aData);
};


#endif
