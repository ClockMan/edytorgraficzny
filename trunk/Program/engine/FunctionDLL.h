#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FunctionDLL_h__
#define __FunctionDLL_h__
#include "Block.h"
/**
 * BlockInput - Klasa pojemnik przechowujaca wejscia i wyjscia bloku
 * @author Piotr
 * @date 2008.11.25
 * @version 0.1
 */
class FunctionDLL
{
	public:
		/**
		 * Uruchamia funkcje bloczka.
		 * @param aBlock referencja do bloczka reprezentujacego funkjce.
		 * @return poprawnosc wykonanej operacji
		 */
		int run(Block &aBlock);
		/**
		 * Wyswietla w oknie parametry przesylane do bloku
		 * @param aBlock referencja do bloczka reprezentujacego funkjce.
		 * @return poprawnosc wykonanej operacji
		 */
		bool showConfig(Block &aBlock);
		/**
		 * Sprawdza poprawnosc konfiguracji bloczku
		 * @param aBlock referencja do bloczka reprezentujacego funkjce.
		 * @return poprawnosc wykonanej operacji
		 */
		int validate(Block &aBlock);
};

#endif
