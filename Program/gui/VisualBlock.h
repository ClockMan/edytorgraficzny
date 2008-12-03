#ifndef VisualBlockH
#define VisualBlockH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>

struct Position {
   TPoint xy;
   char direction; //0 - Left, 1 - Top, 2 - Right, 3 - Bottom
};

class VisualBlock : public TPanel
{
	private:
	protected:
	public:
		__fastcall VisualBlock(TComponent* Owner);
		Position __fastcall getInputPosition(BlockInput *object);
		Position __fastcall getOutputPosition(BlockOutput *object);
	__published:
};
#endif
