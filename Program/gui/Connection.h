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
 * Klasa ma wykonywa� po��czenia najkr�tsz� mo�liw� drog�.
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
