//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "SHOW.h"
#include "../../Program/engine/Block.h"
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused

USELIB("..\..\Lib\memmgr.lib");

extern "C" __declspec(dllexport) int run(Block *aBlock);
extern "C" __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __declspec(dllexport) int validate(Block *aBlock);

bool showConfig(TComponent *owner, Block *aBlock)
{
   TForm1 *x=new TForm1(owner);
   x->ShowModal();
   //odpalamy okienko konfiguracyjne bloczka, konfiguracja powinna byc nieuzale¿niona od wejœæ, mo¿e mieæ wp³yw na wyjœcia, po wykonaniu tej funkcji automatycznie zostanie wywo³ana funkcja validate.
   //wszystkie dane jakie chcemy przechowaæ zapisujemy w aBlock->getConfig().
   //wszystkie funkcje jakie u¿ywamy niepowinny odwo³ywaæ siê do jakichkolwiek danych statycznych w DLL, po prostu dla wszystkich bloczków bêzie za³adowana tylko jedna instancja DLL.
   //jeœli ta funkcja zwróci true, to bêzie to  oznacza³o ¿ê zosta³y wporadzone zmiany, zwróæ false jeœli ¿adne zmiany nie zosta³y wprowadzone, mo¿esz isê pos³u¿yæ aBlock->getConfig()->isChanged()
   delete x;
   return true;
}

int validate(Block *aBlock)
{
   //funkcja sprawdza poprawnoœæ po³¹czeñ z bloczkiem jak i konfiguracji. tzn
   //dodawaæ nowe wejscia, dodawañ nowe wyjœcia, modyfikowaæ ich stany, kody b³êdów, ..
   return 0;
}

int run(Block *aBlock)
{
	//funkcja wykonuje jak¹œ operacjê, najlepiej kod operacji przechowywaæ w zewnêtrznej bibliotece.
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
