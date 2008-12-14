#ifndef PIWOEngineH
#define PIWOEngineH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "../engine/PluginContener.h"

class PIWOEngine : public TScrollBox
{
public:
    PluginContener *plugins;
	__fastcall PIWOEngine(TComponent* Owner);
__published:
};
#endif
