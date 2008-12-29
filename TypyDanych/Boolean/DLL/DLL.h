#ifndef DLLH
#define DLLH

#include <vcl.h>
#include <windows.h>
#include "SHOW.h"
#include "../../../Program/engine/TypeConfig.h"

extern "C"  __declspec(dllexport) TFrame* __stdcall show(TWinControl* owner, TypeConfig* aData);
extern "C"  __declspec(dllexport) bool __stdcall isValid(TypeConfig* aData);
extern "C"  __declspec(dllexport) AnsiString __stdcall getType();
#endif
