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

/**
 * @author Piotr Zegar
 * @date 2008.12.03
 * @version 0.1
 *
 *  Klasa zajmuje siê generowaniem po³¹czeñ miedzy 2 blokami.
 */
class Connection
{
	 protected:
		vector<Line*> lines;
		TColor fonOverColor;
		TColor fonOutColor;
		TColor fonClickColor;
		TWinControl* fowner;
	 public:
		BlockInput* input;
		BlockOutput* output;
		VisualBlock* inBlock;
		VisualBlock* outBlock;

		Connection(TWinControl* owner);
		~Connection();

		bool draw();
		bool redraw(Line* object);
		

};
#endif
