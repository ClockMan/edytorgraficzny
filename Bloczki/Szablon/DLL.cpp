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

#pragma link "MEMMGR.LIB"

extern "C" __stdcall  __declspec(dllexport) int run(Block *aBlock);
extern "C" __stdcall  __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock);
extern "C" __stdcall  __declspec(dllexport) int validate(Block *aBlock);

bool __stdcall  showConfig(TComponent *owner, Block *aBlock)
{ //
  // TForm1 *x=new TForm1(owner);
  // x->block=aBlock;
   //x->ShowModal();
   //odpalamy okienko konfiguracyjne bloczka, konfiguracja powinna byc nieuzale¿niona od wejœæ, mo¿e mieæ wp³yw na wyjœcia, po wykonaniu tej funkcji automatycznie zostanie wywo³ana funkcja validate.
   //wszystkie dane jakie chcemy przechowaæ zapisujemy w aBlock->getConfig().
   //wszystkie funkcje jakie u¿ywamy niepowinny odwo³ywaæ siê do jakichkolwiek danych statycznych w DLL, po prostu dla wszystkich bloczków bêzie za³adowana tylko jedna instancja DLL.
   //jeœli ta funkcja zwróci true, to bêzie to  oznacza³o ¿ê zosta³y wporadzone zmiany, zwróæ false jeœli ¿adne zmiany nie zosta³y wprowadzone, mo¿esz isê pos³u¿yæ aBlock->getConfig()->isChanged()
 //  delete x;
   return true;
}

int __stdcall  validate(Block *aBlock)
{
   //funkcja sprawdza poprawnoœæ po³¹czeñ z bloczkiem jak i konfiguracji. tzn
   //dodawaæ nowe wejscia, dodawañ nowe wyjœcia, modyfikowaæ ich stany, kody b³êdów, ..
   //INICJALIZOWAC TU TEZ KONFIGURACJE
 /*  if (aBlock.input.size()==0)
   {
	  BlockInput x1("wejscie1");
	  x1.allowedTypes.push_back("Bitmap16bit");
	  x1.allowedTypes.push_back("Bitmap24bit");   	
	  x1.setDescription("Hujowe wejscie 1");
	  x1.setErrorCode(1);
	  aBlock.input.push_back(x1);
	  
	  BlockInput x2("wejscie2");
	  x2.allowedTypes.push_back("Bitmap16bit");
	  x2.allowedTypes.push_back("Bitmap24bit");   	
	  x2.setDescription("Hujowe wejscie 2");
	  x2.setErrorCode(1);
	  aBlock.input.push_back(x2);
	  
	  BlockOutput x("wyjscie");
	  x.setOutputType("Btmap16bit");
	  x.setDescription("Hujowe wyjscie");
	  x.setErrorCode(2);
	  aBlock.output.push_back(x);
   }	
   else
   {
   	 if (aBlock.input[0].getConnectionType().isEmpty())
   	    aBlock.input[0].setErrorCode(1);
   	    
   	 if (aBlock.input[1].getConnectionType().isEmpty())
   	    aBlock.input[1].setErrorCode(1);
   	    
   	 if ((aBlock.input[0].getConnectionType().isEmpty())||  (aBlock.input[1].getConnectionType().isEmpty()))
   	  aBlock.output[0].setErrorCode(2);
   	  
   	 if ((aBlock.input[0].getConnectionType()=="Bitmap16bit")||  (aBlock.input[1].getConnectionType()=="Bitmap16bit"))
   	  aBlock.output[0].setOutputType("Btmap16bit");
   	  else
   	  aBlock.output[0].setOutputType("Btmap24bit");
	}
		*/
   
   return 0;
}

int __stdcall  run(Block *aBlock)
{
	//funkcja wykonuje jak¹œ operacjê, najlepiej kod operacji przechowywaæ w zewnêtrznej bibliotece.
   /*	if (aBlock.input.Size()!=2) return 2;
	if (aBlock.input[0].getConnectedType().isEmpty()) return 3;
	if (aBlock.input[1].getConnectedType().isEmpty()) return 3;
	
	int c=aBlock.getConfig()->getInt("string1");
	
	TBitmap x1=IBitmap16bit::getBitmap(aBlock.input[0]->getObject());
	TBitmap x2=IBitmap16bit::getBitmap(aBlock.input[1]->getObject());
	
	TBitmap x;*/
	//dodawnaie bitmapy x1+x2==x
	 /*
	TypeConfig *kopia=IBitmap16bit::getNew();
	IBitmap16bit::setBitmap(kopia, x);
	aBlock.ouput[0].setOutput(*kopia);    */
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
