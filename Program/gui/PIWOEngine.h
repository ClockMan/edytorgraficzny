#ifndef PIWOEngineH
#define PIWOEngineH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include "../brige/PluginContener.h"
#include "VisualBlock.h"
#include "Connection.h"
#include "history.h"

#define PIWOMAINCLASSTYPE TScrollBox

typedef void (__closure *PIWOEngine_Log )(TObject*,const AnsiString);
typedef void (__closure *PIWOEngine_RunProgress)(TObject*,const AnsiString, const double);
typedef void (__closure *PIWOEngine_Event) (TObject*);
/**
 * Glowna klasa projektu, kazda jej instancja symbolizuje osobny projekt
 */
class PIWOEngine : public TPanel
{
	private:
		PIWOMAINCLASSTYPE *area;
		vector<VisualBlock*> blocks;
		vector<Connection*> connections;
        Connection*	selectedConnection;
		vector<VisualBlock*> selectedBlocks;
		VisualBlock* selectedOutputBlock;
		VisualBlock* selectedInputBlock;
		VisualInput* selectedInput;
		VisualOutput* selectedOutput;

		void OnVisualBlockConfigClick(TObject* Sender);
		void OnVisualBlockInputSelected(VisualInput* input,  TObject* Sender);
		void OnVisualBlockOutputSelected(VisualOutput* output,  TObject* Sender);
		void OnVisualBlockInputHistoryClick(VisualInput* input, TObject* Sender);
		void OnVisualBlockOutputHistoryClick(VisualOutput* output, TObject* Sender);
		void OnVisualBlockMove(TObject* Sender, bool moveAll, int x, int y);
		void OnVisualBlockUnselect(TObject* Sender);
		void OnVisualBlockSelect(TObject* Sender);
		void OnVisualBlockSelectAdd(TObject* Sender);
		void __fastcall onThisClick(TObject* Sender);
		void OnConnectionSelect(void* Sender);
		void __fastcall HistoryFormClose(TObject *Sender, TCloseAction &Action);
		void validateBlock(VisualBlock *block, bool updateInputConnections=true);

		Connection* getConnectionTo(VisualInput* input);
		bool MakeConnection(VisualBlock* outputBlock, VisualOutput* output, VisualBlock* inputBlock, VisualInput* input);
		bool runBlock(VisualBlock* block, bool fastRun, bool *useHistory);

		bool runUsingHistory();
		bool runNotUsingHistory();

		bool isRunning;
		bool stopRunning;

		unsigned int runProgress;
		bool changed;
	public:
		/**
		 * Domyslny obrazek widniejacy na przycisku konfiguracyjnym bloczkow gdy niemaja ustawionego swojego
		 */
		Graphics::TBitmap *defaultBlockImage;
		/**
		 * Event: Logowanie - Informacja
		 */
		PIWOEngine_Log OnInformation;
		/**
		 * Event: Logowanie - Debug
		 */
		PIWOEngine_Log OnDebug;
		/**
		 * Event: Logowanie - Sukces
		 */
		PIWOEngine_Log OnSuccess;
		/**
		 * Event: Logowanie - Ostrzezenie
		 */
		PIWOEngine_Log OnWarrning;
		/**
		 * Event: Logowanie - Blad
		 */
		PIWOEngine_Log OnError;
		/**
		 * Event: Logowanie - Podczas uruchamiania - Informacja
		 */
		PIWOEngine_Log OnRunInformation;
		/**
		 * Event: Logowanie - Podczas uruchamiania - Debug
		 */
		PIWOEngine_Log OnRunDebug;
		/**
		 * Event: Logowanie - Podczas uruchamiania - Sukces
		 */
		PIWOEngine_Log OnRunSuccess;
		/**
		 * Event: Logowanie - Podczas uruchamiania - Ostrzerzenie
		 */
		PIWOEngine_Log OnRunWarrning;
		/**
		 * Event: Logowanie - Podczas uruchamiania - Blad
		 */
		PIWOEngine_Log OnRunError;
		/**
		 * Event: gdy zaznaczono blok
		 */
		PIWOEngine_Event OnBlockSelected;
		/**
		 * Event: gdy zaznaczono polaczenie
		 */
		PIWOEngine_Event OnConnectionSelected;
		/**
		 * Event: gdy nic nie jest zaznaczone
		 */
		PIWOEngine_Event OnNothingSelected;
		/**
		 * Event: gdy projekt zostal zmodyfikowany
		 */
		PIWOEngine_Event OnChanged;
		/**
		 * Event: podczas uruchamiania projektu
		 */
		PIWOEngine_RunProgress OnRunProgress;
		/**
		 * Event: gdy projekt zostaje uruchomiony
		 */
		PIWOEngine_Event	OnRunStart;
		/**
		 * Event: gdy projekt zostal uruchomiony
		 */
		PIWOEngine_Event	OnRunEnd;
		/**
		 * Kontener pluginow
		 */
		PluginContener *plugins;
		/**
		 * Lista okien histori aktualnie otwartych dla tego projektu
		 */
		vector<THistory*> historyWindows;
		/**
		 * Czy trym Auto-run ma być włączony
		 */
		bool alwaysRun;
		/**
		 * Konstruktor
		 * @param Owner komponent bedacy parentem i wlascicielem dla projektu
		 */
		__fastcall PIWOEngine(TComponent* Owner);
		/**
		 * Destruktor
		 */
		__fastcall ~PIWOEngine();

		/**
		 * Dodaje blok do projektu
		 * @param name nazwa bloku
		 * @return true jesli blok zostal dodany
		 */
		bool AddBlock(const AnsiString &name);
		/**
		 * Usuwa blok z projektu
		 * @param fullName tytul bloku (napis widniejacy na nim)
		 * @return true jesli blok zostal usuniety
		 */
		bool DeleteBlock(const AnsiString &fullName);
		/**
		 * Usuwa wszystkie zaznaczone bloki
		 * @return true jesli usunieto cos
		 */
		bool DeleteSelectedBlocks();
		/**
		 * Usuwa wszywstkie bloki
		 * @return true jesli usunieto cos
		 */
		bool DeleteAllBlocks();
		/**
		 * Zaznacza wszystkie bloki
		 */
		void SelectAllBlocks();
		/**
		 * Odwraca zaznaczenie wszystkich blokow
		 */
		void InvertBlockSelection();
		/**
		 * Odznacza wszystkie bloki
		 */
		void UnselectAllBlocks();
		/**
		 * Usuwa zaznaczone polaczenie
		 * @return true jesli jakies polaczenie jest zaznaczone i zostalo usuniete
		 */
		bool DeleteSelectedConnection();
		/**
		 * Usuwa wszystkie polaczenia
		 * @return true jesli jakies polaczenie zostalo usuniete
		 */
		bool DeleteAllConnections();
		/**
		 * Odznacza zaznaczone polaczenie, jesl jest takie
		 */
		void UnselectSelectedConnection();
		/**
		 * Anuluje zmiany wprowadzone przez urzytkownika w zaznaczonym polaczeniu
		 */
		void CancelCustomizationOnSelectedConnections();
		/**
		 * Anuluje zmiany wprowadzone przez urzytkownika we wszystkich polaczeniach
		 */
		void CancelCustomizationOnAllConnections();
		/**
		 * Duplikuje zaznaczone bloki
		 */
		void DuplcateSelectedBlocks();
		/**
		 * Sprawsza wszystkie bloki
		 */
		void validateAll();
		/**
		 * Uruchamai projekt
		 * @param useHistory czy ma uzywac historii
		 * @return true jesli uruchomiono bez bledow
		 */
		bool run(bool useHistory=true);
		/**
		 * Sprawdza czy projekt ejst aktualnie uruchamiany
		 * @return true jesli ejst aktualnie uruchamiany, w przeciwnym wypadku false
		 */
		bool isRuned();
		/**
		 * Anuluje uruchamianie projektu
		 * @param wait czy ma czekac az uruchomienie zostanie anulowane
		 */
		void abort(bool wait=false);
		/**
		 * Czy juz anulowano uruchomienie projektu
		 * @return true/false
		 */
		bool isAborted();
		/**
		 * Zapisuje projekt do pliku
		 * @param filename sciezka do pliku
		 * @return false jesli nie zapisano
		 */
		bool saveToFile(const AnsiString &filename);
		/** 
		 * Wczytuje projekt z pliku
		 * @param filename
		 * @return false jesli nie wczytano
		 */
		bool loadFromFile(const AnsiString &filename);
		/**
		 * Czy w projekcie wprowadzono zmiany
		 * @return true/false = tak/nie
		 */
		bool isChanged();
		/**
		 * Zwraca ilosc blokow w projekcie
		 * @return ilosc blokow
		 */
		int getBlockCount();
		/**
		 * Zwraca ilosc polaczen w projekcie
		 * @return ilosc polaczen
		 */
		int getConnectionsCount();
		/**
		 * Czy jakiekolwiek blok jest zaznacozny
		 * @return true jesli tak, false jesli nie
		 */
		bool isBlockSelected();
		/**
		 * Czy polaczenie jest zaznaczone
		 * @return true jesli tak, false jesli nie
		 */
		bool isConnectionSelected();
};

/**
 * Zapisuje string do stream
 * @param str string
 * @param stream stream
 */
void putString(const AnsiString &str,TStream &stream);
/**
 * Zapisuje integer do stream
 * @param i integer
 * @param stream stream
 */
void putInt(const int i,TStream &stream);
/**
 * Pobiera string z stream
 * @param stream stream
 * @return string
 */
AnsiString getString(TStream &stream);
/**
 * Pobiera integer z stream
 * @param stream stream
 * @return integer
 */
int getInt(TStream &stream);
#endif
