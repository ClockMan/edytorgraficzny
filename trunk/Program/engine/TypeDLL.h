#include <System.hpp>
#include <vector>
#include <exception>
#include <vcl.h>
using namespace std;

#ifndef __TypeDLL_h__
#define __TypeDLL_h__

#include "TypeConfig.h"

/**
* Interfejs pozwalaj¹cy na ³¹dowanie i u¿ywanie biblioteki typu
* @author Piotr
* @date 2008.11.25
* @version 0.1
*/
typedef TForm* ( *TypeDLL_show )(TComponent*, TypeConfig*);
typedef bool ( *TypeDLL_isValid )(TypeConfig*);

class TypeDLL
{
		private:
			AnsiString type;
			HANDLE DLLHandle;
			TypeDLL_show fshow;
			TypeDLL_isValid fisValid;
		public:

		/**
		* Konstruktor
		* @param file sciezka do pliku
		* @param stype
		*/
			TypeDLL(const AnsiString file, const AnsiString stype);
		/**
		* Destruktor
		*/
			~TypeDLL();
		/**
		*
		* @param parent
		* @param aData
		* @return
		*/
			TForm* show(TComponent* parent, TypeConfig* aData);
		/**
		* Sprawdza poprawnoœæ danych.
		* @param aData dane.
		* @return poprawnoœæ wykonanej operacji
		*/
			bool isValid(TypeConfig *aData);
		/**
		* Pobiera typ.
		* @return typ.
		*/
			AnsiString& getType();

};

#endif
