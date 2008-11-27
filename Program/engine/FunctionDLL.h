#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __FunctionDLL_h__
#define __FunctionDLL_h__

#include "Block.h"

typedef int ( *FunctionDLL_run )(Block*);
typedef bool ( *FunctionDLL_showConfig )(TComponent*, Block*);
typedef int ( *FunctionDLL_validate )(Block*);
/**
 * FunctionDLL - Klasa ladujaca DLL bloczka, uruchamiaj¹ca funkcje i zwalniaj¹ca go
 * @author Piotr
 * @date 2008.11.26
 * @version 0.1
 */
class FunctionDLL
{
	private:
		AnsiString name;
		HANDLE DLLHandle;
		FunctionDLL_run frun;
		FunctionDLL_validate fvalidate;
		FunctionDLL_showConfig fshowConfig;
	public:

		FunctionDLL(const AnsiString &file, const AnsiString &sname);
		~FunctionDLL();

		/**
		 * Uruchamia funkcje bloczka.
		 * @param aBlock wskaznik do bloczka reprezentujacego funkjce.
		 * @return poprawnosc wykonanej operacji
		 */
		int run(Block *aBlock);
		/**
		 * Wyswietla w oknie parametry przesylane do bloku
		 * @param owner wskaznik do okienka
		 * @param aBlock wskaznik do bloczka reprezentujacego funkjce.
		 * @return poprawnosc wykonanej operacji
		 */
		bool showConfig(TComponent *owner, Block *aBlock);
		/**
		 * Sprawdza poprawnosc konfiguracji bloczku
		 * @param aBlock wskaznik do bloczka reprezentujacego funkjce.
		 * @return poprawnosc wykonanej operacji
		 */
		int validate(Block *aBlock);

		AnsiString& getName();
};

#endif
