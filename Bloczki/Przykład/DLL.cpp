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
   //odpalamy okienko konfiguracyjne bloczka, konfiguracja powinna byc nieuzale�niona od wej��, mo�e mie� wp�yw na wyj�cia, po wykonaniu tej funkcji automatycznie zostanie wywo�ana funkcja validate.
   //wszystkie dane jakie chcemy przechowa� zapisujemy w aBlock->getConfig().
   //wszystkie funkcje jakie u�ywamy niepowinny odwo�ywa� si� do jakichkolwiek danych statycznych w DLL, po prostu dla wszystkich bloczk�w b�zie za�adowana tylko jedna instancja DLL.
   //je�li ta funkcja zwr�ci true, to b�zie to  oznacza�o �� zosta�y wporadzone zmiany, zwr�� false je�li �adne zmiany nie zosta�y wprowadzone, mo�esz is� pos�u�y� aBlock->getConfig()->isChanged()
   delete x;
   return true;
}

int validate(Block *aBlock)
{
   //funkcja sprawdza poprawno�� po��cze� z bloczkiem jak i konfiguracji. tzn
   //dodawa� nowe wejscia, dodawa� nowe wyj�cia, modyfikowa� ich stany, kody b��d�w, ..
   return 0;
}

int run(Block *aBlock)
{
	//funkcja wykonuje jak�� operacj�, najlepiej kod operacji przechowywa� w zewn�trznej bibliotece.
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
