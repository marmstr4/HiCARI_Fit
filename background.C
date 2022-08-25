#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TFrame.h"
#include "TBenchmark.h"
#include "TString.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TROOT.h"
#include "TError.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TPaveText.h"
#include "stdio.h"
#include "TTree.h"
#include <iostream>
#include <fstream>
#include "THStack.h"
#include "TSpectrum.h"
void background()
{

  FILE *input_file = fopen("no_subtract.root", "a");

/*
  THStack *hs = new THStack("hs","histo");
  gStyle->SetPalette(1);

  hs->Add(h_E_In130Cd_129Cd_flash_trig_plas_music);
  hs->Add(h_E_In130Cd_129Cd_flash_trig_plas_music_miniball);
  hs->Add(h_E_In130Cd_129Cd_flash_trig_plas_music_superclover);

  hs->Draw("pfc nostack");
*/
  //TH1F* bkg = (TH1F*) h_E_In132Sn_131In_flash_trig_plas_music->ShowBackground(20);

  //TH1F* bkg = (TH1F*) h_E_In131In_128Cd_flash_trig_plas_music->ShowBackground(20);

  //h_E_In131In_128Cd_flash_trig_plas_music->Add(bkg,-0.9);

  //h_E_In132Sn_131In_flash_trig_plas_music->Rebin(2);

  /*
  THStack *hs = new THStack("hs","histo");
  gStyle->SetPalette(1);

  hs->Add(h_E_In131In_128Cd_flash_trig_plas_music);
  hs->Add(h_E_In131In_128Cd_flash_trig_plas_music_miniball);
  hs->Add(h_E_In131In_128Cd_flash_trig_plas_music_superclover);

  //h_E_In131In_128Cd_flash_trig_plas_music->SetLineColor(1);
  //h_E_In131In_128Cd_flash_trig_plas_music->Draw("same");

  MBegamdc->SetLineColor(7);
  MBegamdc->Rebin(4);

  hs->Draw("pfc nostack");

  MBegamdc->Draw("same");
  */
   gROOT->SetBatch(kTRUE);

   int npeaks = 2;
   MBegamdc->GetXaxis()->SetRangeUser(500,1100);
   // Use TSpectrum to find the peak candidates
   TSpectrum *s = new TSpectrum(npeaks);
   Int_t nfound = s->Search(MBegamdc,25,"",0.50);

   TF1  *fitting1 = new TF1("fitting1","gaus",0,2000);
   TF1  *fitting2 = new TF1("fitting2","gaus",0,2000);
   Double_t *mean;

   for (int i = 0; i < npeaks; i++) {
     mean = s->GetPositionX();


     cout<<i<<" "<<mean[i]<<endl;
   }

   MBegamdc->Fit("fitting1","","",mean[0]-25,mean[0]+25);
   MBegamdc->Fit("fitting2","","",mean[1]-25,mean[1]+25);

     cout<<1<<" "<<fitting1->GetParameter(0)<<" "<<fitting1->GetParameter(1)<<" "<<fitting1->GetParameter(2)<<endl;
     cout<<2<<" "<<fitting2->GetParameter(0)<<" "<<fitting2->GetParameter(1)<<" "<<fitting2->GetParameter(2)<<endl;


  }
