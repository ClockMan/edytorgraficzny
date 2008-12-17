#ifndef PIWOEngineH
#define PIWOEngineH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include "../engine/PluginContener.h"
#include "VisualBlock.h"
#include "Connection.h"

class PIWOEngine : public TPanel
{
	private:
		TScrollBox *area;

		vector<VisualBlock*> blocks;
		vector<Connection*> conections;

        vector<VisualBlock*> selectedBlocks;

		void OnVisualBlockConfigClick(TObject* Sender);
		void OnVisualBlockInputSelected(VisualInput* input,  TObject* Sender);
		void OnVisualBlockOutputSelected(VisualOutput* output,  TObject* Sender);
		void OnVisualBlockInputHistoryClick(VisualInput* input, vectorBlockHistory* history);
		void OnVisualBlockOutputHistoryClick(VisualOutput* output, vectorBlockHistory* history);
		void OnVisualBlockMove(TObject* Sender, bool moveAll, int x, int y);
		void OnVisualBlockUnselect(TObject* Sender);
		void OnVisualBlockSelect(TObject* Sender);
		void OnVisualBlockSelectAdd(TObject* Sender);
		void __fastcall onThisClick(TObject* Sender);
	public:
		PluginContener *plugins;
		__fastcall PIWOEngine(TComponent* Owner);
		__fastcall ~PIWOEngine();

		bool AddBlock(const AnsiString &name);
	__published:
};
#endif
