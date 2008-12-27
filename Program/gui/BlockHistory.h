#ifndef BlockHistoryH
#define BlockHistoryH

#include "BlockHistoryOutputElement.h"
#include "BlockHistoryInputElement.h"
#include <vector>

class BlockHistory
{
	 public:
	  vector<BlockHistoryInputElement*> leftInput;
	  vector<BlockHistoryInputElement*> topInput;
	  vector<BlockHistoryOutputElement*> rightOutput;
	  vector<BlockHistoryOutputElement*> bottomOutput;

	 unsigned int configRevision;

	BlockHistory();
	~BlockHistory();
};

#endif
