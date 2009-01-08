//$$---- Form CPP ----
#include <vcl.h>
#pragma hdrstop
#include "history.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

__fastcall THistory::THistory(TComponent* Owner)
	: TForm(Owner)
{
   showFrame=NULL;
   count=0;
}

__fastcall THistory::~THistory()
{
   this->TreeView1->Items->Clear();
}

void THistory::refresh(BlockElement *toShow)
{
   this->TreeView1->Items->BeginUpdate();
   this->TreeView1->Items->Clear();
   showFrame=NULL;
   Label1->Caption="";
   Caption=block->getTitle();

   TTreeNode *root=this->TreeView1->Items->AddFirst(NULL,block->getTitle());
   root->ImageIndex=0;
   root->Data=block;

   TypeDLL *tdll=NULL;
   for(unsigned int i=0;i<block->history.size();++i)
   {
	 TTreeNode *his=this->TreeView1->Items->AddChild(root,IntToStr(i+1)+". "+FormatDateTime("hh:nn:ss",block->history[i]->date));
	 his->Data=block->history[i];
	 his->ImageIndex=1;
	 his->SelectedIndex=1;

	 for(unsigned int j=0;j<block->history[i]->leftInput.size();++j)
	 {
		 AnsiString tmp="NULL";
		 if (block->history[i]->leftInput[j]->getData()!=NULL) tmp=block->history[i]->leftInput[j]->getData()->getName();
		 TTreeNode *it=this->TreeView1->Items->AddChild(his,(block->history[i]->leftInput[j]->input->getDescription().IsEmpty()?block->history[i]->leftInput[j]->input->getName():block->history[i]->leftInput[j]->input->getDescription())+" - "+tmp);
		 it->ImageIndex=2;
		 it->SelectedIndex=2;
		 if (block->history[i]->leftInput[j]->getData()!=NULL)
		 {
			if (tdll==NULL||tdll->getType()!=block->history[i]->leftInput[j]->getData()->getName()) {
			   tdll=plugins->getType(block->history[i]->leftInput[j]->getData()->getName());
			}
			if (tdll!=NULL) {
			TFrame *fm=tdll->show(this, block->history[i]->leftInput[j]->getData());
			fm->Name="item"+IntToStr(count++);
			fm->Align=alClient;
			fm->Hint=root->Text+" - "+his->Text+" - "+it->Text;
			it->Data=fm;
			if (toShow==block->history[i]->leftInput[j]->input&&i==0)
			{
			   if (showFrame!=NULL) showFrame->Visible=false;
			   fm->Show();
			   Label1->Caption=fm->Hint;
			   showFrame=fm;
			} else fm->Hide();
			}
		 }
	 }

	 for(unsigned int j=0;j<block->history[i]->topInput.size();++j)
	 {
		 AnsiString tmp="NULL";
		 if (block->history[i]->topInput[j]->getData()!=NULL) tmp=block->history[i]->topInput[j]->getData()->getName();
		 TTreeNode *it=this->TreeView1->Items->AddChild(his,(block->history[i]->topInput[j]->input->getDescription().IsEmpty()?block->history[i]->topInput[j]->input->getName():block->history[i]->topInput[j]->input->getDescription())+" - "+tmp);
		 it->ImageIndex=3;
		 it->SelectedIndex=3;
		 if (block->history[i]->topInput[j]->getData()!=NULL)
		 {
			if (tdll==NULL||tdll->getType()!=block->history[i]->topInput[j]->getData()->getName()) {
			   tdll=plugins->getType(block->history[i]->topInput[j]->getData()->getName());
			}
			if (tdll!=NULL) {
			TFrame *fm=tdll->show(this, block->history[i]->topInput[j]->getData());
			fm->Name="item"+IntToStr(count++);
			fm->Align=alClient;
			fm->Hint=root->Text+" - "+his->Text+" - "+it->Text;
			it->Data=fm;
			if (toShow==block->history[i]->topInput[j]->input&&i==0)
			{
			   if (showFrame!=NULL) showFrame->Visible=false;
			   fm->Show();
			   Label1->Caption=fm->Hint;
			   showFrame=fm;
			} else fm->Hide();
			}
		 }
	 }

	 for(unsigned int j=0;j<block->history[i]->rightOutput.size();++j)
	 {
		 AnsiString tmp="NULL";
		 if (block->history[i]->rightOutput[j]->getData()!=NULL) tmp=block->history[i]->rightOutput[j]->getData()->getName();
		 TTreeNode *it=this->TreeView1->Items->AddChild(his,(block->history[i]->rightOutput[j]->output->getDescription().IsEmpty()?block->history[i]->rightOutput[j]->output->getName():block->history[i]->rightOutput[j]->output->getDescription())+" - "+tmp);
		 it->ImageIndex=4;
		 it->SelectedIndex=4;

		 if (block->history[i]->rightOutput[j]->getData()!=NULL)
		 {
			if (tdll==NULL||tdll->getType()!=block->history[i]->rightOutput[j]->getData()->getName()) {
			   tdll=plugins->getType(block->history[i]->rightOutput[j]->getData()->getName());
			}
			if (tdll!=NULL) {
			TFrame *fm=tdll->show(this, block->history[i]->rightOutput[j]->getData());
			fm->Name="item"+IntToStr(count++);
			fm->Align=alClient;
			fm->Hint=root->Text+" - "+his->Text+" - "+it->Text;
			it->Data=fm;
			if (toShow==block->history[i]->rightOutput[j]->output&&i==0)
			{
			   if (showFrame!=NULL) showFrame->Visible=false;
			   fm->Show();
			   Label1->Caption=fm->Hint;
			   showFrame=fm;
			} else fm->Hide();
			}
		 }
	 }

	 for(unsigned int j=0;j<block->history[i]->bottomOutput.size();++j)
	 {
		 AnsiString tmp="NULL";
		 if (block->history[i]->bottomOutput[j]->getData()!=NULL) tmp=block->history[i]->bottomOutput[j]->getData()->getName();
		 TTreeNode *it=this->TreeView1->Items->AddChild(his,(block->history[i]->bottomOutput[j]->output->getDescription().IsEmpty()?block->history[i]->bottomOutput[j]->output->getName():block->history[i]->bottomOutput[j]->output->getDescription())+" - "+tmp);
		 it->ImageIndex=5;
		 it->SelectedIndex=5;
		 if (block->history[i]->bottomOutput[j]->getData()!=NULL)
		 {
			if (tdll==NULL||tdll->getType()!=block->history[i]->bottomOutput[j]->getData()->getName()) {
			   tdll=plugins->getType(block->history[i]->bottomOutput[j]->getData()->getName());
			}
			if (tdll!=NULL) {
			TFrame *fm=tdll->show(this, block->history[i]->bottomOutput[j]->getData());
			fm->Name="item"+IntToStr(count++);
			fm->Align=alClient;
			fm->Hint=root->Text+" - "+his->Text+" - "+it->Text;
			it->Data=fm;
			if (toShow==block->history[i]->bottomOutput[j]->output&&i==0)
			{
			   if (showFrame!=NULL) showFrame->Visible=false;
			   fm->Show();
			   Label1->Caption=fm->Hint;
			   showFrame=fm;
			} else fm->Hide();
			}
		 }
	 }
   }
   root->Expand(true);
   this->TreeView1->Items->EndUpdate();
}

void __fastcall THistory::TreeView1Deletion(TObject *Sender, TTreeNode *Node)
{
   if (Node->Data!=NULL&&Node->ImageIndex>1)
   {
	   ((TFrame*)(Node->Data))->Visible=false;
	   delete ((TFrame*)(Node->Data));
   }
}
//---------------------------------------------------------------------------

void __fastcall THistory::BitBtn2Click(TObject *Sender)
{
	refresh(NULL);	
}
//---------------------------------------------------------------------------


void __fastcall THistory::TreeView1Click(TObject *Sender)
{
  if (TreeView1->Selected!=NULL)
  {
	if (TreeView1->Selected->ImageIndex>1)
	{
		if (TreeView1->Selected->Data==NULL)
			 Application->MessageBoxA("Brak podgl¹du, typ nie wspierany",TreeView1->Selected->Text.c_str(), MB_ICONWARNING | MB_OK);
		else
			{
				try{
				if (showFrame!=NULL) showFrame->Visible=false;
				((TFrame*)(TreeView1->Selected->Data))->Visible=true;
				showFrame=((TFrame*)(TreeView1->Selected->Data));
				}catch(...)
				{
				   refresh(NULL);
                }
			}
	}
  }
}
//---------------------------------------------------------------------------
void __fastcall THistory::CreateParams(Controls::TCreateParams &Params)
{
   TCustomForm::CreateParams(Params);
   Params.ExStyle=Params.ExStyle | WS_EX_APPWINDOW;
   Params.WndParent = GetDesktopWindow();
}
