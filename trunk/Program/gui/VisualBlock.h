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

#define PIWOMAINCLASSTYPE TScrollBox

struct Position {
   TPoint xy;
   char direction; //0 - Left, 1 - Top, 2 - Right, 3 - Bottom, 4 - nie znaleüiono
};

typedef vector<BlockHistory*> vectorBlockHistory;
typedef void (__closure *VisualBlock_FunctionI )(VisualInput*,  TObject*);
typedef void (__closure *VisualBlock_FunctionO )(VisualOutput*, TObject*);
typedef void (__closure *VisualBlock_FunctionHI )(VisualInput*, vectorBlockHistory*);
typedef void (__closure *VisualBlock_FunctionHO )(VisualOutput*, vectorBlockHistory*);
typedef void (__closure *VisualBlock_FunctionMove )(TObject*, bool, int, int);

class VisualBlock : public TPanel
{
	private:
		TSpeedButton *configButton;
		TLabel *title;
		TPanel *status;
		vector<VisualInput*> leftInput;
		vector<VisualInput*> topInput;
		vector<VisualOutput*> rightOutput;
		vector<VisualOutput*> bottomOutput;
		vectorBlockHistory history;
		bool selected;
		bool moving;
		bool button;
		TPoint oldPoint;
		void __fastcall SpeedButtonClick(TObject *Sender);
		void __fastcall InputSelected(TObject *Sender);
		void __fastcall OutputSelected(TObject *Sender);
		void InputShowHistory(TObject *Sender);
		void OutputShowHistory(TObject *Sender);
		void __fastcall BlockClick(TObject *Sender);
		void __fastcall BlockMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall BlockMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall BlockMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
		void resizeAll();
	public:
        Block block;
		AnsiString nameOfBlock;
		int		   numberOfBlock;
		bool runned;

		VisualFunction OnConfigClick;
		VisualBlock_FunctionI OnVisualInputSelected;
		VisualBlock_FunctionO OnVisualOutputSelected;
		VisualBlock_FunctionHI OnVInputHistory;
		VisualBlock_FunctionHO OnVOutputHistory;
		VisualBlock_FunctionMove OnBlockMove;
		VisualFunction OnUnselect;
		VisualFunction OnSelect;
		VisualFunction OnSelectAdd;

		__fastcall VisualBlock(TComponent* Owner);
		__fastcall ~VisualBlock();
		Position getInputPosition(BlockInput* object);
		Position getOutputPosition(BlockOutput* object);
		bool setConfigButtonGlyph(Graphics::TBitmap *bmp);
		void setTitle(const AnsiString &s);
		AnsiString getTitle();
		bool updateVisualComponents();
		bool updateHistory();
		void setSelected(bool status);
		bool isSelected();
		void setStatusColor(TColor cl);
};

bool ctrlDown();
bool altDown();
#endif
