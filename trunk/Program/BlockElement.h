#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockElement_h__
#define __BlockElement_h__

#include "BlockConfig.h"

namespace PIWO
{
	class BlockConfig;
	class BlockElement;
}

namespace PIWO
{
	class BlockElement
	{
		private: string description;
		private: int errorCode;
		private: string errorDescription;
		private: PIWO::BlockConfig object;
		private: string name;

		public:  BlockElement(string aName);

		public: string getDescription();

		public: int getErrorCode();

		public: string geErrorDescription();

		public: string getName();

		public: PIWO::BlockConfig getObject();

		public: bool setDescription(string aDescription);

		public: bool setErrorCode(int aError);

		public: bool setObject(PIWO::BlockConfig aData);
	};
}

#endif
