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
#include "../brige/PluginContener.h"
#include <ImgList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <vector>
/**
 * Klasa jest oknem histori
 */
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
	void __fastcall CreateParams(Controls::TCreateParams &Params);
private:
	vector<TForm*> windows;
	TFrame *showFrame;
	unsigned int count;
public:		// User declarations
	/**
	 * Konstruktor
	 * @param Owner wskaznik do klasy bedacej wlascicielem dla tej
	 */
	__fastcall THistory(TComponent* Owner);
	/**
	 * Destruktor
	 */
	__fastcall ~THistory();
	/**
	 * Wskaznik do wizualnego bloku, musi byc ustawiony przed refresh
	 */
	VisualBlock *block;
	/**
	 * Wskaznik do kontenera pluginow, musi byc ustawione przed refresh
	 */
	PluginContener *plugins;
	/**
	 * Metoda wyswietla liste historii, i pokazuje ostatnia historie dla parametru toShow
	 * @param toShow wskaznik do niskopoziomowego wejscia/wyjscia bloku, jesli NULL to przy wywolaniu zadne "okno" nie zostanie pokazane
	 */
	void refresh(BlockElement *toShow);
};

#endif
