#ifndef VisualBlockH
#define VisualBlockH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "../engine/BlockInput.h";
#include "../engine/BlockOutput.h";
#include "../engine/Block.h";
#include "VisualInput.h";
#include "VisualOutput.h";
#include "BlockHistory.h";

#define PIWOMAINCLASSTYPE TScrollBox

struct Position {
   TPoint xy;
   char direction; //0 - Left, 1 - Top, 2 - Right, 3 - Bottom, 4 - nie znaleziono
};

typedef void (__closure *VisualBlock_FunctionI )(VisualInput*,  TObject*);
typedef void (__closure *VisualBlock_FunctionO )(VisualOutput*, TObject*);
typedef void (__closure *VisualBlock_FunctionHI )(VisualInput*, TObject*);
typedef void (__closure *VisualBlock_FunctionHO )(VisualOutput*, TObject*);
typedef void (__closure *VisualBlock_FunctionMove )(TObject*, bool, int, int);
/**
 * Klasa wyswietla caly bloczek
 */
class VisualBlock : public TPanel
{
	private:
		TSpeedButton *configButton;
		TLabel *title;
		TPanel *status;
		bool selected;
		bool moving;
		bool button;
		TPoint oldPoint;
		void __fastcall SpeedButtonClick(TObject *Sender);
		void __fastcall InputSelected(TObject *Sender);
		void __fastcall OutputSelected(TObject *Sender);
		void InputShowHistory(TObject *Sender);
		void OutputShowHistory(TObject *Sender);
		void __fastcall BlockClick(TObject *Sender);
		void __fastcall BlockMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall BlockMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
		void __fastcall BlockMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
		void resizeAll();
	public:
		/**
		 * Blok w wersji niskopoziomowej
		 */
		Block block;
		AnsiString nameOfBlock;
		int		   numberOfBlock;
		/**
		 * Informacja o tym czy blok zostal juz uruchomiony - zmienna pomocnicza, wewnetrzna
		 */
		bool runned;
		/**
		 * Historia bloku
		 */
		vectorBlockHistory history;
		/**
		 * Lista wejsc do bloku z lewej strony
		 */
		vector<VisualInput*> leftInput;
		/**
		 * Lista wejsc do bloku z gornej strony
		 */
		vector<VisualInput*> topInput;
		/**
		 * Lista wyjsc z bloku z prawej strony
		 */
		vector<VisualOutput*> rightOutput;
		/**
		 * Lista wyjsc z bloku z dolnej strony
		 */
		vector<VisualOutput*> bottomOutput;
		
		/**
		 * Event: gdy kliknieto przycisk konfiguracyjny
		 */
		VisualFunction OnConfigClick;
		/**
		 * Event: gdy kliknieto na wejscie bloku
		 */
		VisualBlock_FunctionI OnVisualInputSelected;
		/**
		 * Event: gdy kliknieto na wyjscie bloku
		 */
		VisualBlock_FunctionO OnVisualOutputSelected;
		/**
		 * Event: gdy kliknieto prawym przycuskiem na wejscie bloku
		 */
		VisualBlock_FunctionHI OnVInputHistory;
		/**
		 * Event: gdy kliknieto prawym przyciskiem na wyjscie bloku
		 */
		VisualBlock_FunctionHO OnVOutputHistory;
		/**
		 * Event: gdy przesunieto blok
		 */
		VisualBlock_FunctionMove OnBlockMove;
		/**
		 * Event: gdy odznacozno blok
		 */
		VisualFunction OnUnselect;
		/**
		 * Event: gdy gdy zaznacozno blok, ale zarzadano odznaczenia innych
		 */
		VisualFunction OnSelect;
		/**
		 * Event: gdy zaznaczono blok
		 */
		VisualFunction OnSelectAdd;
		/**
		 * Konstruktor
		 * @param Owner klasa nadrzedna dla tej klasy
		 */
		__fastcall VisualBlock(TComponent* Owner);
		/**
		 * Destruktor
		 */
		__fastcall ~VisualBlock();
		/**
		 * Pobiera pozycje wejscia do bloku
		 * @param object wejscie
		 * @return pozycja
		 */
		Position getInputPosition(BlockInput* object);
		/**
		 * Pobiera pozycje wyjscia z bloku
		 * @param object wyjscia
		 * @return pozycja
		 */
		Position getOutputPosition(BlockOutput* object);
		/**
		 * Ustawia nowy obrazek jako obrazek pokazujacy sie na przycusku konfiguracyjnym
		 * @param bmp obrazek
		 * @return true jesli operacja sie powiodla
		 */
		bool setConfigButtonGlyph(Graphics::TBitmap *bmp);
		/**
		 * Ustawia tytul bloczka
		 * @param s nowy tytul
		 */
		void setTitle(const AnsiString &s);
		/**
		 * Pobiera aktualny tytul bloczka
		 * @return tytul
		 */
		AnsiString getTitle();
		/**
		 * Dostosowuje wizualne infomacje o bloczku do informacji zawartych w niskopoziomowej klasie Block.
		 * @return false gdy wystapil blad
		 */
		bool updateVisualComponents();
		/**
		 * Aktualizuje historie usuwajac z niej wszelkie przedawnione i nieaktualne dane
		 */
		bool updateHistory();
		/**
		 * Zaznacza/Odznacza blok
		 * @param status true -zaznaczony, false - odznaczony
		 */
		void setSelected(bool status);
		/**
		 * Informuje o tym czy blok jest juz zaznaczony
		 * @return true - zaznaczony, false - nie zaznaczony
		 */
		bool isSelected();
		/**
		 * Ustawia kolor statusu bloczka - widniejacy do okola przycisku konfiguracyjnego
		 * @param cl nowy kolor
		 */
		void setStatusColor(TColor cl);
};

/**
 * Informuje czy klawisz Ctrl jest wcisniety
 * @return true -wcisniety, false - nie wcisniety
 */
bool ctrlDown();
/**
 * Informuje czy klawisz Alt jest wcisniety
 * @return true -wcisniety, false - nie wcisniety
 */
bool altDown();
#endif
