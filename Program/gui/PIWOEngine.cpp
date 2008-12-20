#include <vcl.h>
#pragma hdrstop
#include "PIWOEngine.h"
#include "BlockValidateInputElement.h"
#include "BlockValidateOutputElement.h"
#pragma package(smart_init)

__fastcall PIWOEngine::PIWOEngine(TComponent* Owner)
	: TPanel(Owner)
{
  plugins=NULL;
  area=new PIWOMAINCLASSTYPE(this);
  area->Parent=this;
  area->Align=alClient;
  area->BorderStyle=bsNone;
  area->OnClick=onThisClick;
  //DoubleBuffered=true;
  //area->DoubleBuffered=true;
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

void PIWOEngine::validateBlock(VisualBlock *block, bool updateInputConnections)
{
  FunctionDLL *fun=plugins->getFunction(block->nameOfBlock);

  //zapamiêtaæ po³¹czenia przychodz¹ce, wychodz¹ce, kod b³êdu, opis, typ danych, wskaŸnik wejœcia, wyjœcia
  vector<BlockValidateInputElement*> inputHistory;
  vector<BlockValidateOutputElement*> outputHistory;

  if (updateInputConnections)
  {
	 for(unsigned int i=0;i<block->block.input.size();++i)
	 if (!block->block.input[i].getConnectedType().IsEmpty())
	 {
		BlockValidateInputElement *ih=new BlockValidateInputElement();
		ih->input=&(block->block.input[i]);
		ih->errorDescription=block->block.input[i].getErrorDescription();
		ih->errorCode=block->block.input[i].getErrorCode();
		ih->connection=NULL;
		//szukamy po³¹czenia
		for(unsigned int j=0;j<connections.size();++j)
		{
			if (connections[j]->inBlock==block&&connections[j]->input==&(block->block.input[i]))
			{
			   ih->connection=connections[j];
			   break;
			}
		}
		inputHistory.push_back(ih);
	 }
  }

	 for(unsigned int i=0;i<block->block.output.size();++i)
	 {
		BlockValidateOutputElement *oh=new BlockValidateOutputElement();
		oh->output=&(block->block.output[i]);
		oh->errorDescription=block->block.output[i].getErrorDescription();
		oh->errorCode=block->block.output[i].getErrorCode();
		oh->type=block->block.output[i].getOutputType();
		for(unsigned int j=0;j<connections.size();++j)
		{
			if (connections[j]->outBlock==block&&connections[j]->output==&(block->block.output[i]))
			{
			   oh->connections.push_back(connections[j]);
			}
		}
		outputHistory.push_back(oh);
	 }

   int ret=fun->validate(&(block->block));
   //sprawdziæ czy jakieœ po³¹czenia nie zosta³y "wyjebane"
   //i potem zaktualizowac je...
   
   if (updateInputConnections)
   {
	  while(inputHistory.size()>0)
	  {
		  //sprawdzic czy jest na nowej liscie
		  BlockInput* in=NULL;

		  for(unsigned int j=0;j<block->block.input.size();++j)
		  {
			  if (&(block->block.input[j])==inputHistory[0]->input)
			  {
				 in=&(block->block.input[j]);
				 break;
			  }
		  }

		 if (in!=NULL)
		 {
			//sprawdzamy czy dalej jest podpiêty typ pod niego
			if (in->getConnectedType().IsEmpty())
			{
			   //nic pod³¹czonego, wywalamy po³¹czenie
				for(unsigned int j=0;j<connections.size();++j)
				{
					if (connections[j]==inputHistory[0]->connection)
					{
						delete connections[j];
						connections.erase(connections.begin()+j);
					}
				}
			}
			else
			{
				//jest coœ pod³¹czonego, jeœli code, i error siê nie zgadzaj¹ to aktualizujemy
				if (in->getErrorCode()!=inputHistory[0]->input->getErrorCode()||in->getErrorDescription()!=inputHistory[0]->input->getErrorDescription())
				{
				   inputHistory[0]->connection->update();
				}
			}
		 }
		 else
		 {
			 for(unsigned int j=0;j<connections.size();++j)
			 {
				 if (connections[j]==inputHistory[0]->connection)
				 {
					delete connections[j];
					connections.erase(connections.begin()+j);
				 }
			 }
		 }

		 delete inputHistory[0];
		 inputHistory.erase(inputHistory.begin());
	  }
   }

   if (ret!=0) block->updateVisualComponents();

   //aktualizacja wyjœæ, tu ju¿ bêdzie przejebane :P
   //sprawdzamy które wyjœcia siê zmieni³y, i wrzucamy na wyjœcie je
   //1 - spisaæ bloczki
   //2 - zaktualizowaæ typ
   //3 - zvalidowaæ bloczki
   //4 - zaktualizowac ponownie po³¹czenia
   //lecimy tylko do tych bloczków w których zmieni³ siê typ
   vector<VisualBlock*> toCheck;
   while(outputHistory.size()>0)
   {
	  //sprawdzamy czy jest w spisie
	  BlockOutput* out=NULL;

		  for(unsigned int j=0;j<block->block.output.size();++j)
		  {
			  if (&(block->block.output[j])==outputHistory[0]->output)
			  {
				 out=&(block->block.output[j]);
				 break;
			  }
		  }

	   if (out!=NULL)
		 {
			//sprawdzamy czy dalej jest podpiêty typ pod niego
			//sprawdziæ czy typy siê zmieni³y
			if (out->getOutputType()!=outputHistory[0]->type)
			{
			   //zmieni³ siê typ - aktualizujemy bloki na po³¹czeniach i dodajemy je do listy sprawdzenia


				for(unsigned int j=0;j<connections.size();++j)
				{
					if (connections[j]==inputHistory[0]->connection)
					{
						delete connections[j];
						connections.erase(connections.begin()+j);
					}
				}
			}
			else
			{
				//jest coœ pod³¹czonego, jeœli code, i error siê nie zgadzaj¹ to aktualizujemy
				if (in->getErrorCode()!=inputHistory[0]->input->getErrorCode()||in->getErrorDescription()!=inputHistory[0]->input->getErrorDescription())
				{
				   inputHistory[0]->connection->update();
				}
			}
		 }
		 else
		 {
			 for(unsigned int j=0;j<connections.size();++j)
			 {
				 if (connections[j]==outputHistory[0]->connection)
				 {
					connections[j]->input->disconnect();
					toCheck.push_back(connections[j]->inBlock);
					delete connections[j];
					connections.erase(connections.begin()+j);
				 }
			 }
		 }

		 delete inputHistory[0];
		 inputHistory.erase(inputHistory.begin());
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

	bool canBe=false;
	for(unsigned int i=0;i<input->input->allowedTypes.size();++i)
	{
		if (output->output->getOutputType()==input->input->allowedTypes[i])
		{
			canBe=true;
			break;
		}
	}

	//zablokowanie cyklicznych po³¹czeñ
	if (outputBlock==inputBlock) {
	   if (OnError!=NULL) OnError(this, "Po³¹czenia cyklycznie s¹ zabronione");
		return false;
	}

	vector<VisualBlock*> iwasThere;
	vector<VisualBlock*> toCheck;
	toCheck.push_back(inputBlock);
	while(toCheck.size()>0)
	{
		//sprawdzamy wszystkie po³¹czenia wychodz¹ce z tego bloku, dodajemy je na liste
		for(unsigned int i=0;i<connections.size();++i)
		{
			if (connections[i]->outBlock==toCheck[0])
			{
				if (connections[i]->inBlock==outputBlock) {
				  //cykliczne
				  if (OnError!=NULL) OnError(this, "Po³¹czenia cyklycznie s¹ zabronione");
				  return false;
				}

				bool isOnList=false;
				for(unsigned int j=0;!isOnList&&j<toCheck.size();++j)
				{
				   if (toCheck[j]==connections[i]->inBlock) isOnList=true;
				}
				for(unsigned int j=0;!isOnList&&j<iwasThere.size();++j)
				{
				   if (iwasThere[j]==connections[i]->inBlock) isOnList=true;
				}

				if (!isOnList) toCheck.push_back(connections[i]->inBlock);
			}
		}

		iwasThere.push_back(toCheck[0]);
		toCheck.erase(toCheck.begin());
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


