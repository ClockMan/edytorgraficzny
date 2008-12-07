//---------------------------------------------------------------------------

#ifndef reflectionH
#define reflectionH

#include "../../Program/engine/Block.h"

//---------------------------------------------------------------------------
#ifdef BUILDING_DLL
#define DLL_FUNCTION __declspec(dllexport)
#else
#define DLL_FUNCTION __declspec(dllimport)
#endif // BUILDING_DLL

#ifdef __cplusplus
extern "C" DLL_FUNCTION int __stdcall run(Block*);
extern "C" DLL_FUNCTION bool __stdcall showConfig(TComponent*, Block*);
extern "C" DLL_FUNCTION int __stdcall validate(Block*);
#else
DLL_FUNCTION int __stdcall run(Block*);
DLL_FUNCTION bool __stdcall showConfig(TComponent*, Block*);
DLL_FUNCTION int __stdcall validate(Block*);
#endif // __cplusplus

bool ReflectionHorizontally(Graphics::TBitmap*);
bool ReflectionVertically(Graphics::TBitmap*);

#endif // reflectionH
