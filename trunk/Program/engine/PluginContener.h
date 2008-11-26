#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __PluginContener_h__
#define __PluginContener_h__

#include "TypeDLL.h"
#include "FunctionDLL.h"

/**
* Item - Klasa pojemnik przechowuj¹ca pluginy
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
		* @param aPath scie¿ka do pliku
		* @return poprawnoœæ wykonanej operacji
		*/
			bool addType(string aPath);
		/**
		* Dodaje now¹ funkcjê (plugin)
		* @param aPath scie¿ka do pliku
		* @return poprawnoœæ wykonanej operacji
		*/
			bool addFunction(string aPath);
};

#endif
