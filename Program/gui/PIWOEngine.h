#ifndef PIWOEngineH
#define PIWOEngineH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include "../engine/PluginContener.h"
#include "VisualBlock.h"
#include "Connection.h"

typedef void (__closure *PIWOEngine_Log )(TObject*,const AnsiString);

class PIWOEngine : public TPanel
{
	private:
		TScrollBox *area;

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
		void OnVisualBlockInputHistoryClick(VisualInput* input, vectorBlockHistory* history);
		void OnVisualBlockOutputHistoryClick(VisualOutput* output, vectorBlockHistory* history);
		void OnVisualBlockMove(TObject* Sender, bool moveAll, int x, int y);
		void OnVisualBlockUnselect(TObject* Sender);
		void OnVisualBlockSelect(TObject* Sender);
		void OnVisualBlockSelectAdd(TObject* Sender);
		void __fastcall onThisClick(TObject* Sender);
		void OnConnectionSelect(TObject* Sender);

		Connection* getConnectionTo(VisualInput* input);
		bool MakeConnection(VisualBlock* outputBlock, VisualOutput* output, VisualBlock* inputBlock, VisualInput* input);
	public:
		PIWOEngine_Log OnInformation;
		PIWOEngine_Log OnWarrning;
		PIWOEngine_Log OnError;

		PluginContener *plugins;
		__fastcall PIWOEngine(TComponent* Owner);
		__fastcall ~PIWOEngine();

		bool AddBlock(const AnsiString &name);
	__published:
};
#endif
