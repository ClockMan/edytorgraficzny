#include <vcl.h>
#pragma hdrstop
#include "VisualBlock.h"
#pragma package(smart_init)

__fastcall VisualBlock::VisualBlock(TComponent* Owner)
	: TPanel(Owner)
{
	Caption="�adowanie";
	BevelWidth = 2;
	Width=80;
	Height=60;
	selected=false;
	moving=false;
	BevelOuter=bvRaised;
	BevelInner=bvNone;
	ShowHint=true;
	//DoubleBuffered=true;

	OnClick=BlockClick;
	OnMouseUp=BlockMouseUp;
	OnMouseDown=BlockMouseDown;
	OnMouseMove=BlockMouseMove;

	nameOfBlock="";
	numberOfBlock=0;
	status=new TPanel(this);
	status->Parent=this;
	status->OnClick=BlockClick;
	status->OnMouseUp=BlockMouseUp;
	status->OnMouseDown=BlockMouseDown;
	status->OnMouseMove=BlockMouseMove;
	status->Height=40;
	status->Width=42;
	status->Caption="";
	status->BevelOuter=bvLowered;
	status->BevelInner=bvNone;
	status->Color=clGray;
	status->Visible=false;

	configButton=new TSpeedButton(status);
	configButton->Parent=status;
	configButton->Height=34;
	configButton->Width=36;
	configButton->Left=3;
	configButton->Top=3;
	configButton->Caption="";
	configButton->Transparent=false;
	configButton->Layout=blGlyphTop;
	configButton->Flat=false;
	configButton->Margin=0;
	configButton->Spacing=0;
	configButton->OnClick=SpeedButtonClick;
	configButton->Visible=false;

	title=new TLabel(this);
	title->Parent=this;
	title->Visible=false;
	title->ShowHint=true;
	title->Font->Name="Arial Narrow";
	title->Font->Size=8;
	title->Font->Style=TFontStyles()<<fsBold;
	title->Caption="";
	title->AutoSize=false;
	title->Height=13;
	title->Alignment=taCenter;
	title->OnClick=BlockClick;
	title->OnMouseUp=BlockMouseUp;
	title->OnMouseDown=BlockMouseDown;
	title->OnMouseMove=BlockMouseMove;
	title->Transparent=true;

	OnVisualInputSelected=NULL;
	OnVisualOutputSelected=NULL;
	OnVInputHistory=NULL;
	OnVOutputHistory=NULL;
	OnBlockMove=NULL;
	OnUnselect=NULL;
	OnSelect=NULL;
	OnSelectAdd=NULL;

	runned=false;
}

__fastcall VisualBlock::~VisualBlock()
{
   while(leftInput.size()>0)
   {
	   delete leftInput[0];
	   leftInput.erase(leftInput.begin());
   }

   while(topInput.size()>0)
   {
	   delete topInput[0];
	   topInput.erase(topInput.begin());
   }

   while(rightOutput.size()>0)
   {
	   delete rightOutput[0];
	   rightOutput.erase(rightOutput.begin());
   }

   while(bottomOutput.size()>0)
   {
	   delete bottomOutput[0];
	   bottomOutput.erase(bottomOutput.begin());
   }

   while(history.size()>0)
   {
	   delete history[0];
	   history.erase(history.begin());
   }

   delete configButton;
   delete status;
   delete title;
}

Position VisualBlock::getInputPosition(BlockInput* object)
{
   Position tmp;
   unsigned int i;


   for(i=0;i<leftInput.size();i++)
   {
	  if (leftInput[i]->input==object)
	  {
		  //znale�iono
		  tmp.direction=0;
		  tmp.xy.y=this->Top+leftInput[i]->Top+int(leftInput[i]->Height/2);
		  tmp.xy.x=this->Left;
		  return tmp;
	  }
   }

   for(i=0;i<topInput.size();i++)
   {
	  if (topInput[i]->input==object)
	  {
		  //znale�iono
		  tmp.direction=1;
		  tmp.xy.y=this->Top;
		  tmp.xy.x=this->Left+topInput[i]->Left+int(topInput[i]->Width/2);
		  return tmp;
	  }
   }

   tmp.direction=4;
   return tmp;
}

Position VisualBlock::getOutputPosition(BlockOutput* object)
{
   Position tmp;
   unsigned int i;


   for(i=0;i<rightOutput.size();i++)
   {
	  if (rightOutput[i]->output==object)
	  {
		  //znale�iono
		  tmp.direction=2;
		  tmp.xy.y=this->Top+rightOutput[i]->Top+int(rightOutput[i]->Height/2);
		  tmp.xy.x=this->Left+this->Width;
		  return tmp;
	  }
   }

   for(i=0;i<bottomOutput.size();i++)
   {
	  if (bottomOutput[i]->output==object)
	  {
		  //znale�iono
		  tmp.direction=3;
		  tmp.xy.y=this->Top+this->Height;
		  tmp.xy.x=this->Left+bottomOutput[i]->Left+int(bottomOutput[i]->Width/2);
		  return tmp;
	  }
   }

   tmp.direction=4;
   return tmp;
}

void __fastcall VisualBlock::SpeedButtonClick(TObject *Sender)
{
   if (OnConfigClick!=NULL) {
	  OnConfigClick(this);
   }
}

bool VisualBlock::setConfigButtonGlyph(Graphics::TBitmap *bmp)
{
   if (bmp==NULL) return false;
   configButton->Glyph=bmp;
   return true;
}

void VisualBlock::setTitle(const AnsiString &s)
{
   title->Caption=s;
   title->Hint=s;
   block.title=s;
}

AnsiString VisualBlock::getTitle()
{
   return title->Caption;
}

bool VisualBlock::updateVisualComponents()
{
   //aktualizacja wej��, wyj��
   bool ret=false;
   Caption="";
   title->Visible=true;
   configButton->Visible=true;
   status->Visible=true;
   //pomijamy wej�cia u g�ry i u do�u, to s� wej�cia wirtualne
   //aktualizacja obiekt�w
   vector<VisualInput*> leftInputTmp;
   vector<VisualOutput*> rightOutputTmp;
   unsigned int i;

   for(i=0;i<block.input.size();i++)
   {
	  VisualInput *tmp=NULL;
	  for(unsigned int j=0;j<leftInput.size();j++)
	  {
		  if (leftInput[j]->input==&(block.input[i]))
		  {
			 tmp=leftInput[j];
			 leftInput.erase(leftInput.begin()+j);
			 break;
		  }
	  }
	  if (tmp==NULL) {
		 tmp=new VisualInput(this);
		 tmp->Parent=this;
		 tmp->input=&(block.input[i]);
		 tmp->OnClick=InputSelected;
		 tmp->OnShowHistory=InputShowHistory;
		 ret=true;
	  }

	  if (tmp->Color==clGreen&&tmp->input->getErrorCode()!=0) ret=true;
	  if (tmp->Color==clYellow&&tmp->input->getErrorCode()!=1) ret=true;
	  if (tmp->Color==clRed&&tmp->input->getErrorCode()!=2) ret=true;

	  if (tmp->input->getErrorCode()==0)
			tmp->Color=clGreen;
	  else
	  if (tmp->input->getErrorCode()==1)
			tmp->Color=clYellow;
	  else
			tmp->Color=clRed;

	 AnsiString txt=tmp->input->getDescription();
	 if (!txt.IsEmpty()) txt+="\n";
	 txt+="Dozwolone typy danych na wej�ciu:\n";
	 for(unsigned int i=0;i<tmp->input->allowedTypes.size();i++)
		txt+=" - "+tmp->input->allowedTypes[i]+"\n";
	 if (!tmp->input->getConnectedType().IsEmpty())
		txt+="Pod��czony typ danych:\n - "+(tmp->input->getConnectedType())+"\n";
	 txt+="Status: ";
	 if (tmp->input->getErrorCode()==0) {
		 txt+="OK";
	 } else
	 if (tmp->input->getErrorCode()==1) {
		 txt+="Ostrze�enie";
		 if (!tmp->input->getErrorDescription().IsEmpty()) {
		   txt+=" ("+tmp->input->getErrorDescription()+")";
		 }
	 } else
	 {
	   txt+="B��d";
        if (!tmp->input->getErrorDescription().IsEmpty()) {
		   txt+=" ("+tmp->input->getErrorDescription()+")";
		 }
	 }
	 tmp->Hint=txt;
	 leftInputTmp.push_back(tmp);
   }

   //wyj�cia
   for(i=0;i<block.output.size();i++)
   {
	  VisualOutput *tmp=NULL;
	  for(unsigned int j=0;j<rightOutput.size();j++)
	  {
		  if (rightOutput[j]->output==&(block.output[i]))
		  {
			 tmp=rightOutput[j];
			 rightOutput.erase(rightOutput.begin()+j);
			 break;
		  }
	  }
	  if (tmp==NULL) {
		 tmp=new VisualOutput(this);
		 tmp->Parent=this;
		 tmp->output=&(block.output[i]);
		 tmp->OnClick=OutputSelected;
		 tmp->OnShowHistory=OutputShowHistory;
		 ret=true;
	  }

	  if (tmp->Color==clGreen&&tmp->output->getErrorCode()!=0) ret=true;
	  if (tmp->Color==clYellow&&tmp->output->getErrorCode()!=1) ret=true;
	  if (tmp->Color==clRed&&tmp->output->getErrorCode()!=2) ret=true;

	  if (tmp->output->getErrorCode()==0)
			tmp->Color=clGreen;
	  else
	  if (tmp->output->getErrorCode()==1)
			tmp->Color=clYellow;
	  else
			tmp->Color=clRed;

	 AnsiString txt=tmp->output->getDescription();
	 if (!txt.IsEmpty()) txt+="\n";
	 txt+="Typ danych:\n - "+(tmp->output->getOutputType())+"\n";
	 txt+="Status: ";
	 if (tmp->output->getErrorCode()==0) {
		 txt+="OK";
	 } else
	 if (tmp->output->getErrorCode()==1) {
		 txt+="Ostrze�enie";
		 if (!tmp->output->getErrorDescription().IsEmpty()) {
		   txt+=" ("+tmp->output->getErrorDescription()+")";
		 }
	 } else
	 {
	   txt+="B��d";
		if (!tmp->output->getErrorDescription().IsEmpty()) {
		   txt+=" ("+tmp->output->getErrorDescription()+")";
		 }
	 }
	 tmp->Hint=txt;
	 rightOutputTmp.push_back(tmp);
   }

   while(leftInput.size()>0)
   {
	 delete leftInput[0];
	 leftInput.erase(leftInput.begin());
   }
   while(rightOutput.size()>0)
   {
	 delete rightOutput[0];
	 rightOutput.erase(rightOutput.begin());
   }

   leftInput=leftInputTmp;
   rightOutput=rightOutputTmp;

   resizeAll();
   return ret;
}

bool VisualBlock::updateHistory()
{
   if (history.size()==0) return false;
   for(unsigned int i=0;i<history.size();++i)
   {
	 if ((history[i]->leftInput.size()!=leftInput.size())||
		(history[i]->rightOutput.size()!=rightOutput.size())||
		(history[i]->topInput.size()!=topInput.size())||
		(history[i]->bottomOutput.size()!=bottomOutput.size())||history[i]->configRevision!=block.getConfig()->getRevision())
	 {
	   delete history[i];
	   history.erase(history.begin()+i);
	   i--;
	   continue;
	 }
	 else
	 {
		 unsigned int j;
		 bool end=false;
		 for(j=0;((j<leftInput.size())&&(!end));--j)
			if ((history[i]->leftInput[j]->input!=leftInput[j]->input)&&
			   (history[i]->leftInput[j]->getData()->getName()!=leftInput[j]->input->getConnectedType()))
				end=true;
		 for(j=0;((j<topInput.size())&&(!end));--j)
			if ((history[i]->topInput[j]->input!=topInput[j]->input)&&
			   (history[i]->topInput[j]->getData()->getName()!=topInput[j]->input->getConnectedType()))
				end=true;
		 for(j=0;((j<rightOutput.size())&&(!end));--j)
			if ((history[i]->rightOutput[j]->output!=rightOutput[j]->output)&&
			   (history[i]->rightOutput[j]->getData()->getName()!=rightOutput[j]->output->getOutputType()))
				end=true;
		 for(j=0;((j<bottomOutput.size())&&(!end));--j)
			if ((history[i]->bottomOutput[j]->output!=bottomOutput[j]->output)&&
			   (history[i]->bottomOutput[j]->getData()->getName()!=bottomOutput[j]->output->getOutputType()))
				end=true;
		 if (end) {
			delete history[i];
			history.erase(history.begin()+i);
			i--;
			continue;
		 }
	 }
   }
   return true;
}

void VisualBlock::resizeAll()
{
	unsigned top_bottom=topInput.size();
	if (bottomOutput.size()>top_bottom) top_bottom=bottomOutput.size();

	unsigned width=status->Width+10+(2*17)+2;
	if (((topInput.size()*17)+(topInput.size()>0?(topInput.size()-1)*1:0)+4+(2*17)+2)>width)
	  width=(topInput.size()*17)+(topInput.size()>0?(topInput.size()-1)*1:0)+4+(2*17)+2;
	if (((bottomOutput.size()*17)+(bottomOutput.size()>0?(bottomOutput.size()-1)*1:0)+4+(2*17)+2)>width)
	  width=(bottomOutput.size()*17)+(bottomOutput.size()>0?(bottomOutput.size()-1)*1:0)+4+(2*17)+2;

	Width=width;
	unsigned int height=1;
	//Paski na g�rze
	if (topInput.size()>0) {
		int w=(topInput.size()*17)+(topInput.size()>0?(topInput.size()-1)*1:0);
		int i=int((Width-w)/2);
		for(unsigned int j=0;j<topInput.size();j++)
		{
		  topInput[j]->Top=height;
		  topInput[j]->Left=i;
		  i+=18;
		}
		height+=2+17;
	}
	title->Left=1;
	title->Top=height;
	title->Width=Width-2;
	height+=title->Height+2;

	unsigned int lh=(leftInput.size()*17)+(leftInput.size()>0?(leftInput.size()-1)*1:0);
	unsigned int rh=(rightOutput.size()*17)+(rightOutput.size()>0?(rightOutput.size()-1)*1:0);
	int height2=(lh>rh)?lh:rh;
	//prawe, lewe
	if (leftInput.size()>0) {
		int i=0;
		for(unsigned int j=0;j<leftInput.size();j++)
		{
		  leftInput[j]->Top=height+i;
		  leftInput[j]->Left=2;
		  i+=18;
		}
	}

	if (rightOutput.size()>0) {
		int i=0;
		for(unsigned int j=0;j<rightOutput.size();j++)
		{
		  rightOutput[j]->Top=height+i;
		  rightOutput[j]->Left=Width-2-17;
		  i+=18;
		}
	}

	//przycisk
	if (height2<status->Height) height2=status->Height;
	status->Top=int(height+(height2-status->Height)/2);
	status->Left=int((Width/2)-(status->Width/2));
	height+=height2+2;

	//dolny pasek
	if (bottomOutput.size()>0) {
		height+=3;
		int w=(bottomOutput.size()*17)+(bottomOutput.size()>0?(bottomOutput.size()-1)*1:0);
		int i=int((Width-w)/2);
		for(unsigned int j=0;j<bottomOutput.size();j++)
		{
		  bottomOutput[j]->Top=height;
		  bottomOutput[j]->Left=i;
		  i+=18;
		}
	}
	height+=2;
	Height=height;
}

void __fastcall VisualBlock::InputSelected(TObject *Sender)
{
   if (OnVisualInputSelected==NULL) return;
	  OnVisualInputSelected((VisualInput*)Sender, this);
}

void __fastcall VisualBlock::OutputSelected(TObject *Sender)
{
	if (OnVisualOutputSelected==NULL) return;
	   OnVisualOutputSelected((VisualOutput*)Sender, this);
}

void VisualBlock::InputShowHistory(TObject *Sender)
{
	if (OnVInputHistory==NULL) return;
	   OnVInputHistory((VisualInput*)Sender, this);
}

void VisualBlock::OutputShowHistory(TObject *Sender)
{
	if (OnVOutputHistory==NULL) return;
		OnVOutputHistory((VisualOutput*)Sender, this);
}

void VisualBlock::setSelected(bool status)
{
  if (status) {
	 selected=true;
	 BevelInner=bvLowered;
  }
  else
  {
	BevelInner=bvNone;
	selected=false;
  }
}

bool VisualBlock::isSelected()
{
    return selected;
}

void __fastcall VisualBlock::BlockClick(TObject *Sender)
{
	if (!moving)
	{
	  if (ctrlDown()&&!altDown())
	  {
		 if (selected)
		 {
			if (OnUnselect!=NULL) OnUnselect(this);
			setSelected(false);
		 }
		 else
		 {
			if (OnSelectAdd!=NULL) OnSelectAdd(this);
			setSelected(true);
		 }
	  }
	  else
	  {
		  if (OnSelect!=NULL) OnSelect(this);
		  setSelected(true);
	  }
	}
}

void __fastcall VisualBlock::BlockMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   //przes�wanie aktywuje: prawy przycisk myszy, lewy przycisk myszy z shiftem, prawy przycisk myszy pozawala na przes�wanie jednego obiektu bez zaznaczania
   this->BringToFront();
   
   if ((Button==mbLeft)&&(Shift.Contains(ssShift)))
   {
		if(!selected)
		{
			if (Shift.Contains(ssCtrl)&&!Shift.Contains(ssAlt))
			{
				if (OnSelectAdd!=NULL) OnSelectAdd(this);
				setSelected(true);
			}
			else
			{
				if (OnSelect!=NULL) OnSelect(this);
				setSelected(true);
			}
		}
		else
		{
			if (!(Shift.Contains(ssCtrl)&&!Shift.Contains(ssAlt))&&OnSelect!=NULL)
				  OnSelect(this);
		}

	   GetCursorPos(&oldPoint);
	   Screen->Cursor=crSizeAll;
	   moving=true;

	   ((PIWOMAINCLASSTYPE*)this->Parent)->OnMouseUp=BlockMouseUp;
	   ((PIWOMAINCLASSTYPE*)this->Parent)->OnMouseMove=BlockMouseMove;
	   button=true;
   }
   else
   if (Button==mbRight)
   {
	   GetCursorPos(&oldPoint);
	   Screen->Cursor=crSizeAll;
	   moving=true;
	   button=false;
	   
	   ((PIWOMAINCLASSTYPE*)this->Parent)->OnMouseUp=BlockMouseUp;
	   ((PIWOMAINCLASSTYPE*)this->Parent)->OnMouseMove=BlockMouseMove;
   }
}

void __fastcall VisualBlock::BlockMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
   moving=false;
   Screen->Cursor=crDefault;
   ((PIWOMAINCLASSTYPE*)this->Parent)->OnMouseUp=NULL;
   ((PIWOMAINCLASSTYPE*)this->Parent)->OnMouseMove=NULL;
}

void __fastcall VisualBlock::BlockMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	if (moving&&!((Shift.Contains(ssShift)&&Shift.Contains(ssLeft))||Shift.Contains(ssRight)))
	{
		moving=false;
		Screen->Cursor=crDefault;
		return;
	}

	if (!moving) return;

	TPoint cl;
	GetCursorPos(&cl);
	this->Left=this->Left+cl.x-oldPoint.x;
	this->Top=this->Top+cl.y-oldPoint.y;

	if (button) {
	   //przenoszenie all
	   if (OnBlockMove!=NULL)
				OnBlockMove(this, true ,cl.x-oldPoint.x,cl.y-oldPoint.y);
	}
	else
	{
	   //przenoszenie all
	   if (OnBlockMove!=NULL)
				OnBlockMove(this, (Shift.Contains(ssCtrl)&&!Shift.Contains(ssAlt)) ,cl.x-oldPoint.x,cl.y-oldPoint.y);
	}
	oldPoint=cl;
}

void VisualBlock::setStatusColor(TColor cl)
{
	status->Color=cl;
}

bool ctrlDown()
{
  TKeyboardState State;
  GetKeyboardState(State);
  return (State[VK_CONTROL]&128);
}

bool altDown()
{
  TKeyboardState State;
  GetKeyboardState(State);
  return (State[VK_MENU]&128);
}
