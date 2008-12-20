#ifndef BlockValidateOutputElementH
#define BlockValidateOutputElementH

#include "../engine/BlockOutput.h"
#include "Connection.h"
#include <vector>

class BlockValidateOutputElement
{
	public:
	BlockOutput* output;
	AnsiString type;
	AnsiString errorDescription;
	int errorCode;
	vector<Connection*> connections;
};
#endif                                       
