#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FunctionDLL_h__
#define __FunctionDLL_h__

#include "Block.h"
/**
* BlockInput - Klasa pojemnik przechowuj�ca wej�cia i wyjscia bloku
* @author Piotr
* @date 2008.11.25
* @version 0.1
*/
class FunctionDLL
{
		public:
			/**
			* Uruchamia funkcj� bloczka.
			* @param aBlock referencja do bloczka reprezentuj�cego funkjc�.
			* @return poprawno�� wykonanej operacji
			*/
				int run(Block &aBlock);
			/**
			* Wy�wietla w oknie parametry przesy�ane do bloku
			* @@param aBlock referencja do bloczka reprezentuj�cego funkjc�.
			* @return poprawno�� wykonanej operacji
			*/
				bool showConfig(Block &aBlock);
			/**
			* Sprawdza poprawno�� konfiguracji bloczku
			* @@param aBlock referencja do bloczka reprezentuj�cego funkjc�.
			* @return poprawno�� wykonanej operacji
			*/
				int validate(Block &aBlock);
};

#endif
