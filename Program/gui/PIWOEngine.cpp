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
  selectedOutputBlock=NULL;
  selectedInputBlock=NULL;
  selectedInput=NULL;
  selectedOutput=NULL;
  Color=clMedGray;

  isRunning=false;
  stopRunning=false;
  alwaysRun=false;
  runProgress=0;

  OnInformation=NULL;
  OnDebug=NULL;
  OnSuccess=NULL;
  OnWarrning=NULL;
  OnError=NULL;

  OnRunInformation=NULL;
  OnRunSuccess=NULL;
  OnRunWarrning=NULL;
  OnRunError=NULL;
  OnRunDebug=NULL;

  OnRunProgress=NULL;
  OnRunStart=NULL;
  OnRunEnd=NULL;
  changed=false;
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
   if (fun==NULL)
   {
	  if (OnDebug!=NULL) OnDebug(this,"Dodawanie bloku: Nieznaleziono pluginu o nazwie: "+name);
	  return false;
   }
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
   abort(true);
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
   newBlock->setSelected(true);
   validateBlock(newBlock);
   newBlock->Visible=true;
   if (OnInformation!=NULL) OnInformation(this, "Dodano blok: "+name+" #"+IntToStr(number));
   OnVisualBlockSelect(newBlock);
   changed=true;if (OnChanged!=NULL) OnChanged(this);
   if (alwaysRun) run();
   return true;
}

void PIWOEngine::validateBlock(VisualBlock *block, bool updateInputConnections)
{
  if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Rozpoczeto");
  FunctionDLL *fun=plugins->getFunction(block->nameOfBlock);
  //zapami�ta� po��czenia przychodz�ce, wychodz�ce, kod b��du, opis, typ danych, wska�nik wej�cia, wyj�cia
  vector<BlockValidateInputElement*> inputHistory;
  vector<BlockValidateOutputElement*> outputHistory;

  if (updateInputConnections)
  {
	 for(unsigned int i=0;i<block->block.input.size();++i)
	 {
			BlockValidateInputElement *ih=new BlockValidateInputElement();
			ih->connection=NULL;
			//szukamy po��czenia
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
							if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Zapami�tuje ustawienia wej�cia: "+block->block.input[i].getName()+" ("+block->block.input[i].getDescription()+") - "+IntToStr(i));
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
		if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Zapami�tuje ustawienia wyj�cia: "+block->block.output[i].getName()+" ("+block->block.output[i].getDescription()+") - "+IntToStr(i));
	 }


	int ret=2;
	try {
	ret=fun->validate(&(block->block));
	}
	catch (Exception &exception)
	{
		if (OnError!=NULL) OnError(this,"Validacja bloku "+block->getTitle()+" - B��d wewn�trzny: "+StringReplace(exception.Message, "\n", " ", TReplaceFlags() << rfReplaceAll));
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			if (OnError!=NULL) OnError(this,"Validacja bloku "+block->getTitle()+" - B��d wewn�trzny: "+StringReplace(exception.Message, "\n", " ", TReplaceFlags() << rfReplaceAll));
		}
	}

   if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Validator zwr�ci� kod "+IntToStr(ret)+(ret==0?" (OK)":" (CHANGED)"));
   //sprawdzi� czy jakie� po��czenia nie zosta�y "wyjebane"
   //i potem zaktualizowac je...
   
   if (updateInputConnections)
   {
	  int g=0;
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
			//jest wej�cie
			//jest co� pod��czonego, je�li code, i error si� nie zgadzaj� to aktualizujemy
			//if (in->getErrorCode()!=inputHistory[0]->input->getErrorCode()||in->getErrorDescription()!=inputHistory[0]->input->getErrorDescription())
			{
				inputHistory[0]->connection->update();
			}
		 }
		 else
		 {
			 //niema wej�cia, wywalamy go razem z po��czeniami
			 for(unsigned int j=0;j<connections.size();++j)
			 {
				 if (connections[j]==inputHistory[0]->connection)
				 {
					delete connections[j];
					connections.erase(connections.begin()+j);
				 }
			 }
			 if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Usuwam po��czenia z by�ego wej�cia o id: "+IntToStr(g));
		 }

		 delete inputHistory[0];
		 inputHistory.erase(inputHistory.begin());
		 ++g;
	  }
   }

   if (ret!=0)
   {
	 changed=true;if (OnChanged!=NULL) OnChanged(this);
	 block->updateVisualComponents(); //aktualizujemy wy�wietlanie tylko gdy zmieni� si� kod.
		if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Zaktualizowano wygl�d bloku");
   }
   block->updateHistory();
   if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Sprawdzono historie");

   //aktualizacja wyj��, tu ju� b�dzie przejebane :P
   //sprawdzamy kt�re wyj�cia si� zmieni�y, i wrzucamy na wyj�cie je
   //1 - spisa� bloczki
   //2 - zaktualizowa� typ
   //3 - zvalidowa� bloczki
   //4 - zaktualizowac ponownie po��czenia
   //lecimy tylko do tych bloczk�w w kt�rych zmieni� si� typ
   vector<VisualBlock*> toCheck;
   int g=0;
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
			//wyj�cie nie zosta�o usuni�te...
			if (out->getOutputType()!=outputHistory[0]->type)
			{
			   //typ si� zmieni�, pentla po po��czeniach
			   for(unsigned int g=0;g<outputHistory[0]->connections.size();++g)
			   {
					//sprawdzamy czy nowey typ jest na li�cie
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
					  //typ jest na li�cie, aktualizujemy typ i dodajemy blok do validacji
					  outputHistory[0]->connections[g]->input->connect(out->getOutputType());
					  outputHistory[0]->connections[g]->update();
					}
					else
					{
					   //wi�c od��czamy blok i przeprowadzamy validatcje po��czenia i bloku
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
					if (!isOnList)
					{
					  if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Blok : "+outputHistory[0]->connections[g]->inBlock->getTitle()+" wymaga validacji, dodaje go do listy.");
					  toCheck.push_back(outputHistory[0]->connections[g]->inBlock);
					}
			   }
			}
			else
			{
				//typy s� takie same, sprawdzamy kody b��d�w tylko
				if (out->getErrorCode()!=outputHistory[0]->output->getErrorCode()||out->getErrorDescription()!=outputHistory[0]->output->getErrorDescription())
				{
				   //zmieni� si� kod b��du, aktualizujemy po��czenia
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
			if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Usuwam po��czenia z by�ego wyj�cia o id: "+IntToStr(g));
		 }

		 delete outputHistory[0];
		 outputHistory.erase(outputHistory.begin());
   }

  if (toCheck.size()>0) {
	  if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Rozpoczynam validacje blok�w pochodnych");
  }
  for(unsigned int i=0;i<toCheck.size();++i)
  {
	validateBlock(toCheck[i], true);
  }
  if (toCheck.size()>0) {
	  if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Zako�czono validacje blok�w pochodnych");
  }

  if (OnDebug!=NULL) OnDebug(this,"Validacja bloku "+block->getTitle()+" - Zako�czono");
}

void PIWOEngine::OnVisualBlockConfigClick(TObject* Sender)
{
   VisualBlock *block=(VisualBlock*)Sender;
   abort();
   unsigned int rev=block->block.getConfig()->getRevision();
   FunctionDLL *fun=plugins->getFunction(block->nameOfBlock);
   try
   {
	if (!fun->showConfig(Application,&(block->block)))
	{
	  if (OnWarrning!=NULL) OnWarrning(this, "Konfiguracja bloku "+block->getTitle()+" - nieposiada okna konfiguracji");
	  MessageBox(0,"Ten bloczek niema konfiguracji",("Konfiguracja bloczka: "+block->getTitle()).c_str(),MB_OK);
	  return;
	}
   }
	catch (Exception &exception)
	{
		if (OnError!=NULL) OnError(this,"Konfiguracja bloku "+block->getTitle()+" - B��d wewn�trzny: "+StringReplace(exception.Message, "\n", " ", TReplaceFlags() << rfReplaceAll));
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			if (OnError!=NULL) OnError(this,"Konfiguracja bloku "+block->getTitle()+" - B��d wewn�trzny: "+StringReplace(exception.Message, "\n", " ", TReplaceFlags() << rfReplaceAll));
		}
	}

   if (rev!=block->block.getConfig()->getRevision())
   {
	 changed=true;if (OnChanged!=NULL) OnChanged(this);
	 if (OnDebug!=NULL) OnDebug(this,"Konfiguracja bloku "+block->getTitle()+" - Zmodyfikowano konfiguracje bloku");
	 if (OnDebug!=NULL) OnDebug(this,"Konfiguracja bloku "+block->getTitle()+" - Rozpoczynam wymagan� validacje bloku");
	 validateBlock(block);
	 if (OnDebug!=NULL) OnDebug(this,"Konfiguracja bloku "+block->getTitle()+" - Zako�czono wymagan� validacje bloku");
	 if (alwaysRun) run();
   }
}

bool PIWOEngine::MakeConnection(VisualBlock* outputBlock, VisualOutput* output, VisualBlock* inputBlock, VisualInput* input)
{
	//sprawdzamy czy mo�na pod��czy�.
	if (OnDebug!=NULL) OnDebug(this, "Tworzenie po��czenia "+outputBlock->getTitle()+"("+output->output->getDescription()+") -> "+inputBlock->getTitle()+"("+input->input->getDescription()+") - Rozpoczeto");
	bool canBe=false;
	for(unsigned int i=0;i<input->input->allowedTypes.size();++i)
	{
		if (output->output->getOutputType()==input->input->allowedTypes[i])
		{
			canBe=true;
			break;
		}
	}

	//zablokowanie cyklicznych po��cze�
	if (outputBlock==inputBlock) {
		if (OnError!=NULL) OnError(this, "Tworzenie po��czenia "+outputBlock->getTitle()+"("+output->output->getDescription()+") -> "+inputBlock->getTitle()+"("+input->input->getDescription()+") - Po��czenia cykliczne s� zabronione");
		return false;
	}

	vector<VisualBlock*> iwasThere;
	vector<VisualBlock*> toCheck;
	toCheck.push_back(inputBlock);
	while(toCheck.size()>0)
	{
		//sprawdzamy wszystkie po��czenia wychodz�ce z tego bloku, dodajemy je na liste
		for(unsigned int i=0;i<connections.size();++i)
		{
			if (connections[i]->outBlock==toCheck[0])
			{
				if (connections[i]->inBlock==outputBlock) {
				  //cykliczne
				  if (OnError!=NULL) OnError(this, "Tworzenie po��czenia "+outputBlock->getTitle()+"("+output->output->getDescription()+") -> "+inputBlock->getTitle()+"("+input->input->getDescription()+") - Po��czenia cykliczne s� zabronione");
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

				if (!isOnList)
				{
				  toCheck.push_back(connections[i]->inBlock);
				}
			}
		}
		iwasThere.push_back(toCheck[0]);
		toCheck.erase(toCheck.begin());
	}

	if (!canBe)
	{
		if (OnError!=NULL) OnError(this, "Tworzenie po��czenia "+outputBlock->getTitle()+"("+output->output->getDescription()+") -> "+inputBlock->getTitle()+"("+input->input->getDescription()+") - Pr�ba pod��czenia nieobs�ugiwanego typu danych, przerwano");
		return false;
	}

	//ustawiamy po��czenie :P
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
	con->setSelected(true);
	changed=true;if (OnChanged!=NULL) OnChanged(this);
	if (OnInformation!=NULL) OnInformation(this, "Dodano po��czenie "+outputBlock->getTitle()+"("+output->output->getDescription()+") -> "+inputBlock->getTitle()+"("+input->input->getDescription()+")");
	OnConnectionSelect(con);
	if (OnDebug!=NULL) OnDebug(this, "Tworzenie po��czenia "+outputBlock->getTitle()+"("+output->output->getDescription()+") -> "+inputBlock->getTitle()+"("+input->input->getDescription()+") - Zako�czono");
	return true;
}

void PIWOEngine::OnVisualBlockInputSelected(VisualInput* input,  TObject* Sender)
{
   //connection selecting
   bool runs=false;
   Connection* con=getConnectionTo(input);
   if (selectedOutput!=NULL&&con!=NULL)
   {
	 if (con->output==selectedOutput->output)
	 {
		selectedOutputBlock=NULL;
		selectedInputBlock=NULL;
		selectedInput=NULL;
		selectedOutput=NULL;
	   return;
	 }
	 if (selectedOutputBlock==(VisualBlock*)Sender)
	 {
		selectedOutputBlock=NULL;
		selectedInputBlock=NULL;
		selectedInput=NULL;
		selectedOutput=NULL;
	   return;
	 }
	 //pytanie, i ewentualnie wyjebujemy to po��czenie D:
	 if (Application->MessageBoxA(("Czy chcesz aby istniej�ce po��czenie: \n"+con->outBlock->getTitle()+"("+con->output->getDescription()+") -> "+con->inBlock->getTitle()+"("+con->input->getDescription()+")\n zosta�o zastapione przez:\n"+selectedOutputBlock->getTitle()+"("+selectedOutput->output->getDescription()+") -> "+con->inBlock->getTitle()+"("+con->input->getDescription()+")\n o ile jest to mo�liwe wykonanie takiego po��czenia ?").c_str(),"Po��czenie ju� istnieje",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES) {
			//odczepiamy
			abort(true);
			con->input->disconnect();
			for(unsigned int i=0;i<connections.size();++i)
			{
				if (connections[i]==con) {
				   connections.erase(connections.begin()+i);
				   break;
				}
			}
			delete con;
			con=NULL;
			validateBlock((VisualBlock*)Sender);
			changed=true;if (OnChanged!=NULL) OnChanged(this);
			runs=true;
		}
		else
		{
			selectedOutputBlock=NULL;
			selectedInputBlock=NULL;
			selectedInput=NULL;
			selectedOutput=NULL;
			return;
		}
   }
   
	selectedInputBlock=(VisualBlock*)Sender;
	selectedInput=input;

   if (selectedOutputBlock!=NULL && selectedOutput!=NULL)
   {
	 abort(true);
	 runs=true;
	 if (MakeConnection(selectedOutputBlock,selectedOutput,selectedInputBlock,selectedInput))
	 {
		selectedOutputBlock=NULL;
		selectedInputBlock=NULL;
		selectedInput=NULL;
		selectedOutput=NULL;

	 }
   }
   if (alwaysRun&&runs) run();
}

void PIWOEngine::OnVisualBlockOutputSelected(VisualOutput* output,  TObject* Sender)
{
	bool runs=false;
	selectedOutputBlock=(VisualBlock*)Sender;
	selectedOutput=output;

	if (selectedInput!=NULL) {
		Connection* con=getConnectionTo(selectedInput);
		if (con!=NULL)
		{
			if (con->output==selectedOutput->output)
			{
			  selectedInputBlock=NULL;
			  selectedInput=NULL;
			  return;
			}
			if (selectedOutputBlock==selectedInputBlock)
			{
				selectedOutputBlock=NULL;
				selectedInputBlock=NULL;
				selectedInput=NULL;
				selectedOutput=NULL;
				return;
			}
			//pytanie, i ewentualnie wyjebujemy to po��czenie D:
		if (Application->MessageBoxA(("Czy chcesz aby istniej�ce po��czenie: \n"+con->outBlock->getTitle()+"("+con->output->getDescription()+") -> "+con->inBlock->getTitle()+"("+con->input->getDescription()+")\n zosta�o zastapione przez:\n"+selectedOutputBlock->getTitle()+"("+selectedOutput->output->getDescription()+") -> "+con->inBlock->getTitle()+"("+con->input->getDescription()+")\n o ile jest to mo�liwe wykonanie takiego po��czenia ?").c_str(),"Po��czenie ju� istnieje",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDYES) {
			//odczepiamy
			abort(true);
			runs=true;
			con->input->disconnect();
			for(unsigned int i=0;i<connections.size();++i)
			{
				if (connections[i]==con) {
				   connections.erase(connections.begin()+i);
				   break;
				}
			}
			delete con;
			con=NULL;
			validateBlock((VisualBlock*)Sender);
			changed=true;if (OnChanged!=NULL) OnChanged(this);
		}
		else
		{
			selectedOutputBlock=NULL;
			selectedInputBlock=NULL;
			selectedInput=NULL;
			selectedOutput=NULL;
			return;
		}
	  }
   }

   if (selectedInputBlock!=NULL && selectedInput!=NULL)
   {
	 abort(true);
	 if (MakeConnection(selectedOutputBlock,selectedOutput,selectedInputBlock,selectedInput))
	 {
		selectedOutputBlock=NULL;
		selectedInputBlock=NULL;
		selectedInput=NULL;
		selectedOutput=NULL;
	 }
	 runs=true;
   }
   if (alwaysRun&&runs) run();
}

void __fastcall PIWOEngine::HistoryFormClose(TObject *Sender, TCloseAction &Action)
{
	Action=caFree;
	for(unsigned int i=0;i<historyWindows.size();++i)
	{
		if (historyWindows[i]==Sender)
		{
		   if (OnDebug!=NULL) OnDebug(this, "Historia "+historyWindows[i]->block->getTitle()+" - Zamkni�to okno");
		   historyWindows.erase(historyWindows.begin()+i);
		   break;
		}
	}
}

void PIWOEngine::OnVisualBlockInputHistoryClick(VisualInput* input, TObject* Sender)
{
   VisualBlock* block=(VisualBlock*)Sender;
   if (OnDebug!=NULL) OnDebug(this, "Historia "+block->getTitle()+" - Otrzymano rz�danie histori dla wej�cia "+input->input->getName()+" ("+input->input->getDescription()+")");
   //sprawdzamy czy przypadkiem takie okienko ju� nie jest otwarte
   for(unsigned int i=0;i<historyWindows.size();++i)
   {
	  if (historyWindows[i]->block==block) {
		 historyWindows[i]->refresh(input->input);
		 historyWindows[i]->Show();
		 if (OnDebug!=NULL) OnDebug(this, "Historia "+block->getTitle()+" - Pokazuje istniej�ce okno histori");
		 return;
	  }
   }

   //niema :P
   if (block->history.size()==0)
   {
	  if (OnWarrning!=NULL) OnWarrning(this, "Historia "+block->getTitle()+" - Blok nie posiada histori, prosze go wpierw uruchomi�");
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
   if (OnDebug!=NULL) OnDebug(this, "Historia "+block->getTitle()+" - Tworze i pokazuje nowe okno histori");
}

void PIWOEngine::OnVisualBlockOutputHistoryClick(VisualOutput* output, TObject* Sender)
{
   VisualBlock* block=(VisualBlock*)Sender;
   //sprawdzamy czy przypadkiem takie okienko ju� nie jest otwarte
   if (OnDebug!=NULL) OnDebug(this, "Historia "+block->getTitle()+" - Otrzymano rz�danie histori dla wyj�cia "+output->output->getName()+" ("+output->output->getDescription()+")");
   for(unsigned int i=0;i<historyWindows.size();++i)
   {
	  if (historyWindows[i]->block==block) {
		 historyWindows[i]->refresh(output->output);
		 historyWindows[i]->Show();
		 if (OnDebug!=NULL) OnDebug(this, "Historia "+block->getTitle()+" - Pokazuje istniej�ce okno histori");
		 return;
	  }
   }

   //niema :P
   if (block->history.size()==0)
   {
	  if (OnWarrning!=NULL) OnWarrning(this, "Historia "+block->getTitle()+" - Blok nie posiada histori, prosze go wpierw uruchomi�");
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
   if (OnDebug!=NULL) OnDebug(this, "Historia "+block->getTitle()+" - Tworze i pokazuje nowe okno histori");
}

void PIWOEngine::OnVisualBlockMove(TObject* Sender, bool moveAll, int x, int y)
{
  //przes�wanie blok�w, jesli moveAll jest ustawione to przesuwamy all zaznaczone bloki, a jesli nie to tylko ten do ktorego dostalismy wska�nik (tzn dostajamy conneciton)
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
  changed=true;if (OnChanged!=NULL) OnChanged(this);
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
   if (OnDebug!=NULL) OnDebug(this, "Odznaczono blok - "+block->getTitle());
   block->setSelected(false);
}

void PIWOEngine::OnVisualBlockSelect(TObject* Sender)
{
   while(selectedBlocks.size()>0)
   {
	  if (selectedBlocks[0]!=Sender) {
	   if (OnDebug!=NULL) OnDebug(this, "Odznaczono blok - "+selectedBlocks[0]->getTitle());
	   selectedBlocks[0]->setSelected(false);
	  }
	  selectedBlocks.erase(selectedBlocks.begin());
   }

   for(unsigned int i=0;i<connections.size();++i)
   {
	   if (connections[i]->inBlock==Sender||connections[i]->outBlock==Sender)
			 connections[i]->BringToFront();
   }

   if (OnDebug!=NULL) OnDebug(this, "Zaznaczono blok - "+((VisualBlock*)Sender)->getTitle());
   selectedBlocks.push_back((VisualBlock*)Sender);
   this->UnselectSelectedConnection();
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

   if (OnDebug!=NULL) OnDebug(this, "Zaznaczono blok - "+((VisualBlock*)Sender)->getTitle());
   selectedBlocks.push_back((VisualBlock*)Sender);
   this->UnselectSelectedConnection();
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
	  if (OnDebug!=NULL) OnDebug(this, "Odznaczono po��czenie - "+selectedConnection->outBlock->getTitle()+"("+selectedConnection->output->getDescription()+") -> "+selectedConnection->inBlock->getTitle()+"("+selectedConnection->input->getDescription()+")");
	  selectedConnection->setSelected(false);
   }
   selectedConnection=(Connection*)Sender;
   selectedConnection->BringToFront();
   if (OnDebug!=NULL) OnDebug(this, "Zaznaczono po��czenie - "+selectedConnection->outBlock->getTitle()+"("+selectedConnection->output->getDescription()+") -> "+selectedConnection->inBlock->getTitle()+"("+selectedConnection->input->getDescription()+")");
   this->UnselectAllBlocks();
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
	if (OnDebug!=NULL) OnDebug(this, "Usuwanie bloku "+fullName+" - Rozpoczeto");
	for(unsigned int i=0;i<blocks.size();++i)
	{
		if (blocks[i]->getTitle()==fullName) {
		   toDelete=blocks[i];
		   blocks.erase(blocks.begin()+i);
		   break;
		}
	}
	if (toDelete==NULL)
	{
	  if (OnError!=NULL) OnError(this, "Usuwanie bloku "+fullName+" - Nie istnieje blok o takiej nazwie");
	  return false;
	}
	if (OnDebug!=NULL) OnDebug(this, "Usuwanie bloku "+fullName+" - Znaleziono blok");
	abort(true);
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
	  //sprawdzamy wej�cia

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
	  //sprawdzamy wyj�cia
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

	  //usuwamy po��czenie
	  if (selectedConnection==connections[j]) selectedConnection=NULL;
	  delete connections[j];
	  connections.erase(connections.begin()+j);
	  --j;
   }

   delete toDelete;
	if (OnInformation!=NULL) OnInformation(this, "Usuni�to blok "+fullName+" wraz z po��czeniami");
   //sprawdzamy co wywalone..
   if (blocksToCheck.size()>0&&OnDebug!=NULL) OnDebug(this, "Usuwanie bloku "+fullName+" - Rozpoczynam wymagan� validacje blok�w");
   for(unsigned int i=0;i<blocksToCheck.size();++i)
   {
	   validateBlock(blocksToCheck[i]);
   }
   if (blocksToCheck.size()>0&&OnDebug!=NULL) OnDebug(this, "Usuwanie bloku "+fullName+" - Zako�czono wymagan� validacje blok�w");
   if (OnDebug!=NULL) OnDebug(this, "Usuwanie bloku "+fullName+" - Zako�czono");
   if (alwaysRun) run();
   changed=true;if (OnChanged!=NULL) OnChanged(this);
   return true;
}

bool PIWOEngine::DeleteSelectedBlocks()
{
   if (selectedBlocks.size()==0) return false;
   if (OnDebug!=NULL) OnDebug(this, "Usuwanie zaznaczonych blok�w - Rozpoczeto");
   abort(true);
   for(unsigned int i=0;i<selectedBlocks.size();++i)
   {
	   //zaznaczam po��czenia do usuni�cia
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
		  if (OnInformation!=NULL) OnInformation(this, "Usuni�to blok "+blocks[j]->getTitle()+" wraz z po��czeniami");
		  delete blocks[j];
		  blocks.erase(blocks.begin()+j);
		  --j;
	   }
   }
   selectedBlocks.clear();

   vector<VisualBlock*> blocksToCheck;
   for(unsigned int j=0;j<connections.size();++j)
   {
	  //sprawdzamy wej�cia
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
	  //sprawdzamy wyj�cia
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

	   if (connections[j]->outBlock==NULL && connections[j]->inBlock==NULL)
       	toDelete=true;

	  //usuwamy po��czenie
	  if (toDelete)
	  {
		if (selectedConnection==connections[j]) selectedConnection=NULL;
		delete connections[j];
		connections.erase(connections.begin()+j);
		--j;
	  }
   }

   //sprawdzamy co wywalone..
   if (blocksToCheck.size()>0&&OnDebug!=NULL) OnDebug(this, "Usuwanie zaznaczonych blok�w - Rozpoczeto wymagan� validacje blok�w");
   for(unsigned int i=0;i<blocksToCheck.size();++i)
   {
	   validateBlock(blocksToCheck[i]);
   }
   if (blocksToCheck.size()>0&&OnDebug!=NULL) OnDebug(this, "Usuwanie zaznaczonych blok�w - Zako�czono wymagan� validacje blok�w");
   if (alwaysRun) run();
   changed=true;if (OnChanged!=NULL) OnChanged(this);
   return true;
}

bool PIWOEngine::DeleteAllBlocks()
{
   if (blocks.size()==0) return false;
   abort(true);
   while(connections.size()>0)
   {
	   if (OnDebug!=NULL) OnDebug(this, "Usuwanie wszystkich blok�w - Usuwanie po��czenia: "+connections[0]->outBlock->getTitle()+"("+connections[0]->output->getDescription()+") -> "+connections[0]->inBlock->getTitle()+"("+connections[0]->input->getDescription()+")");
	   delete connections[0];
	   connections.erase(connections.begin());
   }
   while(blocks.size()>0)
   {
	   if (OnInformation!=NULL) OnInformation(this, "Usuwanie wszystkich blok�w - Usuni�to blok: "+blocks[0]->getTitle());
	   delete blocks[0];
	   blocks.erase(blocks.begin());
   }
   if (OnInformation!=NULL) OnInformation(this, "Usuni�to wszystkie bloki i po��czenia");
   if (OnDebug!=NULL) OnDebug(this, "Usuwanie wszystkich blok�w - Zako�czono");
   changed=true;if (OnChanged!=NULL) OnChanged(this);
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
	   if (OnDebug!=NULL) OnDebug(this, "Zaznaczanie wszystkich blok�w - Zaznaczono blok: "+blocks[i]->getTitle());
	}
  }
  if (OnDebug!=NULL) OnDebug(this, "Zaznaczanie wszystkich blok�w - Zako�czono");
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
	   if (OnDebug!=NULL) OnDebug(this, "Odwracanie zaznaczenia wszystkich blok�w - Zaznaczono blok: "+blocks[i]->getTitle());
	}
	else
	{
	   blocks[i]->setSelected(false);
	   if (OnDebug!=NULL) OnDebug(this, "Odwracanie zaznaczenia wszystkich blok�w - Odznaczono blok: "+blocks[i]->getTitle());
    }
  }
  selectedBlocks=newSelections;
  if (OnDebug!=NULL) OnDebug(this, "Odwracanie zaznaczenia wszystkich blok�w - Zako�czono");
}

void PIWOEngine::UnselectAllBlocks()
{
   if (selectedBlocks.size()==0) return;
   while(selectedBlocks.size()>0)
   {
	  selectedBlocks[0]->setSelected(false);
	  if (OnDebug!=NULL) OnDebug(this, "Odznaczanie wszystkich blok�w - Odznaczono block:"+selectedBlocks[0]->getTitle());
	  selectedBlocks.erase(selectedBlocks.begin());
   }
   if (OnDebug!=NULL) OnDebug(this, "Odznaczanie wszystkich blok�w - Zako�czono");
}

bool PIWOEngine::DeleteSelectedConnection()
{
   if (selectedConnection!=NULL)
   {
	  abort(true);
	  for(unsigned int i=0;i<connections.size();++i)
	  {
		if (connections[i]==selectedConnection)
		{
		   selectedConnection->input->disconnect();
		   VisualBlock* block=selectedConnection->inBlock;
		   if (OnInformation!=NULL) OnInformation(this, "Usuni�to po��czenie - "+selectedConnection->outBlock->getTitle()+"("+selectedConnection->output->getDescription()+") -> "+selectedConnection->inBlock->getTitle()+"("+selectedConnection->input->getDescription()+")");
		   delete connections[i];
		   connections.erase(connections.begin()+i);
		   if (OnDebug!=NULL) OnDebug(this, "Usuwanie zaznaczonego po��czenia - Rozpoczynam wymagan� validacje bloku");
		   validateBlock(block);
		   if (OnDebug!=NULL) OnDebug(this, "Usuwanie zaznaczonego po��czenia - Zako�czono wymagan� validacje bloku");
		   break;
		}
	  }
	  selectedConnection=NULL;
	  changed=true;if (OnChanged!=NULL) OnChanged(this);
	  if (alwaysRun) run();
	  return true;
   } else return false;
}

bool PIWOEngine::DeleteAllConnections()
{
   if (connections.size()==0) return false;
   abort(true);
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
	   if (OnDebug!=NULL) OnDebug(this, "Usuwanie wszystkich po��cze� - Usuni�to: "+connections[0]->outBlock->getTitle()+"("+connections[0]->output->getDescription()+") -> "+connections[0]->inBlock->getTitle()+"("+connections[0]->input->getDescription()+")");
	   delete connections[0];
	   connections.erase(connections.begin());
   }
   selectedConnection=NULL;
   if (list.size()>0&&OnDebug!=NULL) OnDebug(this, "Usuwanie wszystkich po��cze� - Rozpoczeto wymagan� validacje blok�w");
   for(unsigned int i=0;i<list.size();++i)
   {
	   validateBlock(list[i]);
   }
   if (list.size()>0&&OnDebug!=NULL) OnDebug(this, "Usuwanie wszystkich po��cze� - Zako�czono wymagan� validacje blok�w");
   if (OnInformation!=NULL) OnInformation(this, "Usuni�to wszystkie po��czenia");
   changed=true;if (OnChanged!=NULL) OnChanged(this);
   if (alwaysRun) run();
   return true;
}

void PIWOEngine::UnselectSelectedConnection()
{
   if (selectedConnection!=NULL)
   {
	  selectedConnection->setSelected(false);
	  if (OnDebug!=NULL) OnDebug(this, "Odznaczono po��czenie - "+selectedConnection->outBlock->getTitle()+"("+selectedConnection->output->getDescription()+") -> "+selectedConnection->inBlock->getTitle()+"("+selectedConnection->input->getDescription()+")");
	  selectedConnection=NULL;
   }
}

void PIWOEngine::CancelCustomizationOnSelectedConnections()
{
   if (selectedConnection!=NULL)
   {
	  selectedConnection->setCustomizeFalse();
	  changed=true;if (OnChanged!=NULL) OnChanged(this);
	  if (OnDebug!=NULL) OnDebug(this, "Anulowanie ustawie� u�ytkownika dla po��czenia - "+selectedConnection->outBlock->getTitle()+"("+selectedConnection->output->getDescription()+") -> "+selectedConnection->inBlock->getTitle()+"("+selectedConnection->input->getDescription()+")");
   }
}

void PIWOEngine::CancelCustomizationOnAllConnections()
{
	for(unsigned int i=0;i<connections.size();++i)
	{
	   connections[i]->setCustomizeFalse();
	   changed=true;if (OnChanged!=NULL) OnChanged(this);
	   if (OnDebug!=NULL) OnDebug(this, "Anulowanie ustawie� u�ytkownika dla po��czenia - "+connections[i]->outBlock->getTitle()+"("+connections[i]->output->getDescription()+") -> "+connections[i]->inBlock->getTitle()+"("+connections[i]->input->getDescription()+")");
    }
}

bool PIWOEngine::runUsingHistory()
{
  if (stopRunning==true) return false;
  stopRunning=true;
  while(isRunning)
  {
	  Application->ProcessMessages();
	  Sleep(1);
  }
  stopRunning=false;
  isRunning=true;
  if (OnRunStart!=NULL) OnRunStart(this);
  runProgress=0;
  bool status=true;
  if (OnRunInformation!=NULL)
	   OnRunInformation(this, "Rozpocz�to uruchamianie z u�yciem historii");
  if (OnInformation!=NULL)
	   OnInformation(this, "Rozpocz�to uruchamianie z u�yciem historii");


	//usuwamy status runned, przetwa�amy zaczynaj�c od najstarszego bloku, czy�cimy dane, w sumie mo�emy zostawi� dane kt�re widnia�y po ostatniej operacji
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
		   if (!stopRunning)
		   if (!runBlock(blocks[i], false, &useHistory)) status=false;
		}
	}
	if (OnRunProgress!=NULL) OnRunProgress(this, (stopRunning?"Anulowano":"Zako�czono"),100.0);
	if (stopRunning&&OnRunError) {
		  OnRunError(this, "Uruchamianie zosta�o przerwane");
	}
	if (!stopRunning&&status&&OnRunSuccess!=NULL) {
		  OnRunSuccess(this, "Zako�czono uruchamianie");
	}
	if (!stopRunning&&!status&&OnRunWarrning!=NULL) {
		  OnRunWarrning(this, "Zako�czono uruchamianie");
	}

	if (stopRunning&&OnError) {
		  OnError(this, "Uruchamianie zosta�o przerwane");
	}
	if (!stopRunning&&status&&OnSuccess!=NULL) {
		  OnSuccess(this, "Zako�czono uruchamianie");
	}
	if (!stopRunning&&!status&&OnWarrning!=NULL) {
		  OnWarrning(this, "Zako�czono uruchamianie");
	}
	if (OnRunEnd!=NULL) OnRunEnd(this);
	stopRunning=false;
	isRunning=false;
	return status;
}

bool PIWOEngine::runNotUsingHistory()
{
  if (stopRunning==true) return false;
  stopRunning=true;
  while(isRunning)
  {
	  Application->ProcessMessages();
	  Sleep(1);
  }
  stopRunning=false;
  isRunning=true;
  if (OnRunStart!=NULL) OnRunStart(this);
  runProgress=0;
  bool status=true;
  if (OnRunInformation!=NULL)
	   OnRunInformation(this, "Rozpocz�to uruchamianie z u�yciem historii");
  if (OnInformation!=NULL)
	   OnInformation(this, "Rozpocz�to uruchamianie z u�yciem historii");


	//usuwamy status runned, przetwa�amy zaczynaj�c od najstarszego bloku, czy�cimy dane, w sumie mo�emy zostawi� dane kt�re widnia�y po ostatniej operacji
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
		   if (!stopRunning)
		   if (!runBlock(blocks[i], false, &useHistory)) status=false;
		}
	}
	if (OnRunProgress!=NULL) OnRunProgress(this, (stopRunning?"Anulowano":"Zako�czono"),100.0);
	if (stopRunning&&OnRunError) {
		  OnRunError(this, "Uruchamianie zosta�o przerwane");
	}
	if (!stopRunning&&status&&OnRunSuccess!=NULL) {
		  OnRunSuccess(this, "Zako�czono uruchamianie");
	}
	if (!stopRunning&&!status&&OnRunWarrning!=NULL) {
		  OnRunWarrning(this, "Zako�czono uruchamianie");
	}

	if (stopRunning&&OnError) {
		  OnError(this, "Uruchamianie zosta�o przerwane");
	}
	if (!stopRunning&&status&&OnSuccess!=NULL) {
		  OnSuccess(this, "Zako�czono uruchamianie");
	}
	if (!stopRunning&&!status&&OnWarrning!=NULL) {
		  OnWarrning(this, "Zako�czono uruchamianie");
	}
	if (OnRunEnd!=NULL) OnRunEnd(this);
	stopRunning=false;
	isRunning=false;
	return status;
}

bool PIWOEngine::runBlock(VisualBlock* block, bool fastRun, bool *useHistory)
{
	if (stopRunning) return false;
	if (OnRunProgress!=NULL) OnRunProgress(this, block->getTitle(),(++runProgress/(blocks.size()+1)*100));
	/*
		Algorytm:
		* za�o�enie: aby bloczek by� przetworzony musi by� przynajmniej jedno wej�cie z kodem 0 gdy bloczek posiada wej�cia i przynajmniej jedno wyj�cie z kodem 0 gdy bloczek posiada wyj�cia.
		* za�o�enie: wej�cia do kt�rych pod��czony typ nie spe�nia wymaga� jest uznawane jako wej�cie z kodem 1 i nie pod��czonym blokiem. [zaktualizowa� w wyswietlaniu bloku i po��czenia, aby nie widzia� blok po��czenia]
		* za�o�enie: uruchamiamy wszystkie bloki jakie si� da.
		- uruchamiamy bloki od kt�rych jeste�my zale�ni (requencyjnie) - je�li nie zosta�y jeszcze uruchomione):
			- sprawdzamy czy blok by� ju� uruchomiony, je�li nie to uruchamiamy
			- pobieramy dane z wyj�� bloku, je�li dane s� r�wne NULL to znaczy �e blok nie zosta� uruchomiony - przerywamy
			- kopiujemy dane na wej�cie
		- sprawdzamy czy bloczke mo�e by� uruchomiony, ma conajmniej jedno poprawne wej�cie i jedno poprawne wyj�cie [o ile ma], jak nie to wywalamy warrning
		- je�li fastRun jest ustawione na true i useHistory=true i mamy dane w histori to je uzywamy, je�li niemamy danych w histori to upewniamy si� �e histora niemo�e zosta� u�yta.
		- uruchamiamy blok
		- sprawdzamy kod b��du
		- sprawdzamy dane wyj�ciowe bloczka
		- ustawiamy dane na wyj�ciach o ile s� poprawne, jak nie to nie ustawiamy
		- przeprowadzamy validacje bloczka
		- ustawiamy historie
		- zwracamy true
	*/

	//sprawdzamy dane wejsciowe.
	//@TODO, powini�ym sprawdza� po wej�cia left/top/right/bottom, ale to nie ejst narazie ziamplementowane, dgy b�dzie cz�c tej funkcji b�dzie wymaga�a przer�bki.
	for(unsigned int i=0;i<block->block.input.size();++i)
	{
		if (!block->block.input[i].getConnectedType().IsEmpty())
		{
		   //znajdujemy po��czenie odpowiedizalne za to wej�cie
		   
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
			  //jest po��czenie, sprawdzamy czy na danym bloku s� dane
			  con->update();
			  TypeConfig *data=con->output->getObject();
			  if (data!=NULL)
			  {
				  //mamy dane wi�c je kopiujemy.
				  //sprawdzamy czy dane s� odpowiedniego typu
				  if (data->getName()==block->block.input[i].getConnectedType()) {
					 block->block.input[i].setObject(*data);
				  }
				  else
				  {
					  if (OnRunError!=NULL) {
						 OnRunError(this, "Otrzymano b��dne dane na wej�ciu "+block->block.input[i].getDescription()+" bloku "+block->getTitle()+", oczekiwano: "+block->block.input[i].getConnectedType()+", otrzymano: "+data->getName());
					  }
					  block->block.input[i].setErrorCode(1);
					  block->setStatusColor(clYellow);
					  block->updateVisualComponents();
					  return false;
				  }
			  }
			  else
			  {
				  //niema danych :(
				  //sprawdzamy czy blok by� uruchamiany
				  
				  if (con->outBlock->runned) {
					  //by� uruchamiany, trudno, wywalamy warrning i przerywamy wykonywanie
					  if (OnRunError!=NULL) {
						 OnRunError(this, "Brak wymaganych danych na wej�ciu do bloku: "+block->getTitle());
					  }
					  block->block.input[i].setErrorCode(1);
					  block->setStatusColor(clYellow);
					  block->updateVisualComponents();
					  return false;
				  }
				  else
				  {
					  //uruchamiamy blok :D
					  if (stopRunning) return false;
					  if (!runBlock(con->outBlock, fastRun, useHistory))
					  {
						  if (stopRunning) return false;
						  con->update();
						  //blok nie zosta� uruchomiony, ale pech
						  if (OnRunError!=NULL) {
							OnRunError(this, "Blok nadrz�dny "+con->outBlock->getTitle()+" dla "+block->getTitle()+" nie zosta� uruchomiony - brak wymaganych danych wej�ciowych");
						  }
						  block->block.input[i].setErrorCode(1);
						  block->setStatusColor(clYellow);
						  block->updateVisualComponents();
						  return false;
					  }
					  else
					  {
						  if (stopRunning) return false;
						  con->update();
						  //a jednak si� uruchomi�, ale fux :d, sprawdzamy czy mamy te dane
                          TypeConfig *data=con->output->getObject();
						  if (data!=NULL)
						  {
							//mamy dane wi�c je kopiujemy.
							//sprawdzamy czy dane s� odpowiedniego typu
							if (data->getName()==block->block.input[i].getConnectedType()) {
								 block->block.input[i].setObject(*data);
							}
							else
							{
								  if (OnRunError!=NULL) {
									 OnRunError(this, "Otrzymano b��dne dane na wej�ciu "+block->block.input[i].getDescription()+" bloku "+block->getTitle()+", oczekiwano: "+block->block.input[i].getConnectedType()+", otrzymano: "+data->getName());
								  }
								  block->block.input[i].setErrorCode(1);
								  block->setStatusColor(clYellow);
								  return false;
							}
						  }
						  else
						  {
							  //by� uruchamiany, trudno, wywalamy warrning i przerywamy wykonywanie
							 if (OnRunError!=NULL) {
								OnRunError(this, "Brak wymaganych danych na wej�ciu do bloku: "+block->getTitle());
							 }
							 block->block.input[i].setErrorCode(1);
							 block->setStatusColor(clYellow);
							 block->updateVisualComponents();
							 return false;
						  }
					  }
				  }
              }
		   }
		   else
		   {
			  //niema po��czenia ? jakim cudem
			  if (OnRunError!=NULL) {
				 OnRunError(this, "Brak wymaganych danych na wej�ciu do bloku (nie znale�iono po��czenia): "+block->getTitle());
			  }
			  block->block.input[i].setErrorCode(2);
			  block->setStatusColor(clYellow);
			  block->updateVisualComponents();
			  return false;
           }
		}
	}
	
	//Mamy ju� dane wej�ciowe (fuxem)
	//nieb�de tu sprawdza� danych wyj�ciowych :d
	//teraz sprawdzimy historie i uruchomimy bloczek D:
	BlockHistory *history=NULL;
	if (*useHistory)
	{
	   //u�ywamy histori, sprawdzamy czy jest taka
	   //je�li wska�niki wej�ciowe si� zgadzaj�, zgadza si� ich revision, zgadza si� revision bloku konfiguracyjnego to niemusze odpala� bloku.
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
				if (block->history[i]->rightOutput[j]->getData()!=NULL)
				{
				   if ((block->history[i]->rightOutput[j]->getData()->getName()!=block->rightOutput[j]->output->getOutputType()))
				   {
					  ok=false;
				   }
				}
				else
				if (!block->rightOutput[j]->output->getOutputType().IsEmpty())
				{
					ok=false;
				}
			  } else ok=false;
		   }

		   for(unsigned int j=0;ok&&j<block->history[i]->bottomOutput.size();++j)
		   {
			  if (block->history[i]->bottomOutput[j]->output==block->bottomOutput[j]->output)
			  {
				if (block->history[i]->bottomOutput[j]->getData()!=NULL)
				{
				   if ((block->history[i]->bottomOutput[j]->getData()->getName()!=block->bottomOutput[j]->output->getOutputType()))
				   {
					  ok=false;
				   }
				}
				else
				if (!block->bottomOutput[j]->output->getOutputType().IsEmpty())
				{
					ok=false;
				}
			  } else ok=false;
		   }

		   if (ok)
		   {
			   history=block->history[i];
			   block->history.erase(block->history.begin()+i); //dodamy potem hitorie na samym pocz�tku
			   if (OnRunDebug!=NULL) OnRunDebug(this, "Znale�iono pasuj�c� historie - ID:"+IntToStr(i));
			   break;
		   }
       }
	   
	}
	else
	{
		//czy�cimy historie gdy niewolno nam jej u�ywa�.
		while (block->history.size()>10)
		{
		  delete block->history[10];
		  block->history.erase(block->history.begin()+10);
		}
	}
	
	//@TODO rozwa�y� u�ycie histori dla blok�w nie posiadaj�cych wyj�cia, czyli np dla bloczk�w z�u��cych do zapisu obrazu do pliku [mo�liwe �e te bloki zostan� w przysz�o�ci usuni�te]
	if (history!=NULL) {
		//mamy historie, inicjujemy wyj�cia i zwracamy true, i wrzucamy historie z powrotem na stos :d
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
		//u�yli�my histori, powiadamiamy o tym
		if (OnRunSuccess!=NULL) {
			 OnRunSuccess(this, "Blok "+block->getTitle()+" zosta� przetworzony w oparciu o dane historyczne");
		}
		block->setStatusColor(clGreen);
		return true;
	}
	//niemamy histori wi�c jeszcze b�dziemy musieli si� sporo pobawi�.
	//zak�adamy �e wejscia mamy ju� wype�nione wykonujemy nast�puj�ce ruchy:
	FunctionDLL *fn=plugins->getFunction(block->nameOfBlock);
	if (OnRunInformation!=NULL) {
			 OnRunInformation(this, "Uruchamiam blok "+block->getTitle());
	}
	int ret=2;
	try{
	ret=fn->run(&(block->block));
	}
	catch (Exception &exception)
	{
		if (OnError!=NULL) OnError(this,"Uruchomienie bloku - "+block->getTitle()+" - B��d wewn�trzny: "+StringReplace(exception.Message, "\n", " ", TReplaceFlags() << rfReplaceAll));
		if (OnRunError!=NULL) OnRunError(this,"Uruchomienie bloku - "+block->getTitle()+" - B��d wewn�trzny: "+StringReplace(exception.Message, "\n", " ", TReplaceFlags() << rfReplaceAll));
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			if (OnError!=NULL) OnError(this,"Uruchomienie bloku - "+block->getTitle()+" - B��d wewn�trzny: "+StringReplace(exception.Message, "\n", " ", TReplaceFlags() << rfReplaceAll));
			if (OnRunError!=NULL) OnRunError(this,"Uruchomienie bloku - "+block->getTitle()+" - B��d wewn�trzny: "+StringReplace(exception.Message, "\n", " ", TReplaceFlags() << rfReplaceAll));
		}
	}

	block->runned=true;
	if (OnRunDebug!=NULL) OnRunDebug(this, "Aktualizuje wygl�d dla bloku "+block->getTitle());
	block->updateVisualComponents();
	if (ret!=0&&ret!=1) {
		//wystapi� b��d, usuwamy dane
		for(unsigned int i=0;i<block->block.output.size();++i)
		{
		   block->block.output[i].clearObject();
		}
		if (OnRunError!=NULL)
				OnRunError(this, "Blok "+block->getTitle()+" nie zosta� przetwo�ony");
		block->setStatusColor(clRed);
		return false;
	} else
	if (ret==1) {
		if (OnRunWarrning!=NULL)
				OnRunWarrning(this, "Blok "+block->getTitle()+" zosta� przetwo�ony ale zwr�c� warrning");
		block->setStatusColor(clYellow);
	}
	else
	{
	   if (OnRunSuccess!=NULL)
				OnRunSuccess(this, "Blok "+block->getTitle()+" zosta� przetwo�ony");
	   block->setStatusColor(clGreen);
	}


	//kod b��du 1 lub 0, spradzi� wyj��ia, skopiowa� do histori, etc
	history=new BlockHistory();
	history->configRevision=block->block.getConfig()->getRevision();
	//kopiujemy wej�cia do histori:
	bool historyWillBeAdded=false;
	for(unsigned int i=0;i<block->leftInput.size();++i)
	{
		BlockHistoryInputElement *hi=new BlockHistoryInputElement();
		hi->input=block->leftInput[i]->input;
		TypeConfig *tp=block->leftInput[i]->input->getObject();
		if (tp!=NULL)
		{
		   hi->setData(*tp);
		   historyWillBeAdded=true;
		}
		else
		{
		   hi->setNULL();
		   block->leftInput[i]->input->setErrorCode(1);
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
		   historyWillBeAdded=true;
		}
		else
		{
		   hi->setNULL();
		   block->topInput[i]->input->setErrorCode(1);
		}
		history->topInput.push_back(hi);
	}

	//sprawdzi� poprawno�� danych na wyj�ciu:
	TypeDLL *tdll=NULL;
	for(unsigned int i=0;i<block->block.output.size();++i)
	{
		TypeConfig *tc=block->block.output[i].getObject();
		if (tc==NULL && !block->block.output[i].getOutputType().IsEmpty())
		{
			//niema danych, a powinny jakie� by�. - tylko warrning
			if (OnRunWarrning!=NULL)
				OnRunWarrning(this, "Brak danych na wyj�ciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+", oczekiwano "+block->block.output[i].getOutputType());
		  block->setStatusColor(clYellow);
		} else
		if(tc!=NULL&&block->block.output[i].getOutputType().IsEmpty())
		{
		  //niechiceli�my danych, a dostali�my.
		  if (OnRunWarrning!=NULL)
				OnRunWarrning(this, "Otrzymano nieoczekiwane dane na wyj�ciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+" typu "+tc->getName()+", dane zosta�y pomini�te");
		  block->block.output[i].clearObject();
		  tc=NULL;
		} else
		if (tc!=NULL)
		{
		   //mamy dane, sprawdzamy czy s� tego typu jakiego oczekiwali�my.
		   if (tc->getName()!=block->block.output[i].getOutputType())
		   {
			  //otrzyma�em b��dne dane, warrning
			  if (OnRunWarrning!=NULL)
				OnRunWarrning(this, "Otrzymano b��dne dane na wyj�ciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+", otrzymano: "+tc->getName()+", oczekiwano: "+block->block.output[i].getOutputType()+", dane zosta�y pomini�te");
			  block->block.output[i].clearObject();
			  block->setStatusColor(clYellow);
			  tc=NULL;
		   }
		   else
		   {
			   //validacja typu :d, a n� kto� si� bawi� :P
			   if (tdll==NULL||(tdll!=NULL&&tdll->getType()!=tc->getName()))
			   {
				  tdll=plugins->getType(tc->getName());
			   }

			   if (tdll==NULL)
			   {
				  //niema DLL typu, pomijamy sprawdzenie, wywalamy warrning
				  if (OnRunWarrning!=NULL)
					OnRunWarrning(this, "Otrzymano niewspierany typ danych na wyj�ciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+", typu: "+tc->getName());
			   }
			   else
			   {
				  if (!tdll->isValid(tc))
				  {
					 //dane nie s� poprawne, wywalamy
					if (OnRunWarrning!=NULL)
						OnRunWarrning(this, "Otrzymano b��dne dane na wyj�ciu "+block->block.output[i].getDescription()+" bloku "+block->getTitle()+", typu: "+tc->getName()+", dane s� niepoprawne i zosta�y pomini�te");
					block->block.output[i].clearObject();
					block->setStatusColor(clYellow);
					tc=NULL;
				  }
			   }
		   }
		}
	}

	//update histori wyj�cia.
	for(unsigned int i=0;i<block->rightOutput.size();++i)
	{
		BlockHistoryOutputElement *hi=new BlockHistoryOutputElement();
		hi->output=block->rightOutput[i]->output;
		TypeConfig *tp=block->rightOutput[i]->output->getObject();
		if (tp!=NULL)
		{
		   hi->setData(*tp);
		   historyWillBeAdded=true;
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
		   historyWillBeAdded=true;
		}
		else
		{
		   hi->setNULL();
		}
		history->bottomOutput.push_back(hi);
	}

	//dodajemy historie :D
	if (historyWillBeAdded)
	{
		block->history.insert(block->history.begin(),history);
	}
	else
	{
        if (OnRunDebug!=NULL)
				OnRunDebug(this, "Blok nie zwr�ci� �adnych danych, niedodano do histori");
		delete history;
	}
	return true;
}

bool PIWOEngine::run(bool useHistory)
{
	return (useHistory)?runUsingHistory():runNotUsingHistory();
}

bool PIWOEngine::isRuned()
{
   return isRunning;
}

void PIWOEngine::abort(bool wait)
{
   if (isRunning&&!stopRunning)
   {
	  stopRunning=true;
	  if (OnRunInformation!=NULL)
			OnRunInformation(this, "Przerwano uruchamianie");
	  if (wait)
	  {
			 while(isRunning)
			 {
				Application->ProcessMessages();
				Sleep(1);
			 }
	  }
   }
}

bool PIWOEngine::isAborted()
{
   return stopRunning;
}

void PIWOEngine::DuplcateSelectedBlocks()
{
	if (selectedBlocks.size()==0) return;
	abort(true);
	vector<VisualBlock*> newBlocks;

	for(unsigned int i=0;i<selectedBlocks.size();++i)
	{
		//tworzymy nowe bloki
		FunctionDLL *fun=plugins->getFunction(selectedBlocks[i]->nameOfBlock);
		if (fun==NULL) {
				if (OnDebug!=NULL) OnDebug(this,"Duplikowanie blok�w: Nieznaleziono pluginu o nazwie: "+selectedBlocks[i]->nameOfBlock);
				return;
		}
		int number=0;
		bool busy;
		do{
			++number;
			busy=false;
			for(unsigned int j=0;j<blocks.size();++j)
			{
				if (blocks[j]->nameOfBlock==selectedBlocks[i]->nameOfBlock && blocks[j]->numberOfBlock==number) {
					break;
				}
			}
		} while (busy);

		VisualBlock *newBlock=new VisualBlock(this->area);
		newBlock->Parent=this->area;
		newBlock->nameOfBlock=selectedBlocks[i]->nameOfBlock;
		newBlock->numberOfBlock=number;
		newBlock->setTitle(selectedBlocks[i]->nameOfBlock+" #"+IntToStr(number));
		newBlock->setConfigButtonGlyph(fun->picture);
		newBlock->Hint=fun->fullName;
		 if (fun->description!="") newBlock->Hint+="\n"+fun->description;
		newBlock->Left=selectedBlocks[i]->Left+100;
		newBlock->Top=selectedBlocks[i]->Top+100;
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
		//modyfikujemy konfiguracje i wej�cia / wyj�cia
		//TODO: w przydadku kopiowanie wyj�c i wej�c top/bootom wymaga aktualizacji
		newBlock->block.setConfig(*(selectedBlocks[i]->block.getConfig()));
		newBlock->block.input=selectedBlocks[i]->block.input;
		newBlock->block.output=selectedBlocks[i]->block.output;
		newBlock->updateVisualComponents();//niech narysuje conieco
		newBlocks.push_back(newBlock);
		blocks.push_back(newBlock);
		if (OnInformation!=NULL) OnInformation(this,"Zduplikowano blok - "+selectedBlocks[i]->nameOfBlock);
	}
	//odnawiamy po��czenia: right i left
	
	for(unsigned int i=0;i<connections.size();++i)
	{
		//szukamy po��cze� kt�rych pocz�tek i konie� jest w selected list
		int beginId=-1;
		int endId=-1;
		for(unsigned int j=0;j<selectedBlocks.size()&&(beginId==-1||endId==-1);++j)
		{
            selectedBlocks[j]->setSelected(false);
			if (selectedBlocks[j]==connections[i]->inBlock) {
			   beginId=j;
			   continue;
			}
			if (selectedBlocks[j]==connections[i]->outBlock) {
			   endId=j;
			   continue;
			}
		}
		if (beginId==-1||endId==-1) continue;

		int inputId=-1;
		int outputId=-1;
		for(unsigned int j=0;j<selectedBlocks[beginId]->block.input.size();++j)
		{
			if (&selectedBlocks[beginId]->block.input[j]==connections[i]->input) {
			   inputId=j;
			   break;
			}
		}
		for(unsigned int j=0;j<selectedBlocks[endId]->block.output.size();++j)
		{
			if (&selectedBlocks[endId]->block.output[j]==connections[i]->output) {
			   outputId=j;
			   break;
			}
		}
		if (inputId==-1||outputId==-1) continue;

		//tworzymy to po��czenie
		Connection* con=new Connection(this->area);
		con->input=&(newBlocks[beginId]->block.input[inputId]);
		con->inBlock=newBlocks[beginId];
		con->output=&(newBlocks[endId]->block.output[outputId]);
		con->outBlock=newBlocks[endId];
		con->OnConnectionSelected=OnConnectionSelect;
		con->input->connect(con->output->getOutputType());
		con->draw();
		//aktualizacja bloku input
		//kopiuje
		for(unsigned j=0;j<connections[i]->lines.size();++j)
		{
		  con->lines[j]->Resize=connections[i]->lines[j]->Resize;
		}
		connections.push_back(con);
		con->update();
	}

	for(unsigned int j=0;j<newBlocks.size();++j)
	{
	   validateBlock(newBlocks[j]);
	   newBlocks[j]->setSelected(true);
	}
	selectedBlocks=newBlocks;
	changed=true;if (OnChanged!=NULL) OnChanged(this);
	if (alwaysRun) run();
}

bool PIWOEngine::saveToFile(const AnsiString &filename)
{
	abort(true);
	//zapisujemy pozycje blok�w, konfiguracje blok�w, po��czenia, potem wykonujemy validacje ka�dego bloku i ka�dego po��czenia
	TFileStream *file=new TFileStream(filename, fmCreate);
	if (file==NULL)
		{
			if (OnError!=NULL) OnError(this, "Niemo�na zapisac projektu do : "+filename);
			return false;
		}
	this->Enabled=false;
	file->Write("PIWO 1.0",8);
	putInt(blocks.size(), *file);
	putInt(connections.size(), *file);
	for(unsigned int j=0;j<blocks.size();++j)
	{
	   putString(blocks[j]->nameOfBlock, *file);
	   putInt(blocks[j]->numberOfBlock, *file);
	   blocks[j]->block.getConfig()->saveToStream(*file);
	   putInt(blocks[j]->Left, *file);
	   putInt(blocks[j]->Top, *file);
	   putInt(blocks[j]->block.input.size(), *file);
	   for(unsigned int k=0;k<blocks[j]->block.input.size();++k)
	   {
		   putString(blocks[j]->block.input[k].getName(), *file);
		   putString(blocks[j]->block.input[k].getDescription(), *file);
		   putString(blocks[j]->block.input[k].getErrorDescription(), *file);
		   putInt(blocks[j]->block.input[k].getErrorCode(), *file);
		   putInt(blocks[j]->block.input[k].allowedTypes.size(), *file);
		   for(unsigned int o=0;o<blocks[j]->block.input[k].allowedTypes.size();++o)
			   putString(blocks[j]->block.input[k].allowedTypes[o], *file);
	   }
	   putInt(blocks[j]->block.output.size(), *file);
	   for(unsigned int k=0;k<blocks[j]->block.output.size();++k)
	   {
		   putString(blocks[j]->block.output[k].getName(), *file);
		   putString(blocks[j]->block.output[k].getDescription(), *file);
		   putString(blocks[j]->block.output[k].getErrorDescription(), *file);
		   putInt(blocks[j]->block.output[k].getErrorCode(), *file);
		   putString(blocks[j]->block.output[k].getOutputType(), *file);
	   }
	   if (OnDebug!=NULL) OnDebug(this, "Zapisuje blok "+blocks[j]->getTitle()+" do pliku");
	}
	//zapisujemy po��czenia
	for(unsigned int j=0;j<connections.size();++j)
	{
		int inBlock=-1;
		int outBlock=-1;
		int input=-1;
		int output=-1;
		//bloki
		for(unsigned int k=0;((k<blocks.size())&&(inBlock==-1||outBlock==-1));++k)
		{
			if (connections[j]->inBlock==blocks[k]) inBlock=k;
			if (connections[j]->outBlock==blocks[k]) outBlock=k;
		}
		//teraz wej�cia, wyj�cia
		if (inBlock!=-1&&outBlock!=-1)
		for(unsigned int k=0;k<blocks[outBlock]->block.output.size();++k)
		{
		   if (&blocks[outBlock]->block.output[k]==connections[j]->output)
		   {
			   output=k;
			   break;
		   }
		}
		if (inBlock!=-1&&outBlock!=-1)
		for(unsigned int k=0;k<blocks[inBlock]->block.input.size();++k)
		{
		   if (&blocks[inBlock]->block.input[k]==connections[j]->input)
		   {
			   input=k;
			   break;
		   }
		}
		putInt(inBlock, *file);
		putInt(outBlock, *file);
		putInt(input, *file);
		putInt(output, *file);
		putInt(connections[j]->lines.size(),*file);
		for(unsigned int k=0;k<connections[j]->lines.size();++k)
		{
		   putInt(connections[j]->lines[k]->Resize, *file);
		}
	}
	delete file;
	changed=false;
	if (OnSuccess!=NULL) OnSuccess(this, "Zapisano projekt do : "+filename);
	this->Enabled=true;
	return true;
}

bool PIWOEngine::loadFromFile(const AnsiString &filename)
{
	//wszystko �miga tylko trzeba doda� logi
	if (blocks.size()>0) return false;
	abort(true);
	TFileStream *file=new TFileStream(filename, fmOpenRead);
	if (file==NULL)
		{
        	if (OnError!=NULL) OnError(this, "Niemo�na wczyta� projektu z : "+filename);
			return false;
		}
	char *id=new char[9];
	file->Read(id, 8);
	id[8]='\0';
	AnsiString c=id;
	delete id;
	if (c!="PIWO 1.0") {
		delete file;
		return false;
	}

	int blocksCount=getInt(*file);
	int connectionsCount=getInt(*file);
	vector<VisualBlock*> newBlocks;
	for(int i=0;i<blocksCount;++i)
	{
		AnsiString name=getString(*file);
		FunctionDLL *fun=plugins->getFunction(name);
		if (fun==NULL)
		{
			if (OnError!=NULL) OnError(this,"Wczytywanie projektu - Nieznaleziono pluginu o nazwie: "+name);
			getInt(*file);
			BlockConfig conf;
			conf.loadFromStream(*file);
			getInt(*file);
			getInt(*file);
			int z=getInt(*file);
			for(int k=0;k<z;++k)
			{
			  getString(*file);
			  getString(*file);
			  getString(*file);
			  getInt(*file);
			  int g=getInt(*file);
			  for(int l=0;l<g;++l)
				 getString(*file);
			}
			z=getInt(*file);
			for(int k=0;k<z;++k)
			{
			  getString(*file);
			  getString(*file);
			  getString(*file);
			  getInt(*file);
			  getString(*file);
			}
            newBlocks.push_back(NULL);
			continue;
		}

		VisualBlock *newBlock=new VisualBlock(this->area);
		newBlock->Parent=this->area;
		newBlock->nameOfBlock=name;
		newBlock->numberOfBlock=getInt(*file);
		if (!newBlock->block.getConfig()->loadFromStream(*file))
				if (OnWarrning!=NULL) OnWarrning(this,"Wczytywanie projektu - Niewczytano konfiguracji bloku "+name+" #"+IntToStr(newBlock->numberOfBlock));
		newBlock->setTitle(name+" #"+IntToStr(newBlock->numberOfBlock));
		newBlock->setConfigButtonGlyph(fun->picture);
		newBlock->Hint=fun->fullName;
		if (fun->description!="") newBlock->Hint+="\n"+fun->description;
		newBlock->Left=getInt(*file);
		newBlock->Top=getInt(*file);
		int z=getInt(*file);
		for(int k=0;k<z;++k)
		{
			BlockInput input(getString(*file));
			input.setDescription(getString(*file));
			input.setErrorDescription(getString(*file));
			input.setErrorCode(getInt(*file));
			int u=getInt(*file);
			for(int f=0;f<u;++f)
				input.allowedTypes.push_back(getString(*file));
			newBlock->block.input.push_back(input);
		}
		z=getInt(*file);
		for(int k=0;k<z;++k)
		{
			BlockOutput output(getString(*file));
			output.setDescription(getString(*file));
			output.setErrorDescription(getString(*file));
			output.setErrorCode(getInt(*file));
			output.setOutputType(getString(*file));
			newBlock->block.output.push_back(output);
		}
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
		newBlock->updateVisualComponents();
		newBlocks.push_back(newBlock);
		blocks.push_back(newBlock);
		if (OnDebug!=NULL) OnDebug(this, "Wczytano blok "+newBlock->getTitle()+" z pliku");
	}

	for(int i=0;i<connectionsCount;++i)
	{
		int inBlock=getInt(*file);
		int outBlock=getInt(*file);
		int input=getInt(*file);
		int output=getInt(*file);
		int z=getInt(*file);
		if (inBlock==-1||outBlock==-1||input==-1||output==-1||newBlocks[inBlock]==NULL||newBlocks[outBlock]==NULL)
		{
		   for(int d=0;d<z;++d) getInt(*file);
		   continue;
		}

		//robimy po��czenie
		Connection* con=new Connection(this->area);
		con->input=&(newBlocks[inBlock]->block.input[input]);
		con->inBlock=newBlocks[inBlock];
		con->output=&(newBlocks[outBlock]->block.output[output]);
		con->outBlock=newBlocks[outBlock];
		con->OnConnectionSelected=OnConnectionSelect;
		con->input->connect(con->output->getOutputType());
		con->draw();
		if ((unsigned int)z==con->lines.size()) {
			for(int j=0;j<z;++j)
			{
				con->lines[j]->Resize=getInt(*file);
			}
		}
		else
		for(int d=0;d<z;++d) getInt(*file);

		connections.push_back(con);
		con->update();
	}

	for(unsigned int i=0;i<newBlocks.size();++i)
	{
		if (newBlocks[i]!=NULL) validateBlock(newBlocks[i]);
	}
	delete file;
	if (OnSuccess!=NULL) OnSuccess(this, "Wczytano projekt z : "+filename);
	return true;
}

bool PIWOEngine::isChanged()
{
	return changed;
}

int PIWOEngine::getBlockCount()
{
   return blocks.size();
}

void PIWOEngine::validateAll()
{
   if (blocks.size()==0) return;
   abort(true);
   for(unsigned int i=0;i<blocks.size();++i)
   {
	   validateBlock(blocks[i]);
   }
   if (OnInformation!=NULL) OnInformation(this, "Przeprowadzono sprawdzenie wszystkich blok�w");
   if (alwaysRun) run();
}

void putString(const AnsiString &str, TStream &stream)
{
	unsigned int i=str.Length();
	stream.Write(&i,sizeof(i));
	if (i==0) return;
	stream.Write(str.c_str(),i);
}

void putInt(const int i, TStream &stream)
{
   stream.Write(&i,sizeof(i));
}

AnsiString getString(TStream &stream)
{
   unsigned int i=0;
   stream.Read(&i,sizeof(i));
   if (i==0) return "";
   char *s=new char[i+1];
   stream.Read(s,i);
   s[i]='\0';
   AnsiString c=s;
   delete s;
   return c;
}

int getInt(TStream &stream)
{
   int i=0;
   stream.Read(&i,sizeof(i));
   return i;
}
