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

  }
