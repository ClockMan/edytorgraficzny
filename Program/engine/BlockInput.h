#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __BlockInput_h__
#define __BlockInput_h__

#include "BlockElement.h"
/**
* BlockInput - Klasa pojemnik przechowuj¹ca wejœcia i wyjscia bloku
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
		* @param aName Nazwa wejœcia bloku
		*/
				BlockInput(const AnsiString aName);
		/**
		* Konstruktor kopiuj¹cy
		*/
				BlockInput(BlockInput &kopia);
		 /**
		 * Destruktor
		 */
				~BlockInput();
		 /**
		 * lista dozwolonych typów które mog¹ zostaæ podane na wejœcie
		 */
				vector<AnsiString> allowedTypes;
		 /**
		 * Realizujê po³¹czenia miêdzy blokami.
		 * @param aName nazwa obiektu z którym bedziê po³¹czone wejœcie.
		 * @return bool poprawnoœæ przeprowadzonej operajci.
		 */
				bool connect(const AnsiString aName);
		 /**
		 * Pobiera typ po³¹czenia.
		 * @return nazwa typu po³¹czenia.
		 */
				AnsiString& getConnectedType();
		  /**
		  * roz³¹cza bloki
		  */
				void disconnect();
};

#endif
