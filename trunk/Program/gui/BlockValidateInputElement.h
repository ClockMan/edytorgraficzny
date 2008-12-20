#ifndef BlockValidateInputElementH
#define BlockValidateInputElementH

#include "../engine/BlockInput.h"
#include "Connection.h"

class BlockValidateInputElement
{
	public:
	BlockInput* input;
	AnsiString errorDescription;
	int errorCode;
	Connection* connection;
};
#endif
