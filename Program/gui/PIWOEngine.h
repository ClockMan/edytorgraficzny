#ifndef PIWOEngineH
#define PIWOEngineH

#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include "../engine/PluginContener.h"
#include "VisualBlock.h"
#include "Connection.h"
#include "history.h"

#define PIWOMAINCLASSTYPE TScrollBox

typedef void (__closure *PIWOEngine_Log )(TObject*,const AnsiString);
typedef void (__closure *PIWOEngine_RunProgress )(TObject*,const AnsiString, const double);

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
	public:
		PIWOEngine_Log OnInformation;
		PIWOEngine_Log OnWarrning;
		PIWOEngine_Log OnError;
		PIWOEngine_RunProgress OnRunAllProgress;
		PIWOEngine_RunProgress OnRunProgress;
		PIWOEngine_RunProgress OnCompileProgress;

		PluginContener *plugins;
		vector<THistory*> historyWindows;

		__fastcall PIWOEngine(TComponent* Owner);
		__fastcall ~PIWOEngine();

		bool AddBlock(const AnsiString &name);
		bool DeleteBlock(const AnsiString &fullName);
		bool DeleteSelectedBlocks();
		bool DeleteAllBlocks();
		void SelectAllBlocks();
		void InvertBlockSelection();
		void UnselectAllBlocks();
		bool DeleteSelectedConnection();
		bool DeleteAllConnections();
		void UnselectSelectedConnection();
		void CancelCustomizationOnSelectedConnections();
		void CancelCustomizationOnAllConnections();
		bool run();
		bool runAll();
		bool compile();//taka �ciema, sprawdizmy poprawno�c all blok�w :d
};
#endif
