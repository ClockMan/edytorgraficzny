//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "configWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TcfgWindow *cfgWindow;
//---------------------------------------------------------------------------
__fastcall TcfgWindow::TcfgWindow(TComponent* Owner)
	: TForm(Owner)
{
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

	if(cfg_->getString("bitrate") == "Bitmap24bit")
		bit_24->Checked = true;
	else if(cfg_->getString("bitrate") == "Bitmap32bit")
		bit_32->Checked = true;
	else if(cfg_->getString("bitrate") == "Bitmap16bit")
		bit_16->Checked = true;
	else if(cfg_->getString("bitrate") == "Bitmap8bit")
		bit_8->Checked = true;
	else if(cfg_->getString("bitrate") == "Bitmap4bit")
		bit_4->Checked = true;
	else
		bit_1->Checked = true;
	
	EditPath->Text = cfg_->getString("path");
	OK->Enabled=!EditPath->Text.IsEmpty();
}
//---------------------------------------------------------------------------
void __fastcall TcfgWindow::CancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TcfgWindow::Button1Click(TObject *Sender)
{
	if(SaveDialog1->Execute())
	{
		EditPath->Text = SaveDialog1->FileName;
		OK->Enabled=true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TcfgWindow::OKClick(TObject *Sender)
{
	cfg_->setString("path",EditPath->Text);
	if(bit_24->Checked) cfg_->setString("bitrate","Bitmap24bit");
	else if(bit_32->Checked) cfg_->setString("bitrate","Bitmap32bit");
	else if(bit_16->Checked) cfg_->setString("bitrate","Bitmap16bit");
	else if(bit_8->Checked) cfg_->setString("bitrate","Bitmap8bit");
	else if(bit_4->Checked) cfg_->setString("bitrate","Bitmap4bit");
	else cfg_->setString("bitrate","Bitmap1bit");

	Close();	
}
//---------------------------------------------------------------------------


