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
	TMenuItem *Odznaczpoczenie1;
	TMenuItem *Duplikujbloki1;
	TMenuItem *Usubloki1;
	TMenuItem *Usupoczenie1;
	void __fastcall FormCreate(TObject *Sender);

private:
	PIWOEngine *piwo;
	int SearchDirectory(std::vector<AnsiString> &refvecFiles,
					const AnsiString        &refcstrRootDirectory,
					const AnsiString        &refcstrExtension,
					bool                     bSearchSubdirectories = true);
public:
    PluginContener plugins;
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
