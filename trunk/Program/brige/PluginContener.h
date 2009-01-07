#include <System.hpp>
#include <vector>
#include <exception>
using namespace std;

#ifndef __PluginContener_h__
#define __PluginContener_h__
										//Sender, progress, max, info, code 0-ok typ danych, 1- ok funkcja, 2- nie typdanych, 3- nie funkcja
typedef void (__closure *PluginContener_OnProgress)(void*, int, int, AnsiString, int);
typedef void (__closure *PluginContener_Log )(TObject*,const AnsiString);

#include "TypeDLL.h"
#include "FunctionDLL.h"
/**
 * Klasa pojemnik przechowujaca pluginy
 * @author Piotr
 * @date 2008.11.25
 * @version 0.1
 */
class PluginContener
{
	private:
		vector<TypeDLL*> listOfType;
		vector<FunctionDLL*> listOfFunction;
		int SearchDirectory(std::vector<AnsiString> &refvecFiles,
					const AnsiString        &refcstrRootDirectory,
					const AnsiString        &refcstrExtension,
					bool	   bSearchSubdirectories = true);
		void AddMenus(FunctionDLL *info, TMainMenu &menu, TImageList &images, int upId, int downId, int functionIcon, int folderIcon);
		void OnFunctionClick(void* Sender);
		vector<TMenuItem*> menuItems; //wszystkie itemy z menu
	public:
		/**
		 * Event
		 */
		PluginContener_OnProgress OnLoadingProgress;
		/**
		 * Event
		 */
		FunctionDLL_onClick OnFunctionAddRequest;
		/**
		 * Konstuktor domyslny
		 */
		PluginContener();
		/**
		 * Destruktor
		 */
		~PluginContener();
		/**   
		 * Metoda przeszukuje podfoldery w poszukiwaniu plikow typow ii plikow funkcji, laduje je i tworzy dla nich menu
		 * @param blockDir folder zawierajacy dll funkcji
		 * @param typesDir folder zawierajacy dll typu
		 * @param menu referencja do obiektu menu do ktorego maja zostac dodane nowe mena
		 * @param images lista obrazkow (kontener) powiazany z tym menu
		 * @param upId identyfikator ustawiony w popredzajacych menach - GroupId
		 * @param downId identyfikator ustawiony w nastepnych menach - GroupId
		 * @param functionIcon domyslny nr ikony dla funkcji
		 * @param folderIcon domyslny nr ikony dla kategori
		 * @return true gdy zaladowano chodz jeden plugin
		 */
		bool LoadData(AnsiString blockDir, AnsiString typesDir, TMainMenu &menu, TImageList &images, int upId, int downId, int functionIcon, int folderIcon);
		/**
		 * Laduje i dodaje dll typu do kontenera.
		 * @param fileDLL sciezka do pliku
		 * @return NULL lub wskaznik do klsy TypeDLL
		 */
		TypeDLL* addType(const AnsiString &fileDLL);
		/**
		 * Laduje i dodaje dll funkcji do kontenera.
		 * @param fileDLL sciezka do pliku
		 * @return NULL lub wskaznik do klasy FunctionDLL
		 */
		FunctionDLL* addFunction(const AnsiString &fileDLL);
		/**
		 * Zwraca klase ktora zaladowala odpowiedni typ
		 * @param type nazwa typu
		 * @return klasa TypeDLL
		 */
		TypeDLL* getType(const AnsiString &type);
		/**
		 * Zwraca klase ktora zaladowala odpowiednia funkcje
		 * @param name nazwa funkcji
		 * @return klasa FunctionDLL
		 */
		FunctionDLL* getFunction(const AnsiString &name);
		/**
		 * Blokuje lub odblokowuje wszystkie pozycje w menu ladowanym dynamicznie
		 * @param enabled true-odblokowane, false-zablokowane
		 */
		void setMenuItemsStatus(bool enabled);
};

#endif
