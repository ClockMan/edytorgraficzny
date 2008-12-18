#include <vcl.h>
#pragma hdrstop
#include "PIWOEngine.h"
#pragma package(smart_init)

__fastcall PIWOEngine::PIWOEngine(TComponent* Owner)
	: TPanel(Owner)
{
  plugins=NULL;
  area=new TScrollBox(this);
  area->Parent=this;
  area->Align=alClient;
  area->BorderStyle=bsNone;
  area->OnClick=onThisClick;
  this->BorderStyle=bsNone;
  this->BevelOuter=bvLowered;
  this->BevelWidth=2;
  this->OnClick=onThisClick;
  selectedConnection=NULL;
  OnInformation=NULL;
  OnWarrning=NULL;
  OnError=NULL;
  selectedOutputBlock=NULL;
  selectedInputBlock=NULL;
  selectedInput=NULL;
  selectedOutput=NULL;
  Color=clMedGray;
}


__fastcall PIWOEngine::~PIWOEngine()
{
  while(connections.size()>0)
  {
	  delete connections[0];
	  connections.erase(connections.begin());
  }

  while(blocks.size()>0)
  {
	  delete blocks[0];
	  blocks.erase(blocks.begin());
  }
  delete area;
}


bool PIWOEngine::AddBlock(const AnsiString &name)
{
   FunctionDLL *fun=plugins->getFunction(name);
   if (fun==NULL) return false;
   //szukamy numerku.
   int number=0;
   bool busy;
   do{
	++number;
	busy=false;
	for(unsigned int i=0;i<blocks.size();++i)
	{
		if (blocks[i]->nameOfBlock==name && blocks[i]->numberOfBlock==number) {
		  busy=true;
		  break;
		}
	}
   } while (busy);

   VisualBlock *newBlock=new VisualBlock(this->area);
   newBlock->Parent=this->area;
   newBlock->nameOfBlock=name;
   newBlock->numberOfBlock=number;
   newBlock->setTitle(name+" #"+IntToStr(number));
   newBlock->setConfigButtonGlyph(fun->picture);
   newBlock->Hint=fun->fullName;
   if (fun->description!="") newBlock->Hint+="\n"+fun->description;
   newBlock->Left=10;
   newBlock->Top=10;
   fun->validate(&(newBlock->block));
   newBlock->updateVisualComponents();
   newBlock->Visible=true;
   newBlock->OnConfigClick=OnVisualBlockConfigClick;
   newBlock->OnVisualInputSelected=OnVisualBlockInputSelected;
   newBlock->OnVisualOutputSelected=OnVisualBlockOutputSelected;
   newBlock->OnVInputHistory=OnVisualBlockInputHistoryClick;
   newBlock->OnVOutputHistory=OnVisualBlockOutputHistoryClick;
   newBlock->OnBlockMove=OnVisualBlockMove;
   newBlock->OnUnselect=OnVisualBlockUnselect;
   newBlock->OnSelect=OnVisualBlockSelect;
   newBlock->OnSelectAdd=OnVisualBlockSelectAdd;
   blocks.push_back(newBlock);
   if (OnInformation!=NULL) OnInformation(this, "Dodano blok: "+name+" #"+IntToStr(number));
   return true;
}

void PIWOEngine::validateBlock(VisualBlock *block)
{
  FunctionDLL *fun=plugins->getFunction(block->nameOfBlock);
  //@TODO
  if (fun->validate(&(block->block))!=-1)        //TODO: powinno byæ !=0 ale dam chwilow na czas testów !=-1 (s¹ b³êdy w DLL)
	 block->updateVisualComponents();
  //aktualizujemy po³¹czenia.
  for(unsigned int i=0;i<connections.size();++i)
  {
	  if (connections[i]->outBlock==block) {
		  //jeœli jest to wyjœcie, to aktualizujemy po³¹czenie i jeœli typy siê niezgadzaj¹ to aktualizujemy te¿ inBlok
		  connections[i]->update();
	  }
	  else
	  if (connections[i]->inBlock==block) {
		 //jeœli jest to wejœcie, to wykonujemy requencyjnie, ale tylko wtedy gdy zmieni siê errorCode, errorDescription lub OutputType
		 connections[i]->update();
	  }
  }
}

void PIWOEngine::OnVisualBlockConfigClick(TObject* Sender)
{
   VisualBlock *block=(VisualBlock*)Sender;
   unsigned int rev=block->block.getConfig()->getRevision();
   FunctionDLL *fun=plugins->getFunction(block->nameOfBlock);
   if (!fun->showConfig(Application,&(block->block)))
   {
	  if (OnWarrning!=NULL) OnWarrning(this, "Blok: "+block->getTitle()+" nieposiada okna konfiguracji");
	  MessageBox(0,"Ten bloczek niema konfiguracji",("Konfiguracja bloczka: "+block->getTitle()).c_str(),MB_OK);
	  return;
   }
   if (rev!=block->block.getConfig()->getRevision())
   {
	 if (OnInformation!=NULL) OnInformation(this, "Zmodyfikowanao konfiguracje bloku: "+block->getTitle());
	 validateBlock(block);
   }
}

bool PIWOEngine::MakeConnection(VisualBlock* outputBlock, VisualOutput* output, VisualBlock* inputBlock, VisualInput* input)
{
	//sprawdzamy czy mo¿na pod³¹czyæ.

	if (outputBlock==inputBlock) {
       if (OnError!=NULL) OnError(this, "Po³¹czenia cyklycznie s¹ zabronione");
		return false;
	}
	bool canBe=false;
	for(unsigned int i=0;i<input->input->allowedTypes.size();++i)
	{
		if (output->output->getOutputType()==input->input->allowedTypes[i])
		{
			canBe=true;
			break;
		}
	}

	if (!canBe)
	{
		if (OnError!=NULL) OnError(this, "Po³¹czenie: "+outputBlock->getTitle()+"("+output->output->getDescription()+") -> "+inputBlock->getTitle()+"("+input->input->getDescription()+") niemo¿e zostaæ zrealizowane, pruba pod³¹czenia nieobs³ugiwanego typu danych");
		return false;
	}

	//ustawiamy po³¹czenie :P
	Connection* con=new Connection(this->area);
	con->input=input->input;
	con->inBlock=inputBlock;
	con->output=output->output;
	con->outBlock=outputBlock;
	con->OnConnectionSelected=OnConnectionSelect;
	input->input->connect(output->output->getOutputType());
	//aktualizacja bloku input
	con->draw();
	connections.push_back(con);
	validateBlock(inputBlock);
	return true;
}

void PIWOEngine::OnVisualBlockInputSelected(VisualInput* input,  TObject* Sender)
{
   //connection selecting
   Connection* con=getConnectionTo(input);
   if (con!=NULL)
   {
	 if (OnError!=NULL) OnError(this, "Po³¹czenie do tego wejœcia ju¿ istnieje "+con->outBlock->getTitle()+"("+con->output->getDescription()+") -> "+con->inBlock->getTitle()+"("+con->input->getDescription()+")");
	 return;
   }

	selectedInputBlock=(VisualBlock*)Sender;
	selectedInput=input;

   if (selectedOutputBlock!=NULL && selectedOutput!=NULL)
   {
	 if (MakeConnection(selectedOutputBlock,selectedOutput,selectedInputBlock,selectedInput))
	 {
		selectedOutputBlock=NULL;
		selectedInputBlock=NULL;
		selectedInput=NULL;
		selectedOutput=NULL;
	 }
   }
}

void PIWOEngine::OnVisualBlockOutputSelected(VisualOutput* output,  TObject* Sender)
{
	selectedOutputBlock=(VisualBlock*)Sender;
	selectedOutput=output;

   if (selectedInputBlock!=NULL && selectedInput!=NULL)
   {
	 if (MakeConnection(selectedOutputBlock,selectedOutput,selectedInputBlock,selectedInput))
	 {
		selectedOutputBlock=NULL;
		selectedInputBlock=NULL;
		selectedInput=NULL;
		selectedOutput=NULL;
	 }
   }
}

void PIWOEngine::OnVisualBlockInputHistoryClick(VisualInput* input, vectorBlockHistory* history)
{

}

void PIWOEngine::OnVisualBlockOutputHistoryClick(VisualOutput* output, vectorBlockHistory* history)
{

}

void PIWOEngine::OnVisualBlockMove(TObject* Sender, bool moveAll, int x, int y)
{
  //przesówanie bloków, jesli moveAll jest ustawione to przesuwamy all zaznaczone bloki, a jesli nie to tylko ten do ktorego dostalismy wskaŸnik (tzn dostajamy conneciton)
  if (moveAll)
  {
	for(unsigned int i=0;i<selectedBlocks.size();++i)
	{
	   if (selectedBlocks[i]!=Sender)
	   {
		 selectedBlocks[i]->Left+=x;
		 selectedBlocks[i]->Top+=y;
       }
    }
  }

  if (!moveAll)
  {
	  for(unsigned int i=0;i<connections.size();++i)
	  {
		 if (connections[i]->inBlock==Sender||connections[i]->outBlock==Sender) {
		   connections[i]->draw();
		 }
	  }
  }
  else
  {
	  for(unsigned int i=0;i<connections.size();++i)
	  {
		 if (connections[i]->inBlock==Sender||connections[i]->outBlock==Sender) {
		   connections[i]->draw();
		 }
	  }

	  for(unsigned int i=0;i<selectedBlocks.size();++i)
	  {
			for(unsigned int j=0;j<connections.size();++j)
			{
				if (connections[j]->inBlock==selectedBlocks[i]||connections[j]->outBlock==selectedBlocks[i]) {
					connections[j]->draw();
				}
			}
	  }
  }
}

void PIWOEngine::OnVisualBlockUnselect(TObject* Sender)
{
   //odznaczamy ten blok
   VisualBlock *block=(VisualBlock*)Sender;
   for(unsigned int i=0;i<selectedBlocks.size();++i)
   {
	   if (selectedBlocks[i]==block)
	   {
		  selectedBlocks.erase(selectedBlocks.begin()+i);
		  break;
	   }
   }
   if (OnInformation!=NULL) OnInformation(this, "Odznaczono blok: "+block->getTitle());
   block->setSelected(false);
}

void PIWOEngine::OnVisualBlockSelect(TObject* Sender)
{
   while(selectedBlocks.size()>0)
   {
	  if (selectedBlocks[0]!=Sender) {
	   if (OnInformation!=NULL) OnInformation(this, "Odznaczono blok: "+selectedBlocks[0]->getTitle());
	   selectedBlocks[0]->setSelected(false);
	  }
	  selectedBlocks.erase(selectedBlocks.begin());
   }

   for(unsigned int i=0;i<connections.size();++i)
   {
	   if (connections[i]->inBlock==Sender||connections[i]->outBlock==Sender)
			 connections[i]->BringToFront();
   }

   if (OnInformation!=NULL) OnInformation(this, "Zaznaczono blok: "+((VisualBlock*)Sender)->getTitle());
   selectedBlocks.push_back((VisualBlock*)Sender);
}

void PIWOEngine::OnVisualBlockSelectAdd(TObject* Sender)
{
   for(unsigned int i=0;i<selectedBlocks.size();++i)
   {
	  if (selectedBlocks[i]==Sender) return;
   }

   for(unsigned int i=0;i<connections.size();++i)
   {
	   if (connections[i]->inBlock==Sender||connections[i]->outBlock==Sender)
			 connections[i]->BringToFront();
   }

   if (OnInformation!=NULL) OnInformation(this, "Zaznaczono blok: "+((VisualBlock*)Sender)->getTitle());
   selectedBlocks.push_back((VisualBlock*)Sender);
}

void __fastcall PIWOEngine::onThisClick(TObject* Sender)
{
   while(selectedBlocks.size()>0)
   {
	  selectedBlocks[0]->setSelected(false);
	  if (OnInformation!=NULL) OnInformation(this, "Odznaczono blok: "+selectedBlocks[0]->getTitle());
	  selectedBlocks.erase(selectedBlocks.begin());
   }
}

void PIWOEngine::OnConnectionSelect(void* Sender)
{
   if (selectedConnection!=NULL)
   {
	  if (OnInformation!=NULL) OnInformation(this, "Odznaczono po³¹czenie: "+selectedConnection->outBlock->getTitle()+"("+selectedConnection->output->getDescription()+") -> "+selectedConnection->inBlock->getTitle()+"("+selectedConnection->input->getDescription()+")");
	  selectedConnection->setSelected(false);
   }
   selectedConnection=(Connection*)Sender;
   selectedConnection->BringToFront();
   if (OnInformation!=NULL) OnInformation(this, "Zaznaczono po³¹czenie: "+selectedConnection->outBlock->getTitle()+"("+selectedConnection->output->getDescription()+") -> "+selectedConnection->inBlock->getTitle()+"("+selectedConnection->input->getDescription()+")");
}

Connection* PIWOEngine::getConnectionTo(VisualInput* input)
{
   for(unsigned int i=0;i<connections.size();++i)
	   if (connections[i]->input==input->input) return connections[i];
   return NULL;
}


