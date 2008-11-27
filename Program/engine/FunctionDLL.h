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
* FunctionDLL - Klasa �aduj�ca DLL bloczka, uruchamiaj�ca funkcje i zwalniaj�ca go
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
			* Uruchamia funkcj� bloczka.
			* @param aBlock wska�nik do bloczka reprezentuj�cego funkjc�.
			* @return poprawno�� wykonanej operacji
			*/
				int run(Block *aBlock);
			/**
			* Wy�wietla w oknie parametry przesy�ane do bloku
			* @param owner wska�nik do okienka
			* @param aBlock wska�nik do bloczka reprezentuj�cego funkjc�.
			* @return poprawno�� wykonanej operacji
			*/
				bool showConfig(TComponent *owner, Block *aBlock);
			/**
			* Sprawdza poprawno�� konfiguracji bloczku
			* @param aBlock wska�nik do bloczka reprezentuj�cego funkjc�.
			* @return poprawno�� wykonanej operacji
			*/
				int validate(Block *aBlock);

				AnsiString& getName();
};

#endif
