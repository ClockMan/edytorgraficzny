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
	TMemo *Memo1;
	TStatusBar *StatusBar1;
	TMenuItem *Uruchom2;
	TMenuItem *Uruchomwszystko1;
	TMenuItem *Uruchom3;
	TMenuItem *Sprawdpoprawno1;
	TMenuItem *Zresetujwszystkiepoczenia1;
	TMenuItem *Zresetujzaznaczonepoczenie1;
	TMenuItem *Widok1;
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
