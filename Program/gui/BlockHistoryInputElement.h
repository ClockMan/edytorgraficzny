#ifndef BlockHistoryInputElementH
#define BlockHistoryInputElementH

#include "../engine/BlockInput.h"
#include "../engine/TypeConfig.h"

class BlockHistoryInputElement
{
     private:
	TypeConfig* data;
     public:
	BlockInput* input;

	void setData(TypeConfig &d);
	TypeConfig* getData();

	BlockHistoryInputElement();
	~BlockHistoryInputElement();
};



#endif
