/*


*/
#include "classEASIROCDisplay.h"

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h> /* system, NULL, EXIT_FAILURE */

#include "TROOT.h"
#include "TSystem.h"
#include "TGTab.h"
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"

ClassImp(EASIROCDisplay)

void EASIROCDisplay::PrepareHist()
{
	for (int i=0; i<m_nChs; i++) {
		std::stringstream name;
		name << "h_" << i << std::ends;
		//m_h1[i] = new TH1F(name.str().data(),name.str().data(),2050,0,4100);
		m_h1[i] = new TH1F(name.str().data(),name.str().data(),600,700,1900);
		m_h1[i] ->SetLineWidth(1);
      m_h1[i] ->SetLineColor(1);
	}
}

// ----- transplant from EASIROC_UT2/tree.cc 
void EASIROCDisplay::LoadData()
{
   if ( m_stop ) { // initialize
		m_stop=false;
	 	for (int i=0; i<m_nChs; i++)  m_h1[i] ->Reset();
	}
	printf("\n[just, transplant covert program from EASIROC_UT2/tree.cc]\n");	
	const char *rmv, *cmd, *lst;
	//rmv = "rm ./linker";
	//cmd = "str=`ls -lt ./data/* | head -1`; ary=(${str}); cnt=${#ary[@]}; echo ${ary[${cnt}-1]}; ln -s ${ary[${cnt}-1]} ./linker";
	cmd = "str=`ls -lt ./data/* | head -1`; ary=(${str}); cnt=${#ary[@]}; ln -s ${ary[${cnt}-1]} ./linker";
	system(cmd);
	lst = "ls -l ./linker";
	system(lst);
	sleep(1);

	// ----- load a data file as a linker
	m_datFile.open("./linker", std::ios::in | std::ios::binary);
	//std::fstream m_datFile("./linker", std::ios::in | std::ios::binary);
	//m_datFile = fopen(fileName,"rb");
	if( !m_datFile ) {
        std::cout << "Error: cannot open file" << std::endl;
        exit(1);
   }
	unsigned int scalerValArr[10][69];
	unsigned int events = 0;

#if 0
  // Read Event Header
  if(fread(&head, sizeof(Header), 1, _fData) != 1) {
    fclose(_fData);
    return -1; /*return 0; End of program*/
  }

  head.eventSize = ntohl(head.eventSize); // size of current event
  head.eventNumb = ntohl(head.eventNumb); // current event number

  int eventSize = head.eventSize;
  int eventNumb = head.eventNumb;

  //   int evN = head.eventNumb;
  if (DEBUG) cout <<  "Event number: " << eventNumb << endl;

  int rawDataSize = eventSize - sizeof(head) - sizeof(pEnd);
  int nByteTot    = rawDataSize ;
  int nByteRead   = 0;
  sampleCountMax  = 0;

  //cout << "New Event : size = 0x" << hex << eventSize << ", "
  //     << eventNumb << dec << endl;

  while (nByteRead < nByteTot ) // nByteTot represents the size of the full event, not only the current packet
  {

  buffer=fread(runUid, 1, 20, _fData);

#endif

	size_t sumDataSize=0;

	//while (m_datFile) {	
	while (events<9999999) {
		if ( m_stop ) break;
      char headerByte[4]={};
      m_datFile.read(headerByte, 4); 
      unsigned int header = getBigEndian32(headerByte);
      bool isHeader = ((header >> 27) & 0x01) == 0x01;
		//std::cerr << "header=" << header << " isHeader=" << isHeader << std::endl;
#if 0
		if (!isHeader) {
            std::cerr << "Frame Error" << std::endl;
            fprintf(stderr, "    %08X\n", header);
            std::exit(1);
		}
#endif
		size_t dataSize = header & 0x0fff;
  		size_t testSize = m_datFile.tellg();
		sumDataSize += dataSize;
		//std::cerr << "dataSize=" << dataSize << " sum=" << sumDataSize << " testSize=" << testSize << std::endl;
		/*
		header=268431492 isHeader=1
		dataSize=132 sum=1514352
		header=268431490 isHeader=1
		dataSize=130 sum=1514482
		*/
		unsigned int scalerValues[69];
		char* dataBytes = new char[dataSize * 4];
		m_datFile.read(dataBytes, dataSize * 4);

		for (size_t i = 0; i < dataSize; ++i) {
			unsigned int data = getBigEndian32(dataBytes + 4 * i);
			if (isAdcHg(data)) {
         	int ch = (data >> 13) & 0x3f;
         	bool otr = ((data >> 12) & 0x01) != 0;
         	int value = data & 0x0fff;
         	if (!otr) {
            	//adc[ch]=value;
					m_h1[ch] ->Fill(value);
            }
         } else if (isAdcLg(data)) {
         	int ch = (data >> 13) & 0x3f;
         	bool otr = ((data >> 12) & 0x01) != 0;
         	int value = data & 0x0fff;
         	if(!otr) {
             	//low_adc[ch]=value;
         	}
			} else if (isTdcLeading(data)) {
            int ch = (data >> 13) & 0x3f;
            int value = data & 0x0fff;
            //tL[ch]=value;
         } else if (isTdcTrailing(data)) {
            int ch = (data >> 13) & 0x3f;
            int value = data & 0x0fff;
            //tT[ch]=value;
         } else if (isScaler(data)) {
            int ch = (data >> 14) & 0x7f;
            int value = data & 0x3fff;
            scalerValues[ch] = value;
            if(ch==68) {
            	int scalerValArrIndex = events % 100;
            	memcpy(scalerValArr[scalerValArrIndex], scalerValues, sizeof(scalerValues));
            }
			}else {
         	int ch = (data >> 13) & 0x3f;
         	int value = data & 0x0fff;
      		std::cout << "adchg:"  << (data & 0x00680000);
      		std::cout << "adclg:"  << (data & 0x00680000);
      		std::cout << "tdcl:"   << (data & 0x00601000);
      		std::cout << "tdct:"   << (data & 0x00601000);
      		std::cout << "scaler:" << (data & 0x00600000);
      		std::cout << "data:" << data << std::endl;
      		std::cout << "ch:" << ch << " value:" << value << std::endl;
      		std::cerr << "Unknown data type" << std::endl;
			}
		}//
		//tree->Fill();
		delete[] dataBytes;

		if (testSize>10E+15) {
			std::cerr << "the data reaches to the end" << std::endl;
			sleep(1);
			continue;
		}

		events++;

   	if(events%m_evnt==0) {
			std::cout << "reading events#:" << events << std::endl;
			for (int h=0; h<4; h++) {
				m_can[h]->cd();
				for (int i=0; i<16; i++) {
					m_can[h]->cd(1+i);
					m_h1[i + 16*h]->Draw();
				}
				m_can[h]->Update();
			}
			gSystem->ProcessEvents() ;
		}

#if 1
	if(events % 10 == 0) {
   	unsigned int scalerValuesSum[69];
      	for(int i = 0; i < 69; ++i) {
         	scalerValuesSum[i] = 0;
      	}
      	for(int i = 0; i < 10; ++i) {
      		for(int j = 0; j < 69; ++j) {
            	scalerValuesSum[j] += scalerValArr[i][j];
            }
      	}

      int counterCount1MHz = scalerValuesSum[67];
      int counterCount1KHz = scalerValuesSum[68];

      // 1count = 1.0ms
      double counterCount = (double)counterCount1KHz + counterCount1MHz / 1000.0;
      //cout << "counterCount" << counterCount << endl;
      // TODO
      // Firmwareのバグを直したら消す
      counterCount /= 2.0;

      //cout << "counterCount: " << counterCount << endl;
      for(size_t j = 0; j < 67; ++j) {
      	//cout << j << " scalerValuesSun: " << scalerValuesSum[j] << ", ";
      	bool ovf = ((scalerValuesSum[j] >> 13) & 0x01) != 0;
         ovf = true;
         //double scalerCount = scalerValuesSum[j] & 0x1fff;  //changed by N.CHIKUMA 2015 Oct 6
         double scalerCount = scalerValuesSum[j] & 0xffff;
         //cout << "scalerCount: " << scalerCount << ", ";
         if(!ovf && scalerCount != 0) {
            //double rate = scalerCount / counterCount;
            //cout << "rate: " << rate << endl;
            //scaler[j]=rate;
         }
     	}
	}
#endif
   }
}


void EASIROCDisplay::ReplaceRun()
{
   printf("Stop Filling Hists, and rm ./linker\n");
	m_stop = true;
   const char *lst;
   const char *rmv;
	//lst = "ls -l ./linker";
   rmv = "rm ./linker";
	//system(lst);
	system(rmv);
  	//fclose(_fData);
   m_datFile.close();
}


// ----- destructor
EASIROCDisplay::~EASIROCDisplay()
{
   std::cerr << "call destructor\n" << std::endl;
}

typedef TGHorizontalFrame TGHoriFrame;
typedef TGCompositeFrame TGCompFrame;
typedef TRootEmbeddedCanvas TEmbCanv;

// ----- constructor
EASIROCDisplay::EASIROCDisplay(const TGWindow *p,UInt_t w,UInt_t h)
: m_evnt(200), m_stop(false)//, m_smooth(50)
//int main(int argc, char *argv[])
{
   std::cerr << "call EASIROCDisplay constructor\n" << std::endl;
   TGMainFrame *mainF = new TGMainFrame(p,w,h);
   TGHoriFrame *horiF = new TGHoriFrame(mainF, 60, 20, kFixedWidth);

   TGTextButton *exit = new TGTextButton(horiF, "&Exit");//,  "gApplication->Terminate(0)");
   TGTextButton *load = new TGTextButton(horiF, "&Load");//, "EASIROCDisplay::LoadData()");
   TGTextButton *stop = new TGTextButton(horiF, "&Replace");//,  "Sleep()");
   m_index            = new TGNumberEntry(horiF,200,0,-1, TGNumberFormat::kNESInteger, TGNumberFormat::kNEANonNegative);

   m_index->Connect("ValueSet(Long_t)","EASIROCDisplay",this,"InputIndex()");
   load   ->Connect("Clicked()","EASIROCDisplay",this,"LoadData()");
   stop   ->Connect("Clicked()","EASIROCDisplay",this,"ReplaceRun()");
   exit   ->Connect("Clicked()","EASIROCDisplay",this,"Terminate()");

   horiF->AddFrame(m_index, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2));
   horiF->AddFrame(load,    new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2));
   horiF->AddFrame(stop,    new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2));
   horiF->AddFrame(exit,    new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX, 2, 2, 2, 2));

   horiF->Resize(500, exit->GetDefaultHeight());
   mainF->AddFrame(horiF, new TGLayoutHints(kLHintsBottom | kLHintsRight, 2, 2, 5, 1));

   //--------- create the Tab widget
   TGTab *fTab = new TGTab(mainF, 300, 300);
   
   //--------- create an empty tab element
   TGCompFrame *compfMain;
   TGCompFrame *compfEmb[6];// = new TGCompositeFrame(compfMain, 60, 60, kHorizontalFrame);
	TEmbCanv *embCanv[6];//
   TGLayoutHints *layout = new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY, 3, 3, 3, 3);

	for (int i=0; i<4; i++) {
		std::stringstream name;
		name << "Tab " << i << std::ends;
		compfMain = fTab->AddTab(name.str().data());
		compfEmb[i] = new TGCompFrame(compfMain, 60, 60, kHorizontalFrame);
		embCanv[i]  = new TEmbCanv(name.str().data(), compfEmb[i], 1400, 950);		
 
      std::stringstream cname;
      cname << "Can " << i << std::ends;
		int canID = embCanv[i] ->GetCanvasWindowId();
   	m_can[i] = new TCanvas(cname.str().data(), 10, 10, canID);
		m_can[i]->Divide(4,4);
		for (int j=0; j<16; j++) {
			m_can[i] ->cd(1+j);
         gPad->SetBottomMargin(0.10);
         gPad->SetTopMargin   (0.01);
         gPad->SetRightMargin (0.01);
         gPad->SetLeftMargin  (0.10);
		}
   	embCanv[i]->AdoptCanvas(m_can[i]);

     	compfEmb[i]->AddFrame(embCanv[i], layout);
		compfMain  ->AddFrame(compfEmb[i], layout);
	}

   // make tab yellow
   //Pixel_t yellow;
   //gClient->GetColorByName("yellow", yellow);
   //TGTabElement *tabel = fTab->GetTabTab("Tab 2");;
   //tabel->ChangeBackground(yellow);

   //-------------- end embedded canvas
   mainF->AddFrame(fTab, new TGLayoutHints(kLHintsBottom | kLHintsExpandX | kLHintsExpandY, 2, 2, 4, 2));
   mainF->MapSubwindows();
   mainF->Resize();   // resize to default size
   mainF->MapWindow();

	PrepareHist();
}
