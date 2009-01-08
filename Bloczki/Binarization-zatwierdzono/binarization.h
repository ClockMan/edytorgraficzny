//---------------------------------------------------------------------------
#ifndef binarizationH
#define binarizationH 

#include "../../Program/engine/Block.h" 
#include "../function.hpp" 

extern "C" __stdcall __declspec(dllexport) int run(Block *aBlock); 
extern "C" __stdcall __declspec(dllexport) bool showConfig(TComponent *owner, Block *aBlock); 
extern "C" __stdcall __declspec(dllexport) int validate(Block *aBlock); 

//--------------------------------------------------------------------------- 
#endif//binarizationH 

