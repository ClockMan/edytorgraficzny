#include <System.hpp>
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
		vector<TypeDLL*> listOfType;
		vector<FunctionDLL*> listOfFunction;
	public:
		/**
		 * Destruktor
		 */
		~PluginContener();

		/**
		 * Dodaje nowy typ (plugin)
		 * @param aPath sciezka do pliku
		 * @return poprawnosc wykonanej operacji
		 */
		bool addType(const AnsiString &aPath, const AnsiString &type);
		/**
		 * Dodaje nowa funkcje (plugin)
		 * @param aPath sciezka do pliku
		 * @return poprawnosc wykonanej operacji
		 */
		bool addFunction(const AnsiString &aPath, const AnsiString &name);
		/**
		 * funkcja umozliwiajaca pobranie obiektu opisujacego TypeDll znajac jego nazwe
		 * @param type nazwa typu
		 * @return wskaznik do obiektu TypeDll
		 */	
		TypeDLL* getTypeDLL(const AnsiString &type);
		/**
		 * funkcja umozliwiajaca pobranie obiektu opisujacego FunctionDLL znajac jego nazwe
		 * @param name nazwa funkcji
		 * @return wskaznik do obiektu FunctionDLL
		 */
		FunctionDLL* getFunctionDLL(const AnsiString &name);
};

#endif
