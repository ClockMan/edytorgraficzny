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
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *Plik1;
	TMenuItem *Edycja1;
	TMenuItem *Uruchom1;
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
	TMenuItem *Usu1;
	TMenuItem *Blok1;
	TMenuItem *Duplikuj1;
	TMenuItem *Usu2;
	TMenuItem *Edytujkonfiguracje1;
	TMenuItem *Wejcia1;
	TMenuItem *Wyjcia1;
	TMenuItem *Pomoc1;
	TMenuItem *Instrukcjauytkoniwka1;
	TMenuItem *Dokumentacjatechniczna1;
	TMenuItem *Oautorach1;
	TMenuItem *Oprogramie1;
	TImageList *ImageList1;
	void __fastcall FormCreate(TObject *Sender);

private:
	PIWOEngine *piwo;
	void  OnLoadProgress(void* Sender, int position, int max, AnsiString info, int id);
public:
	PluginContener plugins;

	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
