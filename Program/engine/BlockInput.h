#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;
#ifndef __BlockInput_h__
#define __BlockInput_h__

#include "BlockElement.h"
/**
 * BlockInput - Klasa pojemnik przechowujaca wejscia i wyjscia bloku
 * @author Piotr
 * @date 2008.11.25
 * @version 0.1
 */
class BlockInput: public BlockElement
{
	public:
		AnsiString inputType;
	public:
		/**
		 * Konstruktor
		 * @param aName nazwa wejscia bloku
		 */
		BlockInput(const AnsiString aName);
		/**
		 * Konstruktor kopiujacy
		 * @param copy element ktory zostanie skopiowany
		 */
		BlockInput(const BlockInput &kopia);
		/**
		 * Destruktor
		 */
		~BlockInput();
		/**
		 * lista dozwolonych typow które moga zostac podane na wejscie
		 */
		vector<AnsiString> allowedTypes;
		/**
		 * Realizuje polaczenia miêdzy blokami.
		 * @param aName nazwa obiektu z ktorym bedzie polaczone wejscie.
		 * @return poprawnosc przeprowadzonej operajci.
		 */
		bool connect(const AnsiString aName);
		/**
		 * Pobiera typ polaczenia.
		 * @return nazwa typu polaczenia.
		 */
		AnsiString& getConnectedType();
		/**
		 * rozlacza bloki
		 */
		void disconnect();
};

#endif
