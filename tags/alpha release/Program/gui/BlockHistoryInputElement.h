#ifndef BlockHistoryInputElementH
#define BlockHistoryInputElementH

#include "../engine/BlockInput.h"
#include "../engine/TypeConfig.h"
/**
 * Klasa zawiera historie dla pojedynczego wejscia bloku
 */
class BlockHistoryInputElement
{
    private:
	TypeConfig* data;
    public:
    /**
     * Wejscie bloku
     */
	BlockInput* input;
	/**
	 * Ustawia obiekt
	 * @param d dane
	 */
	void setData(TypeConfig &d);
	/**
	 * Czysci obiekt
	 */
	void setNULL();
	/**
	 * Zwraca obiekt
	 * @return NULL lub TypeConfig*
	 */
	TypeConfig* getData();
	/**
	 * Konstruktor
	 */
	BlockHistoryInputElement();
	/**
	 * Destruktor
	 */
	~BlockHistoryInputElement();
};



#endif
