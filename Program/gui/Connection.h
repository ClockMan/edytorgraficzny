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

#define CONNECTION_OK_NORMAL   		 0x20FF20
#define CONNECTION_OK_SELECTED 		 0xDF0038
#define CONNECTION_WARRNING_NORMAL   0x0BD1EE
#define CONNECTION_WARRNING_SELECTED 0x00FDFD
#define CONNECTION_ERROR_NORMAL   	 0xCE0000
#define CONNECTION_ERROR_SELECTED 	 0xFF0000

static const TColor ConnectionOkNormalColor=CONNECTION_OK_NORMAL;
static const TColor ConnectionOkSelectedColor=CONNECTION_OK_SELECTED;
static const TColor ConnectionWarrningNormalColor=CONNECTION_WARRNING_NORMAL;
static const TColor ConnectionWarrningSelectedColor=CONNECTION_WARRNING_SELECTED;
static const TColor ConnectionErrorNormalColor=CONNECTION_ERROR_NORMAL;
static const TColor ConnectionErrorSelectedColor=CONNECTION_ERROR_SELECTED;
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
		vector<Line*> lines;
		TWinControl* fowner;
		int status;
		bool selected;
		
		void OnLineMove(TObject* Sender);
		void OnConnectionSelectedRequest(TObject* Sender);
		void update(Line* object);
	 public:
		BlockInput* input;
		BlockOutput* output;
		VisualBlock* inBlock;
		VisualBlock* outBlock;

		Connection(TWinControl* owner);
		~Connection();

		bool update();
		
		void BringToFront();
		void setSelected(bool s);
};
#endif
