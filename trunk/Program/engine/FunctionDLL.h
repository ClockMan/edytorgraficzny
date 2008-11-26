#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FunctionDLL_h__
#define __FunctionDLL_h__

#include "Block.h"
/**
* BlockInput - Klasa pojemnik przechowuj¹ca wejœcia i wyjscia bloku
* @author Piotr
* @date 2008.11.25
* @version 0.1
*/
class FunctionDLL
{
		public:
			/**
			* Uruchamia funkcjê bloczka.
			* @param aBlock referencja do bloczka reprezentuj¹cego funkjcê.
			* @return poprawnoœæ wykonanej operacji
			*/
				int run(Block &aBlock);
			/**
			* Wyœwietla w oknie parametry przesy³ane do bloku
			* @@param aBlock referencja do bloczka reprezentuj¹cego funkjcê.
			* @return poprawnoœæ wykonanej operacji
			*/
				bool showConfig(Block &aBlock);
			/**
			* Sprawdza poprawnoœæ konfiguracji bloczku
			* @@param aBlock referencja do bloczka reprezentuj¹cego funkjcê.
			* @return poprawnoœæ wykonanej operacji
			*/
				int validate(Block &aBlock);
};

#endif
