#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockElement_h__
#define __BlockElement_h__

#include "TypeConfig.h"

class BlockElement
{
		protected:
			AnsiString description;
			int errorCode;
			AnsiString errorDescription;
			TypeConfig *object;
			AnsiString name;

		public:
			BlockElement(const AnsiString aName);
			BlockElement(BlockElement &block);
			~BlockElement();

			AnsiString& getDescription();
			int getErrorCode();
			AnsiString& geErrorDescription();
			AnsiString& getName();
			TypeConfig* getObject();
			void setDescription(const AnsiString aDescription);
			void setErrorDescription(const AnsiString aErrorDescription);
			void setErrorCode(int aError);
			void setObject(TypeConfig &aData);
};


#endif
