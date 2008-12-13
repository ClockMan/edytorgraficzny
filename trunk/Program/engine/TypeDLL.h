#include <System.hpp>
#include <vector>
#include <exception>
#include <vcl.h>
using namespace std;

#ifndef __TypeDLL_h__
#define __TypeDLL_h__

#include "TypeConfig.h"

typedef TForm* ( *TypeDLL_show )(TComponent*, TypeConfig*);
typedef bool ( *TypeDLL_isValid )(TypeConfig*);
typedef AnsiString& ( *TypeDLL_getType )();
/**
 * Interfejs pozwalajacy na l¹dowanie i uzywanie biblioteki typu
 * @author Piotr
 * @date 2008.11.25
 * @version 0.1
 */
class TypeDLL
{
	private:
		AnsiString type;
		HANDLE DLLHandle;
		TypeDLL_show fshow;
		TypeDLL_isValid fisValid;
		TypeDLL_getType fgetType;
	public:

		/**
		 * Konstruktor
		 * @param file sciezka do pliku
		 * @param stype
		 */
		TypeDLL(const AnsiString &fileDLL);
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
		 * Sprawdza poprawnosc danych.
		 * @param aData dane.
		 * @return poprawnosc wykonanej operacji
		 */
		bool isValid(TypeConfig *aData);
		/**
		 * Pobiera typ.
		 * @return typ.
		 */
		AnsiString& getType();

};

#endif
