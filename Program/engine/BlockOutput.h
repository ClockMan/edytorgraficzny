#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockOutput_h__
#define __BlockOutput_h__

#include "BlockElement.h"
/**
* BlockInput - Klasa pojemnik przechowuj¹ca wejœcia i wyjscia bloku
* @author Piotr
* @date 2008.11.25
* @version 0.1
*/
class BlockOutput: public BlockElement
{
		private:
				AnsiString outputType;
		public:
			/**
			* Konstruktor
			* @param aName nazwa wyjœcia.
			*/
				BlockOutput(const AnsiString aName);
			/**
			* Konstruktor kopiuj¹cy.
			* @param copy obiekt który zostanie skopiowany
			*/
				BlockOutput(const BlockOutput &copy);
			/**
			* Destruktor
			*/
				~BlockOutput();
			/**
			* Zwraca typ wyjœcia.
			* @return AnsiString typ wyjœcia
			*/
				AnsiString& getOutputType();
			/**
			* Ustawia typ wyjœcia.
			* @param aName typ wyjœcia.
			* @return poprawnoœæ wykonanej operacji
			*/
				bool setOutputType(AnsiString aName);
};

#endif
