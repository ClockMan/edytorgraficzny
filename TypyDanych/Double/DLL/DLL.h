#ifndef DLLH
#define DLLH

#include <vcl.h>
#include <windows.h>
#include "SHOW.h"
#include "../../../Program/engine/TypeConfig.h"

extern "C"  __declspec(dllexport) TForm* __stdcall show(TComponent* owner, TypeConfig* aData);
extern "C"  __declspec(dllexport) bool __stdcall isValid(TypeConfig* aData);
extern "C"  __declspec(dllexport) AnsiString __stdcall getType();
#endif
