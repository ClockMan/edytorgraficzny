//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "binarization.h"
//#include "configWindow.h"

#include "../../TypyDanych/Bitmap1bit/Interface/IBitmap1bit.h"
#include "../../TypyDanych/Bitmap4bit/Interface/IBitmap4bit.h"
#include "../../TypyDanych/Bitmap8bit/Interface/IBitmap8bit.h"
#include "../../TypyDanych/Bitmap16bit/Interface/IBitmap16bit.h"
#include "../../TypyDanych/Bitmap24bit/Interface/IBitmap24bit.h"
#include "../../TypyDanych/Bitmap32bit/Interface/IBitmap32bit.h"

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
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}
//---------------------------------------------------------------------------
