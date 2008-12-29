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
  OnRunAllProgress=NULL;
  OnRunProgress=NULL;
  OnCompileProgress=NULL;
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
	 {
			BlockValidateInputElement *ih=new BlockValidateInputElement();
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
			if (ih->connection!=NULL)
						{
							ih->input=&(block->block.input[i]);
							ih->errorDescription=block->block.input[i].getErrorDescription();
							ih->errorCode=block->block.input[i].getErrorCode();
							inputHistory.push_back(ih);
						} else delete ih;
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
			//jest wejœcie
			//jest coœ pod³¹czonego, jeœli code, i error siê nie zgadzaj¹ to aktualizujemy
			//if (in->getErrorCode()!=inputHistory[0]->input->getErrorCode()||in->getErrorDescription()!=inputHistory[0]->input->getErrorDescription())
			{
				inputHistory[0]->connection->update();
			}
		 }
		 else
		 {
			 //niema wejœcia, wywalamy go razem z po³¹czeniami
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

   if (ret!=0) block->updateVisualComponents(); //aktualizujemy wyœwietlanie tylko gdy zmieni³ siê kod.
   block->updateHistory();

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
			//wyjœcie nie zosta³o usuniête...
			if (out->getOutputType()!=outputHistory[0]->type)
			{
			   //typ siê zmieni³, pentla po po³¹czeniach
			   for(unsigned int g=0;g<outputHistory[0]->connections.size();++g)
			   {
					//sprawdzamy czy nowey typ jest na liœcie
					bool isTypeOnList=false;
					for(unsigned int i=0;i<outputHistory[0]->connections[g]->input->allowedTypes.size();++i)
					{
						if (outputHistory[0]->connections[g]->input->allowedTypes[i]==out->getOutputType()) {
						   isTypeOnList=true;
						   break;
						}
					}


					if (isTypeOnList)
					{
					  //typ jest na liœcie, aktualizujemy typ i dodajemy blok do validacji
					  outputHistory[0]->connections[g]->input->connect(out->getOutputType());
					  outputHistory[0]->connections[g]->update();
					}
					else
					{
					   //wiêc od³¹czamy blok i przeprowadzamy validatcje po³¹czenia i bloku
					   outputHistory[0]->connections[g]->input->disconnect();
					   outputHistory[0]->connections[g]->inBlock->updateVisualComponents();
					   outputHistory[0]->connections[g]->update();
					}

					bool isOnList=false;
					for(unsigned int k=0;k<toCheck.size();++k)
					{
						if (toCheck[k]==outputHistory[0]->connections[g]->inBlock) {
						   isOnList=true;
						   break;
						}
					}
					if (!isOnList) toCheck.push_back(outputHistory[0]->connections[g]->inBlock);
			   }
			}
			else
			{
				//typy s¹ takie same, sprawdzamy kody b³êdów tylko
				if (out->getErrorCode()!=outputHistory[0]->output->getErrorCode()||out->getErrorDescription()!=outputHistory[0]->output->getErrorDescription())
				{
				   //zmieni³ siê kod b³êdu, aktualizujemy po³¹czenia
				   for(unsigned int g=0;g<outputHistory[0]->connections.size();++g)
				   {
					  outputHistory[0]->connections[g]->update();
				   }
				}
			}
		 }
		 else
		 {
			for(unsigned int k=0;k<outputHistory[0]->connections.size();++k)
			{
			 for(unsigned int j=0;j<connections.size();++j)
			 {
				 if (connections[j]==outputHistory[0]->connections[k])
				 {
					connections[j]->input->disconnect();
					toCheck.push_back(connections[j]->inBlock);
					delete connections[j];
					connections.erase(connections.begin()+j);
				 }
			 }
			}
		 }

		 delete outputHistory[0];
		 outputHistory.erase(outputHistory.begin());
   }

  for(unsigned int i=0;i<toCheck.size();++i)
  {
	validateBlock(toCheck[i], true);
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
	con->update();
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

void __fastcall PIWOEngine::HistoryFormClose(TObject *Sender, TCloseAction &Action)
{
	Action=caFree;
	for(unsigned int i=0;i<historyWindows.size();++i)
	{
		if (historyWindows[i]==Sender)
		{
		   historyWindows.erase(historyWindows.begin()+i);
		   break;
		}
	}
}

void PIWOEngine::OnVisualBlockInputHistoryClick(VisualInput* input, TObject* Sender)
{
   VisualBlock* block=(VisualBlock*)Sender;
   //sprawdzamy czy przypadkiem takie okienko ju¿ nie jest otwarte
   for(unsigned int i=0;i<historyWindows.size();++i)
   {
	  if (historyWindows[i]->block==block) {
		 historyWindows[i]->refresh(input->input);
		 historyWindows[i]->Show();
		 return;
	  }
   }

   //niema :P
   if (block->history.size()==0)
   {
	  Application->MessageBoxA("Brak historii",block->getTitle().c_str(), MB_ICONINFORMATION | MB_OK);
	  return;
   }

   THistory *his=new THistory(NULL);
   his->block=block;
   his->plugins=plugins;
   his->OnClose=HistoryFormClose;
   his->Show();
   his->refresh(input->input);
   historyWindows.push_back(his);
}

void PIWOEngine::OnVisualBlockOutputHistoryClick(VisualOutput* output, TObject* Sender)
{
   VisualBlock* block=(VisualBlock*)Sender;
   //sprawdzamy czy przypadkiem takie okienko ju¿ nie jest otwarte
   for(unsigned int i=0;i<historyWindows.size();++i)
   {
	  if (historyWindows[i]->block==block) {
		 historyWindows[i]->refresh(output->output);
		 historyWindows[i]->Show();
		 return;
	  }
   }

   //niema :P
   if (block->history.size()==0)
   {
	  Application->MessageBoxA("Brak historii",block->getTitle().c_str(), MB_ICONINFORMATION | MB_OK);
	  return;
   }

   THistory *his=new THistory(NULL);
   his->block=block;
   his->plugins=plugins;
   his->OnClose=HistoryFormClose;
   his->Show();
   his->refresh(output->output);
   historyWindows.push_back(his);
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
   UnselectAllBlocks();
   UnselectSelectedConnection();
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

bool PIWOEngine::DeleteBlock(const AnsiString &fullName)
{
	VisualBlock* toDelete=NULL;
	for(unsigned int i=0;i<blocks.size();++i)
	{
		if (blocks[i]->getTitle()==fullName) {
		   toDelete=blocks[i];
		   blocks.erase(blocks.begin()+i);
		   break;
		}
	}
	if (toDelete==NULL) return false;

    for(unsigned int j=0;j<connections.size();++j)
	{
		   if (connections[j]->inBlock==toDelete)
		   {
			  connections[j]->inBlock=NULL;
		   }
		   else
		   if (connections[j]->outBlock==toDelete)
		   {
			  connections[j]->outBlock=NULL;
		   }
	}

   vector<VisualBlock*> blocksToCheck;
   for(unsigned int j=0;j<connections.size();++j)
   {
	  //sprawdzamy wejœcia

	  if (connections[j]->inBlock!=NULL && connections[j]->outBlock==NULL)
	  {
		 connections[j]->input->disconnect();
		 bool isOnList=false;
		 for(unsigned int i=0;i<blocksToCheck.size();++i)
		 {
			 if (blocksToCheck[i]==connections[j]->inBlock)
			 {
				isOnList=true;
				break;
			 }
		 }
		 if (!isOnList) blocksToCheck.push_back(connections[j]->inBlock);
	  }
	  //sprawdzamy wyjœcia
	  if (connections[j]->outBlock!=NULL && connections[j]->inBlock==NULL)
	  {
		 bool isOnList=false;
		 for(unsigned int i=0;i<blocksToCheck.size();++i)
		 {
			 if (blocksToCheck[i]==connections[j]->outBlock)
			 {
				isOnList=true;
				break;
			 }
		 }
		 if (!isOnList) blocksToCheck.push_back(connections[j]->outBlock);
	  }

	  //usuwamy po³¹czenie
	  if (selectedConnection==connections[j]) selectedConnection=NULL;
	  delete connections[j];
	  connections.erase(connections.begin()+j);
	  --j;
   }

   delete toDelete;

   //sprawdzamy co wywalone..
   for(unsigned int i=0;i<blocksToCheck.size();++i)
   {
	   validateBlock(blocksToCheck[i]);
   }
   return true;
}

bool PIWOEngine::DeleteSelectedBlocks()
{
   if (selectedBlocks.size()==0) return false;

   for(unsigned int i=0;i<selectedBlocks.size();++i)
   {
	   //zaznaczam po³¹czenia do usuniêcia
	   for(unsigned int j=0;j<connections.size();++j)
	   {
		   if (connections[j]->inBlock==selectedBlocks[i])
		   {
			  connections[j]->inBlock=NULL;
		   }
		   else
		   if (connections[j]->outBlock==selectedBlocks[i])
		   {
			  connections[j]->outBlock=NULL;
		   }
	   }
   }

   for(unsigned int j=0;j<blocks.size();++j)
   {
	   if (blocks[j]->isSelected()) {
		  delete blocks[j];
		  blocks.erase(blocks.begin()+j);
		  ++j;
	   }
   }
   selectedBlocks.clear();

   vector<VisualBlock*> blocksToCheck;
   for(unsigned int j=0;j<connections.size();++j)
   {
	  //sprawdzamy wejœcia
	  bool toDelete=false;

	  if (connections[j]->inBlock!=NULL && connections[j]->outBlock==NULL)
	  {
		 connections[j]->input->disconnect();
		 toDelete=true;
		 bool isOnList=false;
		 for(unsigned int i=0;i<blocksToCheck.size();++i)
		 {
			 if (blocksToCheck[i]==connections[j]->inBlock)
			 {
				isOnList=true;
				break;
			 }
		 }
		 if (!isOnList) blocksToCheck.push_back(connections[j]->inBlock);
	  }
	  //sprawdzamy wyjœcia
	  if (connections[j]->outBlock!=NULL && connections[j]->inBlock==NULL)
	  {
		 toDelete=true;
		 bool isOnList=false;
		 for(unsigned int i=0;i<blocksToCheck.size();++i)
		 {
			 if (blocksToCheck[i]==connections[j]->outBlock)
			 {
				isOnList=true;
				break;
			 }
		 }
		 if (!isOnList) blocksToCheck.push_back(connections[j]->outBlock);
	  }

	  //usuwamy po³¹czenie
	  if (toDelete)
	  {
	  if (selectedConnection==connections[j]) selectedConnection=NULL;
	  delete connections[j];
	  connections.erase(connections.begin()+j);
	  --j;
	  }
   }

   //sprawdzamy co wywalone..
   for(unsigned int i=0;i<blocksToCheck.size();++i)
   {
	   validateBlock(blocksToCheck[i]);
   }
   return true;
}

bool PIWOEngine::DeleteAllBlocks()
{
   if (blocks.size()==0) return false;
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
   return true;
}

void PIWOEngine::SelectAllBlocks()
{
  for(unsigned int i=0;i<blocks.size();++i)
  {
	if (!blocks[i]->isSelected())
	{
	   selectedBlocks.push_back(blocks[i]);
	   blocks[i]->setSelected(true);
	}
  }
}

void PIWOEngine::InvertBlockSelection()
{
  vector<VisualBlock*> newSelections;
  for(unsigned int i=0;i<blocks.size();++i)
  {
	if (!blocks[i]->isSelected())
	{
	   newSelections.push_back(blocks[i]);
	   blocks[i]->setSelected(true);
	}
	else
	{
	   blocks[i]->setSelected(false);
    }
  }
  selectedBlocks=newSelections;
}

void PIWOEngine::UnselectAllBlocks()
{
   while(selectedBlocks.size()>0)
   {
	  selectedBlocks[0]->setSelected(false);
	  if (OnInformation!=NULL) OnInformation(this, "Odznaczono blok: "+selectedBlocks[0]->getTitle());
	  selectedBlocks.erase(selectedBlocks.begin());
   }
}

bool PIWOEngine::DeleteSelectedConnection()
{
   if (selectedConnection!=NULL)
   {
	  for(unsigned int i=0;i<connections.size();++i)
	  {
		if (connections[i]==selectedConnection)
		{
		   selectedConnection->input->disconnect();
		   VisualBlock* block=selectedConnection->inBlock;
		   delete connections[i];
		   connections.erase(connections.begin()+i);
		   validateBlock(block);
		   break;
		}
	  }
	  selectedConnection=NULL;
	  return true;
   } else return false;
}

bool PIWOEngine::DeleteAllConnections()
{
   if (connections.size()==0) return false;
   vector<VisualBlock*> list;
   while(connections.size()>0)
   {
	   bool isOnListToValidate=false;
	   for(unsigned int i=0;i<list.size();++i)
	   {
		  if (list[i]==connections[0]->inBlock)
		  {
			 isOnListToValidate=true;
			 break;
		  }
	   }

	   if (!isOnListToValidate) list.push_back(connections[0]->inBlock);
	   delete connections[0];
	   connections.erase(connections.begin());
   }
   selectedConnection=NULL;
   for(unsigned int i=0;i<list.size();++i)
   {
	   validateBlock(list[i]);
   }
   return true;
}

void PIWOEngine::UnselectSelectedConnection()
{
   if (selectedConnection!=NULL)
   {
	  selectedConnection->setSelected(false);
	  selectedConnection=NULL;
   }
}

void PIWOEngine::CancelCustomizationOnSelectedConnections()
{
   if (selectedConnection!=NULL)
   {
	  selectedConnection->setCustomizeFalse();
   }
}

void PIWOEngine::CancelCustomizationOnAllConnections()
{
	for(unsigned int i=0;i<connections.size();++i)
	{
	   connections[i]->setCustomizeFalse();
    }
}

bool PIWOEngine::run()
{
  bool status=true;
	//usuwamy status runned, przetwa¿amy zaczynaj¹c od najstarszego bloku, czyœcimy dane, w sumie mo¿emy zostawiæ dane które widnia³y po ostatniej operacji
	for(unsigned int i=0;i<blocks.size();++i)
	{
		blocks[i]->runned=false;
		for(unsigned int j=0;j<blocks[i]->leftInput.size();++j)
		{
		   blocks[i]->leftInput[j]->input->clearObject();
		}

		for(unsigned int j=0;j<blocks[i]->topInput.size();++j)
		{
		   blocks[i]->topInput[j]->input->clearObject();
		}

		for(unsigned int j=0;j<blocks[i]->rightOutput.size();++j)
		{
		   blocks[i]->rightOutput[j]->output->clearObject();
		}

		for(unsigned int j=0;j<blocks[i]->bottomOutput.size();++j)
		{
		   blocks[i]->bottomOutput[j]->output->clearObject();
		}
	}

	for(unsigned int i=0;i<blocks.size();++i)
	{
		bool toRun=true;
		for(unsigned int j=0;j<connections.size();++j)
		{
			if (connections[j]->outBlock==blocks[i]&&!connections[j]->input->getConnectedType().IsEmpty()) {
				toRun=false;
				break;
			}
		}

		if (toRun)
		{
		   bool useHistory=true;
		   if (!runBlock(blocks[i], false, &useHistory)) status=false;
		}
	}
	return status;
}

bool PIWOEngine::runAll()
{
  bool status=true;
	//usuwamy status runned, przetwa¿amy zaczynaj¹c od najstarszego bloku, czyœcimy dane, w sumie mo¿emy zostawiæ dane które widnia³y po ostatniej operacji
	for(unsigned int i=0;i<blocks.size();++i)
	{
		blocks[i]->runned=false;
		for(unsigned int j=0;j<blocks[i]->leftInput.size();++j)
		{
		   blocks[i]->leftInput[j]->input->clearObject();
		}

		for(unsigned int j=0;j<blocks[i]->topInput.size();++j)
		{
		   blocks[i]->topInput[j]->input->clearObject();
		}

		for(unsigned int j=0;j<blocks[i]->rightOutput.size();++j)
		{
		   blocks[i]->rightOutput[j]->output->clearObject();
		}

		for(unsigned int j=0;j<blocks[i]->bottomOutput.size();++j)
		{
		   blocks[i]->bottomOutput[j]->output->clearObject();
		}
	}

	for(unsigned int i=0;i<blocks.size();++i)
	{
		bool toRun=true;
		for(unsigned int j=0;j<connections.size();++j)
		{
			if (connections[j]->outBlock==blocks[i]&&!connections[j]->input->getConnectedType().IsEmpty()) {
				toRun=false;
				break;
			}
		}

		if (toRun)
		{
		   bool useHistory=false;
		   if (!runBlock(blocks[i], false, &useHistory)) status=false;
		}
	}
	return status;
}

bool PIWOEngine::compile()
{
	//do napisania potem - nazwa siê zmieni
	return false;
}

bool PIWOEngine::runBlock(VisualBlock* block, bool fastRun, bool *useHistory)
{
	/*
		Algorytm:
		* za³o¿enie: aby bloczek by³ przetworzony musi byæ przynajmniej jedno wejœcie z kodem 0 gdy bloczek posiada wejœcia i przynajmniej jedno wyjœcie z kodem 0 gdy bloczek posiada wyjœcia.
		* za³o¿enie: wejœcia do których pod³¹czony typ nie spe³nia wymagañ jest uznawane jako wejœcie z kodem 1 i nie pod³¹czonym blokiem. [zaktualizowaæ w wyswietlaniu bloku i po³¹czenia, aby nie widzia³ blok po³¹czenia]
		* za³o¿enie: uruchamiamy wszystkie bloki jakie siê da.
		- uruchamiamy bloki od których jesteœmy zale¿ni (requencyjnie) - jeœli nie zosta³y jeszcze uruchomione):
			- sprawdzamy czy blok by³ ju¿ uruchomiony, jeœli nie to uruchamiamy
			- pobieramy dane z wyjœæ bloku, jeœli dane s¹ równe NULL to znaczy ¿e blok nie zosta³ uruchomiony - przerywamy
			- kopiujemy dane na wejœcie
		- sprawdzamy czy bloczke mo¿e byæ uruchomiony, ma conajmniej jedno poprawne wejœcie i jedno poprawne wyjœcie [o ile ma], jak nie to wywalamy warrning
		- jeœli fastRun jest ustawione na true i useHistory=true i mamy dane w histori to je uzywamy, jeœli niemamy danych w histori to upewniamy siê ¿e histora niemo¿e zostaæ u¿yta.
		- uruchamiamy blok
		- sprawdzamy kod b³êdu
		- sprawdzamy dane wyjœciowe bloczka
		- ustawiamy dane na wyjœciach o ile s¹ poprawne, jak nie to nie ustawiamy
		- przeprowadzamy validacje bloczka
		- ustawiamy historie
		- zwracamy true
	*/

	//sprawdzamy dane wejsciowe.
	//@TODO, powiniœym sprawdzaæ po wejœcia left/top/right/bottom, ale to nie ejst narazie ziamplementowane, dgy bêdzie czêœc tej funkcji bêdzie wymaga³a przeróbki.
	for(unsigned int i=0;i<block->block.input.size();++i)
	{
		if (!block->block.input[i].getConnectedType().IsEmpty())
		{
		   //znajdujemy po³¹czenie odpowiedizalne za to wejœcie
		   Connection *con=NULL;
		   for(unsigned int j=0;j<connections.size();++j)
		   {
			   if (connections[j]->input==&block->block.input[i])
			   {
				  con=connections[j];
				  break;
			   }
		   }

		   if (con!=NULL)
		   {
			  //jest po³¹czenie, sprawdzamy czy na danym bloku s¹ dane
			  con->update();
			  TypeConfig *data=con->output->getObject();
			  if (data!=NULL)
			  {
				  //mamy dane wiêc je kopiujemy.
				  //sprawdzamy czy dane s¹ odpowiedniego typu
				  if (data->getName()==block->block.input[i].getConnectedType()) {
					 block->block.input[i].setObject(*data);
				  }
				  else
				  {
					  if (OnError!=NULL) {
						 OnError(this, "Otrzymano b³êdne dane na wejœciu "+block->block.input[i].getDescription()+" bloku "+block->getTitle()+", oczekiwano: "+block->block.input[i].getConnectedType()+", otrzymano: "+data->getName());
					  }
					  block->setStatusColor(clYellow);
					  return false;
				  }
			  }
			  else
			  {
				  //niema danych :(
				  //sprawdzamy czy blok by³ uruchamiany
				  if (con->outBlock->runned) {
					  //by³ uruchamiany, trudno, wywalamy warrning i przerywamy wykonywanie
					  if (OnError!=NULL) {
						 OnError(this, "Brak wymaganych danych na wejœciu do bloku: "+block->getTitle());
					  }
					  block->setStatusColor(clYellow);
					  return false;
				  }
				  else
				  {
					  //uruchamiamy blok :D
					  if (!runBlock(con->outBlock, fastRun, useHistory))
					  {
						  //blok nie zosta³ uruchomiony, ale pech
						  if (OnError!=NULL) {
							OnError(this, "Blok nadrzêdny "+con->outBlock->getTitle()+" dla "+block->getTitle()+" nie zosta³ uruchomiony - brak wymaganych danych wejœciowych");
						  }
						  block->setStatusColor(clYellow);
						  return false;
					  }
					  else
					  {
						  //a jednak siê uruchomi³, ale fux :d, sprawdzamy czy mamy te dane
                          TypeConfig *data=con->output->getObject();
						  if (data!=NULL)
						  {
							//mamy dane wiêc je kopiujemy.
							//sprawdzamy czy dane s¹ odpowiedniego typu
							if (data->getName()==block->block.input[i].getConnectedType()) {
								 block->block.input[i].setObject(*data);
							}
							else
							{
								  if (OnError!=NULL) {
									 OnError(this, "Otrzymano b³êdne dane na wejœciu "+block->block.input[i].getDescription()+" bloku "+block->getTitle()+", oczekiwano: "+block->block.input[i].getConnectedType()+", otrzymano: "+data->getName());
								  }
								  block->setStatusColor(clYellow);
								  return false;
							}
						  }
						  else
						  {
							  //by³ uruchamiany, trudno, wywalamy warrning i przerywamy wykonywanie
							 if (OnError!=NULL) {
								OnError(this, "Brak wymaganych danych na wejœciu do bloku: "+block->getTitle());
							 }
							 block->setStatusColor(clYellow);
							 return false;
						  }
					  }
				  }
              }
		   }
		   else
		   {
			  //niema po³¹czenia ? jakim cudem
			  if (OnError!=NULL) {
				 OnError(this, "Brak wymaganych danych na wejœciu do bloku (nie znale¿iono po³¹czenia): "+block->getTitle());
			  }
			  block->setStatusColor(clYellow);
			  return false;
           }
		}
	}

	//Mamy ju¿ dane wejœciowe (fuxem)
	//niebêde tu sprawdza³ danych wyjœciowych :d
	//teraz sprawdzimy historie i uruchomimy bloczek D:
	BlockHistory *history=NULL;
	if (*useHistory)
	{
	   //u¿ywamy histori, sprawdzamy czy jest taka
	   //jeœli wskaŸniki wejœciowe siê zgadzaj¹, zgadza siê ich revision, zgadza siê revision bloku konfiguracyjnego to niemusze odpalaæ bloku.
	   //wyszukujemy historie :D  sprawdzamy tylko right i left, top i bottom nie zaimplementowane
	   for(unsigned int i=0;i<block->history.size();++i)
	   {
		   bool ok=true;
		   //sprawdzamy wersje konfiguracji
		   if (block->block.getConfig()->getRevision()!=block->history[i]->configRevision) ok=false;
		   if (block->history[i]->leftInput.size()!=block->leftInput.size()) ok=false;
		   if (block->history[i]->rightOutput.size()!=block->rightOutput.size()) ok=false;
		   if (block->history[i]->topInput.size()!=block->topInput.size()) ok=false;
		   if (block->history[i]->bottomOutput.size()!=block->bottomOutput.size()) ok=false;

		   for(unsigned int j=0;ok&&j<block->history[i]->leftInput.size();++j)
		   {
			  if (block->history[i]->leftInput[j]->input==block->leftInput[j]->input)
			  {
				if (block->history[i]->leftInput[j]->getData()!=NULL&&block->leftInput[j]->input->getObject()!=NULL)
				{
				   if ((block->history[i]->leftInput[j]->getData()->getName()!=block->leftInput[j]->input->getObject()->getName())||
					   (block->history[i]->leftInput[j]->getData()->getId()!=block->leftInput[j]->input->getObject()->getId())||
					   (block->history[i]->leftInput[j]->getData()->getRevision()!=block->leftInput[j]->input->getObject()->getRevision()))
				   {
                      ok=false; 
				   }
				}
				else
				if (!(block->history[i]->leftInput[j]->getData()==NULL&&block->leftInput[j]->input->getObject()==NULL))
				{
				  ok=false;
                }
			  } else ok=false;
		   }

		   for(unsigned int j=0;ok&&j<block->history[i]->topInput.size();++j)
		   {
			  if (block->history[i]->topInput[j]->input==block->topInput[j]->input)
			  {
				if (block->history[i]->topInput[j]->getData()!=NULL&&block->topInput[j]->input->getObject()!=NULL)
				{
				   if ((block->history[i]->topInput[j]->getData()->getName()!=block->topInput[j]->input->getObject()->getName())||
					   (block->history[i]->topInput[j]->getData()->getId()!=block->topInput[j]->input->getObject()->getId())||
					   (block->history[i]->topInput[j]->getData()->getRevision()!=block->topInput[j]->input->getObject()->getRevision()))
				   {
                      ok=false; 
				   }
				}
				else
				if (!(block->history[i]->topInput[j]->getData()==NULL&&block->topInput[j]->input->getObject()==NULL))
				{
					ok=false;
				}
			  } else ok=false;
		   }

		   for(unsigned int j=0;ok&&j<block->history[i]->rightOutput.size();++j)
		   {
			  if (block->history[i]->rightOutput[j]->output==block->rightOutput[j]->output)
			  {
				if (block->history[i]->rightOutput[j]->getData()!=NULL&&block->rightOutput[j]->output->getObject()!=NULL)
				{
				   if ((block->history[i]->rightOutput[j]->getData()->getName()!=block->rightOutput[j]->output->getObject()->getName())||
					   (block->history[i]->rightOutput[j]->getData()->getId()!=block->rightOutput[j]->output->getObject()->getId())||
					   (block->history[i]->rightOutput[j]->getData()->getRevision()!=block->rightOutput[j]->output->getObject()->getRevision()))
				   {
                      ok=false; 
				   }
				}
				else
				if (!(block->history[i]->rightOutput[j]->getData()==NULL&&block->rightOutput[j]->output->getObject()==NULL))
				{
					ok=false;
				}
			  } else ok=false;
		   }

           for(unsigned int j=0;ok&&j<block->history[i]->bottomOutput.size();++j)
		   {
			  if (block->history[i]->bottomOutput[j]->output==block->bottomOutput[j]->output)
			  {
				if (block->history[i]->bottomOutput[j]->getData()!=NULL&&block->bottomOutput[j]->output->getObject()!=NULL)
				{
				   if ((block->history[i]->bottomOutput[j]->getData()->getName()!=block->bottomOutput[j]->output->getObject()->getName())||
					   (block->history[i]->bottomOutput[j]->getData()->getId()!=block->bottomOutput[j]->output->getObject()->getId())||
					   (block->history[i]->bottomOutput[j]->getData()->getRevision()!=block->bottomOutput[j]->output->getObject()->getRevision()))
				   {
                      ok=false; 
				   }
				}
				else
				if (!(block->history[i]->bottomOutput[j]->getData()==NULL&&block->bottomOutput[j]->output->getObject()==NULL))
				{
					ok=false;
				}
			  } else ok=false;
		   }

		   if (ok)
		   {
			   history=block->history[i];
			   block->history.erase(block->history.begin()+i); //dodamy potem hitorie na samym pocz¹tku
			   break;
		   }
       }
	   
	}
	else
	{
		//czyœcimy historie gdy niewolno nam jej u¿ywaæ.
		while (block->history.size()>0)
		{
		  delete block->history[0];
		  block->history.erase(block->history.begin());
		}
	}

	//@TODO rozwa¿yæ u¿ycie histori dla bloków nie posiadaj¹cych wyjœcia, czyli np dla bloczków z³u¿¹cych do zapisu obrazu do pliku [mo¿liwe ¿e te bloki zostan¹ w przysz³oœci usuniête]
	if (history!=NULL) {
		//mamy historie, inicjujemy wyjœcia i zwracamy true, i wrzucamy historie z powrotem na stos :d
		for(unsigned int i=0;i<history->rightOutput.size();++i)
		{
		  if (history->rightOutput[i]->getData()==NULL) {
			history->rightOutput[i]->output->clearObject();
		  }
		  else
		  {
			history->rightOutput[i]->output->setObject(*history->rightOutput[i]->getData());
		  }
		}

		for(unsigned int i=0;i<history->bottomOutput.size();++i)
		{
		  if (history->bottomOutput[i]->getData()==NULL) {
			history->bottomOutput[i]->output->clearObject();
		  }
		  else
		  {
			history->bottomOutput[i]->output->setObject(*history->bottomOutput[i]->getData());
		  }
		}

		block->history.insert(block->history.begin(),history);
		//u¿yliœmy histori, powiadamiamy o tym
		if (OnInformation!=NULL) {
			 OnInformation(this, "Blok "+block->getTitle()+" zosta³ przetworzony w oparciu o dane historyczne");
		}
		block->setStatusColor(clGreen);
		return true;
	}

	//niemamy histori wiêc jeszcze bêdziemy musieli siê sporo pobawiæ.
	//zak³adamy ¿e wejscia mamy ju¿ wype³nione wykonujemy nastêpuj¹ce ruchy:
	FunctionDLL *fn=plugins->getFunction(block->nameOfBlock);
	if (OnInformation!=NULL) {
			 OnInformation(this, "Uruchamiam blok: "+block->getTitle());
	}
	int ret=fn->run(&(block->block));
	block->runned=true;
	block->updateVisualComponents();
	if (ret!=0&&ret!=1) {
		//wystapi³ b³¹d, usuwamy dane
		for(unsigned int i=0;i<block->block.output.size();++i)
		{
		   block->block.output[i].clearObject();
		}
		if (OnError!=NULL)
				OnError(this, "Blok "+block->getTitle()+" nie zosta³ przetwo¿ony - b³¹d wewnêtrzny");
		block->setStatusColor(clRed);
		return false;
	}

	//kod b³êdu 1 lub 0, spradziæ wyjœæia, skopiowaæ do histori, etc
	history=new BlockHistory();
	history->configRevision=block->block.getConfig()->getRevision();
	//kopiujemy wejœcia do histori:
	for(unsigned int i=0;i<block->leftInput.size();++i)
	{
		BlockHistoryInputElement *hi=new BlockHistoryInputElement();
		hi->input=block->leftInput[i]->input;
		TypeConfig *tp=block->leftInput[i]->input->getObject();
		if (tp!=NULL)
		{
		   hi->setData(*tp);
		}
		else
		{
		   hi->setNULL();
		}
		history->leftInput.push_back(hi);
	}

	for(unsigned int i=0;i<block->topInput.size();++i)
	{
		BlockHistoryInputElement *hi=new BlockHistoryInputElement();
		hi->input=block->topInput[i]->input;
		TypeConfig *tp=block->topInput[i]->input->getObject();
		if (tp!=NULL)
		{
		   hi->setData(*tp);
		}
		else
		{
		   hi->setNULL();
		}
		history->topInput.push_back(hi);
	}

	//sprawdziæ poprawnoœæ danych na wyjœciu:
	TypeDLL *tdll=NULL;
	for(unsigned int i=0;i<block->block.output.size();++i)
	{
		TypeConfig *tc=block->block.output[i].getObject();
		if (tc==NULL && !block->block.output[i].getOutputType().IsEmpty())
		{
			//niema danych, a powinny jakieœ byæ. - tylko warrning
			if (OnWarrning!=NULL)
				OnWarrning(this, "Brak danych na wyjœciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+", oczekiwano "+block->block.output[i].getOutputType());
		} else
		if(tc!=NULL&&block->block.output[i].getOutputType().IsEmpty())
		{
		  //niechiceliœmy danych, a dostaliœmy.
		  if (OnWarrning!=NULL)
				OnWarrning(this, "Otrzymano nieoczekiwane dane na wyjœciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+" typu "+tc->getName()+", dane zosta³y pominiête");
		  block->block.output[i].clearObject();
		  tc=NULL;
		} else
		if (tc!=NULL)
		{
		   //mamy dane, sprawdzamy czy s¹ tego typu jakiego oczekiwaliœmy.
		   if (tc->getName()!=block->block.output[i].getOutputType())
		   {
			  //otrzyma³em b³êdne dane, warrning
			  if (OnWarrning!=NULL)
				OnWarrning(this, "Otrzymano b³êdne dane na wyjœciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+", otrzymano: "+tc->getName()+", oczekiwano: "+block->block.output[i].getOutputType()+", dane zosta³y pominiête");
			  block->block.output[i].clearObject();
			  tc=NULL;
		   }
		   else
		   {
			   //validacja typu :d, a nó¿ ktoœ siê bawi³ :P
			   if (tdll==NULL||(tdll!=NULL&&tdll->getType()!=tc->getName()))
			   {
				  tdll=plugins->getType(tc->getName());
			   }

			   if (tdll==NULL)
			   {
				  //niema DLL typu, pomijamy sprawdzenie, wywalamy warrning
				  if (OnWarrning!=NULL)
					OnWarrning(this, "Otrzymano niewzpierany typ danych na wyjœciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+", typu: "+tc->getName());
			   }
			   else
			   {
				  if (!tdll->isValid(tc))
				  {
					 //dane nie s¹ poprawne, wywalamy
					if (OnWarrning!=NULL)
						OnWarrning(this, "Otrzymano b³êdne dane na wyjœciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+", typu: "+tc->getName()+", dane s¹ niepoprawne i zosta³y pominiête");
					block->block.output[i].clearObject();
					tc=NULL;
				  }
			   }
		   }
		}
	}

	//update histori wyjœcia.
	for(unsigned int i=0;i<block->rightOutput.size();++i)
	{
		BlockHistoryOutputElement *hi=new BlockHistoryOutputElement();
		hi->output=block->rightOutput[i]->output;
		TypeConfig *tp=block->rightOutput[i]->output->getObject();
		if (tp!=NULL)
		{
		   hi->setData(*tp);
		}
		else
		{
		   hi->setNULL();
		}
		history->rightOutput.push_back(hi);
	}

	for(unsigned int i=0;i<block->bottomOutput.size();++i)
	{
		BlockHistoryOutputElement *hi=new BlockHistoryOutputElement();
		hi->output=block->bottomOutput[i]->output;
		TypeConfig *tp=block->bottomOutput[i]->output->getObject();
		if (tp!=NULL)
		{
		   hi->setData(*tp);
		}
		else
		{
		   hi->setNULL();
		}
		history->bottomOutput.push_back(hi);
	}

	//dodajemy historie :D
	block->history.push_back(history);
	block->setStatusColor(clGreen);
	return true;
}
