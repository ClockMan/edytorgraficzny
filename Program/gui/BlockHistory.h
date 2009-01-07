#ifndef BlockHistoryH
#define BlockHistoryH

#include "BlockHistoryOutputElement.h"
#include "BlockHistoryInputElement.h"
#include <vector>
/**
 * Klasa zawiera historie dla calego bloku po jego jednokrotnym uruchomieniu.
 */
class BlockHistory
{
	 public:
	  /**
	   * Lista histori dla wejsc z lewej strony bloczka
	   */
	  vector<BlockHistoryInputElement*> leftInput;
	  /**
	   * Lista histori dla wejsc z gornej strony bloczka
	   */
	  vector<BlockHistoryInputElement*> topInput;
	  /**
	   * Lista histori dla wyjsc z prawej strony bloczka
	   */
	  vector<BlockHistoryOutputElement*> rightOutput;
	  /**
	   * Lista histori dla wyjsc z dolnej strony bloczka
	   */
	  vector<BlockHistoryOutputElement*> bottomOutput;
	  /**
	   * Wersja konfiguracji
	   */
	  unsigned int configRevision;
	  /**
	   * Data i godzina dodania histori
	   */
	  TDateTime date;
	  /**
	   * Konstruktor domyslny
	   */
	  BlockHistory();
	  /**
	   * Konstruktor kopiujacy
	   * @param ob obiekt z ktorego mamy skopiowac
	   */
	  BlockHistory(BlockHistory &b);
	  /**
	   * Destruktor
	   */
	  ~BlockHistory();
};

typedef vector<BlockHistory*> vectorBlockHistory;
#endif
