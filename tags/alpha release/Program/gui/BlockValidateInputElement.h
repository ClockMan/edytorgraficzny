#ifndef BlockValidateInputElementH
#define BlockValidateInputElementH

#include "../engine/BlockInput.h"
#include "Connection.h"

/**
 * Klasa ta jest pojemnikiem, dla metody validateBlock w PIWOEngine
 */
class BlockValidateInputElement
{
	public:
	/**
	 * Wskaznik do wejscia bloku
	 */
	BlockInput* input;
	/**
	 * Komunikat bledu na tym wejsciu
	 */
	AnsiString errorDescription;
	/**
	 * Kod bledu na tym wejsciu
	 */
	int errorCode;
	/**
	 * Polaczenie aktualnie podlaczone do tego wejscia, lub NULL gdy go brak
	 */
	Connection* connection;
};
#endif
