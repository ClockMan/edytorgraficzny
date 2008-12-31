#ifndef ConnectionH
#define ConnectionH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <vector>
#include "../engine/BlockInput.h"
#include "../engine/BlockOutput.h"
#include "Line.h"
#include "VisualBlock.h"

#define CONNECTION_OK_NORMAL   		 0x33CC33
#define CONNECTION_OK_SELECTED 		 0x20FF20
#define CONNECTION_WARRNING_NORMAL   61137
#define CONNECTION_WARRNING_SELECTED 65021
#define CONNECTION_ERROR_NORMAL   	 206
#define CONNECTION_ERROR_SELECTED 	 255

static const TColor ConnectionOkNormalColor=CONNECTION_OK_NORMAL;
static const TColor ConnectionOkSelectedColor=CONNECTION_OK_SELECTED;
static const TColor ConnectionWarrningNormalColor=CONNECTION_WARRNING_NORMAL;
static const TColor ConnectionWarrningSelectedColor=CONNECTION_WARRNING_SELECTED;
static const TColor ConnectionErrorNormalColor=CONNECTION_ERROR_NORMAL;
static const TColor ConnectionErrorSelectedColor=CONNECTION_ERROR_SELECTED;

typedef void (__closure *Connection_Function)(void*);

/**
 * @author Piotr Zegar
 * @date 2008.12.03
 * @version 0.1
 *
 *  Klasa zajmuje siê generowaniem po³¹czeñ miedzy 2 blokami.
 */
class Connection
{
	 private:
		TWinControl* fowner;
		int status;
		bool selected;
		
		void OnLineMove(TObject* Sender);
		void OnConnectionSelectedRequest(TObject* Sender);
		void OnConnectionResetRequest(TObject* Sender);

		bool connectionOk(Position &in, Position &out);
		void redraw(Position &in, Position &out);
	 public:
		Connection_Function OnConnectionSelected;

		BlockInput* input;
		BlockOutput* output;
		VisualBlock* inBlock;
		VisualBlock* outBlock;
		AnsiString typeOfConnection;
		vector<Line*> lines;

		Connection(TWinControl* owner);
		~Connection();

		bool draw();
		bool update();
		bool connectionOk();

		void BringToFront();
		void setSelected(bool s);
		bool getCustomizeState();
		void setCustomizeFalse();
};
#endif
