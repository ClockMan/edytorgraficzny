#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __PluginContener_h__
#define __PluginContener_h__

#include "TypeDLL.h"
#include "FunctionDLL.h"
/**
 * Item - Klasa pojemnik przechowujaca pluginy
 * @author Piotr
 * @date 2008.11.25
 * @version 0.1
 */

class PluginContener
{
	private:
		vector<PIWO::TypeDLL> listOfType;
		vector<PIWO::FunctionDLL> listOfFunction;

	public:
		/**
		 * Dodaje nowy typ (plugin)
		 * @param aPath sciezka do pliku
		 * @return poprawnosc wykonanej operacji
		 */
		bool addType(string aPath);
		/**
		 * Dodaje nowa funkcje (plugin)
		 * @param aPath sciezka do pliku
		 * @return poprawnosc wykonanej operacji
		 */
		bool addFunction(string aPath);
};

#endif
