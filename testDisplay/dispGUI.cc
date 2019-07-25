//#include "classEASIROCSpectrum.h"
#include "classEASIROCDisplay.h"

#include "TStyle.h"
#include "TApplication.h"

int main(int argc,char *argv[])
{
	// ----- ROOT settings
   gStyle->SetFrameLineWidth(1);
   gStyle->SetHistLineWidth(1);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetLineScalePS(1);

	// need to define, otherwise ROOT system gives 
	//  *** Break *** segmentation violation ... 
   TApplication app("EASIROCDisplay",&argc, argv);

   // Popup the GUI...
   //SpectrumGUI *spec = new SpectrumGUI(gClient->GetRoot(),1000,1000);
   new EASIROCDisplay(gClient->GetRoot(),1000,1000);

   // from classEASIROCSpectrum.cc
   //a = new EASIROCSpectrum(64);
   //new EASIROCSpectrum(64);
   app.Run(kTRUE);
	return 0;
}


