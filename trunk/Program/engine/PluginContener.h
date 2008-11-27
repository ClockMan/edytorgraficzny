#include <System.hpp>
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
		   vector<TypeDLL*> listOfType;
		   vector<FunctionDLL*> listOfFunction;
		public:

		~PluginContener();
		
		/**
		* Dodaje nowy typ (plugin)
		* @param aPath scie¿ka do pliku
		* @return poprawnoœæ wykonanej operacji
		*/
			bool addType(const AnsiString &aPath, const AnsiString &type);
		/**
		* Dodaje now¹ funkcjê (plugin)
		* @param aPath scie¿ka do pliku
		* @return poprawnoœæ wykonanej operacji
		*/
			bool addFunction(const AnsiString &aPath, const AnsiString &name);

			TypeDLL* getTypeDLL(const AnsiString &type);
			FunctionDLL* getFunctionDLL(const AnsiString &name);
};

#endif
