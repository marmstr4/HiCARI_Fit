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

void background(Double_t life1, Double_t life2)
{
gROOT->SetBatch(kTRUE);

     fstream file;

     file.open("output_file.csv", std::ios_base::app | std::ios_base::in);

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
   //gROOT->SetBatch(kTRUE);
   /*
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

   MBegamdc->Fit("fitting1","","",mean[0]-50,mean[0]+50);
   MBegamdc->Fit("fitting2","","",mean[1]-50,mean[1]+50);

  cout<<1<<" "<<fitting1->GetParameter(0)<<" "<<fitting1->GetParameter(1)<<" "<<fitting1->GetParameter(2)<<" "<<fitting1->GetChisquare()/fitting1->GetNDF()<<endl;
  cout<<2<<" "<<fitting2->GetParameter(0)<<" "<<fitting2->GetParameter(1)<<" "<<fitting2->GetParameter(2)<<" "<<fitting2->GetChisquare()/fitting2->GetNDF()<<endl;
  */

  Double_t minlim = 300, maxlim = 1100, bkg_tol = -0.9;
  Double_t fit_w= 50, match_w = 25, search_tol = 0.05, search_iter = 10;
  Int_t bkg_iter = 20, npeaks = 2;

  h_E_In131In_128Cd_flash_trig_plas_music->GetXaxis()->SetRangeUser(minlim,maxlim);
  TH1F* bkg = (TH1F*) h_E_In131In_128Cd_flash_trig_plas_music->ShowBackground(bkg_iter);
  h_E_In131In_128Cd_flash_trig_plas_music->Add(bkg,bkg_tol);
  //h_E_In131In_128Cd_flash_trig_plas_music->Draw();

  // Use TSpectrum to find the peak candidates
  TSpectrum *s = new TSpectrum(npeaks);
  Int_t nfound = s->Search(h_E_In131In_128Cd_flash_trig_plas_music,search_iter,"",search_tol);

  TF1  *fitting1 = new TF1("fitting1","gaus",0,2000);
  TF1  *fitting2 = new TF1("fitting2","gaus",0,2000);
  Double_t *mean;

  for (int i = 0; i < npeaks; i++) {
    mean = s->GetPositionX();
    cout<<i<<" "<<mean[i]<<endl;
  }

  h_E_In131In_128Cd_flash_trig_plas_music->Fit("fitting1","","",mean[0]-fit_w,mean[0]+fit_w);
  h_E_In131In_128Cd_flash_trig_plas_music->Fit("fitting2","","",mean[1]-fit_w,mean[1]+fit_w);

 Double_t amp1 = fitting1->GetParameter(0),  amp2 = fitting2->GetParameter(0);
 Double_t mean1=fitting1->GetParameter(1),   mean2 = fitting2->GetParameter(1);
 Double_t sigma1= fitting1->GetParameter(2), sigma2 = fitting2->GetParameter(2);


 TF1 *match1 = new TF1("match1","[0]*TMath::Gaus(x,[1],[2])",mean1-match_w,mean1+match_w);
 TF1 *match2 = new TF1("match2","[0]*TMath::Gaus(x,[1],[2])",mean2-match_w,mean2+match_w);

 match1->SetParameter(0,amp1); match2->SetParameter(0,amp2);
 match1->FixParameter(1,mean1); match2->FixParameter(1,mean2);
 match1->FixParameter(2,sigma1); match2->FixParameter(2,sigma2);

 MBegamdc->Rebin(4);
 MBegamdc->Fit("match1","R");
 cout<<match1->GetChisquare()/match1->GetNDF()<<endl;
 MBegamdc->Fit("match2","R");
 cout<<match2->GetChisquare()/match2->GetNDF()<<endl;

 Double_t abs_redu_chi = match2->GetChisquare()/match2->GetNDF()+match1->GetChisquare()/match1->GetNDF();

 if (file.is_open())
     file <<life1<<" "<<life2<<" "<<match1->GetChisquare()/match1->GetNDF()<<" "<<match2->GetChisquare()/match2->GetNDF()<<" "<<abs_redu_chi<<endl;

  }
