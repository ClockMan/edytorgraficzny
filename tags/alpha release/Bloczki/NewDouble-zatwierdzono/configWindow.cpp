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
	Edit1->Text=FloatToStr(cfg_->getDouble("data"));
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	try{
	cfg_->setDouble("data",StrToFloat(Edit1->Text));
	}catch(...)
	{}
	Close();
}
//---------------------------------------------------------------------------




void __fastcall TcfgWindow::Edit1KeyPress(TObject *Sender, char &Key)
{
	if (!((Key==8)||((Key==',')&&(!Edit1->Text.Pos(',')))||(Key=='1')||(Key=='2')||(Key=='3')||(Key=='4')||(Key=='5')||(Key=='6')||(Key=='7')||(Key=='8')||(Key=='9')||(Key=='0'))) Key=0;
}
//---------------------------------------------------------------------------

