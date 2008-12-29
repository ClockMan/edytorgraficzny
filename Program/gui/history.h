//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef historyH
#define historyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
#include "VisualBlock.h"
#include "../engine/PluginContener.h"
#include <ImgList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <vector>

//---------------------------------------------------------------------------
class THistory : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TImageList *ImageList1;
	TPanel *Panel1;
	TTreeView *TreeView1;
	TPanel *Panel2;
	TBitBtn *BitBtn2;
	TLabel *Label1;
	void __fastcall TreeView1Deletion(TObject *Sender, TTreeNode *Node);
	void __fastcall BitBtn2Click(TObject *Sender);
	void __fastcall TreeView1Click(TObject *Sender);
private:
	vector<TForm*> windows;
	TFrame *showFrame;
	unsigned int count;
public:		// User declarations
	__fastcall THistory(TComponent* Owner);
	__fastcall ~THistory();

	VisualBlock *block;
	PluginContener *plugins;

	void refresh(BlockElement *toShow);
};
//---------------------------------------------------------------------------
#endif
