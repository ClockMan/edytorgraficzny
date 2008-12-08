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
	
	BlockHistoryInputElement();
	~BlockHistoryInputElement();

	void setData(TYpeConfig &d);
	TypeConfig* getData();
};



#endif
