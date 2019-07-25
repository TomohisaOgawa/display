//https://www-he.scphys.kyoto-u.ac.jp/member/n.kamo/wiki/doku.php?id=study:software:root:myclass

#ifndef __INCLUDE_GURD_EASIROCDisplay__
#define __INCLUDE_GURD_EASIROCDisplay__

#define MAXSTOREFILE 20
#define MAXCHANNEL 64 

#include <iostream>
#include <fstream>

#include <TGClient.h>
#include <TCanvas.h>
//#include <TApplication.h>
#include <TRandom.h>
#include <TGFrame.h>

#include <TH1F.h>
#include <TObject.h>
#include <TGNumberEntry.h>

//namespace EASIROC {

	class EASIROCDisplay : public TObject
	{
	   // constructor destructor
		public:
	   EASIROCDisplay(const TGWindow *p,UInt_t w,UInt_t h);
	   ~EASIROCDisplay();
	
		void LoadData();
		void ReplaceRun();
   	inline void Terminate() { 
			exit(0); 
		};
      inline void InputIndex() { 
			m_evnt = m_index->GetNumberEntry()->GetNumber(); 
		};

		// define as class-specific constant, initialize once and no change
	   static const int m_nChs = 64;    
		std::ifstream m_datFile;

	   // ----- member variables 
	   private:
		TGNumberEntry *m_index;
		int m_evnt;
		bool m_stop;
		TH1F *m_h1[m_nChs];
		TCanvas *m_can[6];

      // ----- internal member function 
      private:
      inline unsigned int getBigEndian32(const char* b) {
         return  ((b[0] << 24) & 0xff000000) |
                 ((b[1] << 16) & 0x00ff0000) |
                 ((b[2] <<  8) & 0x0000ff00) |
                 ((b[3] <<  0) & 0x000000ff);
      };
      inline bool isAdcHg(unsigned int data) {
         return (data & 0x00680000) == 0x00000000;
      };
      inline bool isAdcLg(unsigned int data) {
         return (data & 0x00680000) == 0x00080000;
      };
      inline bool isTdcLeading(unsigned int data) {
         return (data & 0x00601000) == 0x00201000;
      };
      inline bool isTdcTrailing(unsigned int data) {
         return (data & 0x00601000) == 0x00200000;
      };
      inline bool isScaler(unsigned int data) {
         return (data & 0x00600000) == 0x00400000;
      };

      void PrepareHist();

		//std::fstream m_datFile;
		//FILE* m_datFile;

		ClassDef(EASIROCDisplay,1)
	};

//}
#endif

