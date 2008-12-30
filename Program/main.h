//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include "gui/PIWOEngine.h"
#include <Menus.hpp>
#include <ImgList.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *Plik1;
	TMenuItem *Edycja1;
	TMenuItem *Nowy1;
	TMenuItem *Otwrz1;
	TMenuItem *Zapisz1;
	TMenuItem *Zapiszjako1;
	TMenuItem *Exportujjakoobraz1;
	TMenuItem *Zamknij1;
	TMenuItem *Zakocz1;
	TMenuItem *Zaznaczwszystkiebloki1;
	TMenuItem *Odznaczwszystkiebloki1;
	TMenuItem *Odwrzaznaczenieblokw1;
	TMenuItem *Duplikujbloki1;
	TMenuItem *Usubloki1;
	TMenuItem *ObrazBMP1;
	TMenuItem *N1;
	TMenuItem *Zakocz2;
	TMenuItem *Usuzaznaczonebloki1;
	TMenuItem *Odznaczzaznaczonepoaczenie1;
	TMenuItem *Usuwszystkiepoczenia1;
	TMenuItem *Usuzaznaczonepoczenie1;
	TMenuItem *Pomoc1;
	TMenuItem *Instrukcjauytkoniwka1;
	TMenuItem *Dokumentacjatechniczna1;
	TMenuItem *Oautorach1;
	TMenuItem *Oprogramie1;
	TImageList *ImageList1;
	TStatusBar *StatusBar1;
	TMenuItem *Uruchom2;
	TMenuItem *Uruchomwszystko1;
	TMenuItem *Uruchom3;
	TMenuItem *Zresetujwszystkiepoczenia1;
	TMenuItem *Zresetujzaznaczonepoczenie1;
	TMenuItem *Widok1;
	TPanel *Panel1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TListView *ListView1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TImageList *ImageList2;
	TPopupMenu *PopupMenu1;
	TMenuItem *Wyczylogi1;
	TMenuItem *Zapiszdopliku1;
	TListView *ListView2;
	TListView *ListView3;
	TSaveDialog *SaveDialog1;
	TPopupMenu *PopupMenu2;
	TMenuItem *MenuItem1;
	TMenuItem *MenuItem2;
	TPopupMenu *PopupMenu3;
	TMenuItem *MenuItem3;
	TMenuItem *MenuItem4;
	TToolBar *ToolBar1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Zakocz2Click(TObject *Sender);
	void __fastcall Zaznaczwszystkiebloki1Click(TObject *Sender);
	void __fastcall Odznaczwszystkiebloki1Click(TObject *Sender);
	void __fastcall Odwrzaznaczenieblokw1Click(TObject *Sender);
	void __fastcall Usubloki1Click(TObject *Sender);
	void __fastcall Usuzaznaczonebloki1Click(TObject *Sender);
	void __fastcall Odznaczzaznaczonepoaczenie1Click(TObject *Sender);
	void __fastcall Usuwszystkiepoczenia1Click(TObject *Sender);
	void __fastcall Usuzaznaczonepoczenie1Click(TObject *Sender);
	void __fastcall Zresetujwszystkiepoczenia1Click(TObject *Sender);
	void __fastcall Zresetujzaznaczonepoczenie1Click(TObject *Sender);
	void __fastcall Uruchomwszystko1Click(TObject *Sender);
	void __fastcall Uruchom3Click(TObject *Sender);
	void __fastcall PageControl1Resize(TObject *Sender);
	void __fastcall Wyczylogi1Click(TObject *Sender);
	void __fastcall MenuItem1Click(TObject *Sender);
	void __fastcall MenuItem3Click(TObject *Sender);
	void __fastcall Zapiszdopliku1Click(TObject *Sender);
	void __fastcall MenuItem2Click(TObject *Sender);
	void __fastcall MenuItem4Click(TObject *Sender);

private:
	PIWOEngine *piwo;
	void  OnLoadProgress(void* Sender, int position, int max, AnsiString info, int id);
	void  OnFunctionAddClick(void* Sender);
	void OnLog(TObject* Sender, const AnsiString message);
public:
	PluginContener plugins;
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
