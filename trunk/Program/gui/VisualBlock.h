#ifndef VisualBlockH
#define VisualBlockH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "../engine/BlockInput.h";
#include "../engine/BlockOutput.h";
#include "../engine/Block.h";
#include "VisualInput.h";
#include "VisualOutput.h";
#include "BlockHistory.h";

struct Position {
   TPoint xy;
   char direction; //0 - Left, 1 - Top, 2 - Right, 3 - Bottom, 4 - nie znaleŸiono
};


typedef bool ( *VisualBlock_FunctionI )(VisualInput*,  TObject*);
typedef bool ( *VisualBlock_FunctionO )(VisualOutput*, TObject*);
typedef bool ( *VisualBlock_FunctionHI )(VisualInput*, vector<BlockHistory*>*);
typedef bool ( *VisualBlock_FunctionHO )(VisualOutput*, vector<BlockHistory*>*);

class VisualBlock : public TPanel
{
	private:
		Block block;
		TSpeedButton *configButton;
		TLabel *title;
		vector<VisualInput*> leftInput;
		vector<VisualInput*> topInput;
		vector<VisualOutput*> rightOutput;
		vector<VisualOutput*> bottomOutput;
		vector<BlockHistory*> history;
		void __fastcall SpeedButtonClick(TObject *Sender);
		void __fastcall InputSelected(TObject *Sender);
		void __fastcall OutputSelected(TObject *Sender);
		void __fastcall InputShowHistory(TObject *Sender);
		void __fastcall OutputShowHistory(TObject *Sender);
		void resizeAll();
	public:
		Classes::TNotifyEvent OnConfigClick;
		VisualBlock_FunctionI OnVisualInputSelected;
		VisualBlock_FunctionO OnVisualOutputSelected;
		VisualBlock_FunctionHI OnVInputHistory;
		VisualBlock_FunctionHO OnVOutputHistory;

		__fastcall VisualBlock(TComponent* Owner);
		__fastcall ~VisualBlock();
		Position getInputPosition(BlockInput* object);
		Position getOutputPosition(BlockOutput* object);
		bool setConfigButtonGlyph(AnsiString file);
		void setTitle(AnsiString &s);
		AnsiString getTitle();
		bool updateVisualComponents();
        //@TODO przenoszenie, zaznaczanie, usuwanie, odznaczanie, anulowanie zaznaczen - bloczka, bloczków
};
#endif
