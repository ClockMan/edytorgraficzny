//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "configWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TcfgWindow *cfgWindow;
//---------------------------------------------------------------------------
__fastcall TcfgWindow::TcfgWindow(TComponent* Owner)
	: TForm(Owner)
{               
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::CancelClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	cfg_ = NULL;
	Action = caFree;	
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::SetConfig(Block* block)
{
	cfg_ = block->getConfig();
	CSpinEdit1->Value=cfg_->getInt("d1_1");
	CSpinEdit2->Value=cfg_->getInt("d1_2");
	CSpinEdit3->Value=cfg_->getInt("d1_3");
	CSpinEdit4->Value=cfg_->getInt("d1_4");
	CSpinEdit5->Value=cfg_->getInt("d1_5");

	CSpinEdit6->Value=cfg_->getInt("d2_1");
	CSpinEdit7->Value=cfg_->getInt("d2_2");
	CSpinEdit8->Value=cfg_->getInt("d2_3");
	CSpinEdit9->Value=cfg_->getInt("d2_4");
	CSpinEdit10->Value=cfg_->getInt("d2_5");

	CSpinEdit11->Value=cfg_->getInt("d3_1");
	CSpinEdit12->Value=cfg_->getInt("d3_2");
	CSpinEdit13->Value=cfg_->getInt("d3_3");
	CSpinEdit14->Value=cfg_->getInt("d3_4");
	CSpinEdit15->Value=cfg_->getInt("d3_5");

	CSpinEdit16->Value=cfg_->getInt("d4_1");
	CSpinEdit17->Value=cfg_->getInt("d4_2");
	CSpinEdit18->Value=cfg_->getInt("d4_3");
	CSpinEdit19->Value=cfg_->getInt("d4_4");
	CSpinEdit20->Value=cfg_->getInt("d4_5");

	CSpinEdit21->Value=cfg_->getInt("d5_1");
	CSpinEdit22->Value=cfg_->getInt("d5_2");
	CSpinEdit23->Value=cfg_->getInt("d5_3");
	CSpinEdit24->Value=cfg_->getInt("d5_4");
	CSpinEdit25->Value=cfg_->getInt("d5_5");
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	cfg_->setInt("d1_1",CSpinEdit1->Value);
	cfg_->setInt("d1_2",CSpinEdit2->Value);
	cfg_->setInt("d1_3",CSpinEdit3->Value);
	cfg_->setInt("d1_4",CSpinEdit4->Value);
	cfg_->setInt("d1_5",CSpinEdit5->Value);

	cfg_->setInt("d2_1",CSpinEdit6->Value);
	cfg_->setInt("d2_2",CSpinEdit7->Value);
	cfg_->setInt("d2_3",CSpinEdit8->Value);
	cfg_->setInt("d2_4",CSpinEdit9->Value);
	cfg_->setInt("d2_5",CSpinEdit10->Value);

	cfg_->setInt("d3_1",CSpinEdit11->Value);
	cfg_->setInt("d3_2",CSpinEdit12->Value);
	cfg_->setInt("d3_3",CSpinEdit13->Value);
	cfg_->setInt("d3_4",CSpinEdit14->Value);
	cfg_->setInt("d3_5",CSpinEdit15->Value);

	cfg_->setInt("d4_1",CSpinEdit16->Value);
	cfg_->setInt("d4_2",CSpinEdit17->Value);
	cfg_->setInt("d4_3",CSpinEdit18->Value);
	cfg_->setInt("d4_4",CSpinEdit19->Value);
	cfg_->setInt("d4_5",CSpinEdit20->Value);

	cfg_->setInt("d5_1",CSpinEdit21->Value);
	cfg_->setInt("d5_2",CSpinEdit22->Value);
	cfg_->setInt("d5_3",CSpinEdit23->Value);
	cfg_->setInt("d5_4",CSpinEdit24->Value);
	cfg_->setInt("d5_5",CSpinEdit25->Value);

	Close();
}
//---------------------------------------------------------------------------


