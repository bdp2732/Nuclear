 #include "TCanvas.h"
 #include "TROOT.h"
 #include "TGraphErrors.h"
 #include "TF1.h"
 #include "TH1F.h"
 #include "TH2F.h"
 #include "TLegend.h"
 #include "TMath.h"
 #include "TLorentzVector.h"
 #include "TChain.h"
 #include "TTree.h"
 #include "TStyle.h"
 #include "TSystem.h"
 #include "TRandom.h"
 #include "TFile.h"
 #include "TLine.h"
 #include "TLatex.h"
 #include "TMatrixD.h"
 #include <iostream>
 #include <fstream>

void minimisation2(Int_t step){
 
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
TChain *tree=new TChain("T");
char filename[200];
sprintf(filename,"/home/fermion2732/Example/pi0_calibration/dvcsbasicwf4_LH2_%d.root",step-1);
tree->Add(filename);
Int_t nentries = tree->GetEntries();
cout<<"nentries = "<<nentries<<endl;
//nentries=10000;
// nentries=nentries/2.;
/////////////////////////// INPUT VARIABLES  ////////////////////////

//Calorimeter
Double_t E1[20];tree->SetBranchAddress("E1",&E1);
Double_t E2[20];tree->SetBranchAddress("E2",&E2);
Int_t numb1[20];tree->SetBranchAddress("numb1",&numb1);
Int_t numb2[20];tree->SetBranchAddress("numb2",&numb2);
Double_t xc1;tree->SetBranchAddress("xc1",&xc1);
Double_t yc1;tree->SetBranchAddress("yc1",&yc1);
Double_t xc2;tree->SetBranchAddress("xc2",&xc2);
Double_t yc2;tree->SetBranchAddress("yc2",&yc2);
Double_t ene1;tree->SetBranchAddress("ene1",&ene1);
Double_t ene2;tree->SetBranchAddress("ene2",&ene2);
Double_t size1;tree->SetBranchAddress("size1",&size1);
Double_t size2;tree->SetBranchAddress("size2",&size2);
Double_t Et;tree->SetBranchAddress("Et",&Et);
Double_t minv;tree->SetBranchAddress("minv",&minv);
Double_t mm2;tree->SetBranchAddress("mm2",&mm2);

Int_t nb;

///////// VARIABLES ////////////////////////////////////////////////////////
Double_t ener[208];

TMatrixD A(208,208),B(1,208);
for(Int_t i=0;i<208;i++){
  B(0,i)=0;
  for(Int_t j=0;j<208;j++) A(i,j)=0;  
}

/////// ANALYSE //////////////////////////////////////////////////////////

for(Int_t evt=0;evt<nentries;evt++){
if(evt%10000==0) cout<<evt<<"/"<<nentries<<endl;
tree->GetEntry(evt);
if(Et>0.&&minv<0.17&&minv>0.10&&ene1>0.2&&ene2>0.2&&mm2+10.5*minv-1.38<1.2&mm2+10.5*minv-1.38>0.5){

for(Int_t j=0;j<208;j++){ener[j]=0.;}
for(Int_t j=0;j<size1;j++){ener[numb1[j]]=E1[j];}
for(Int_t j=0;j<size2;j++){ener[numb2[j]]=E2[j];}
for(Int_t j=0;j<208;j++){
for(Int_t k=0;k<208;k++){A(j,k)+=ener[j]*ener[k];}
B(0,j)+=ener[j]*Et;
}

}	
}//ev loop


/////// FIN ANALYSE //////////////////////////////////////////////////////////
//A.Print();

A.Invert();
TMatrixD C=B*A;
//C->Print();

Double_t coef[208];
Double_t dum;
sprintf(filename,"results/coeff_pi0_4_LH2_iter%d.txt",step-1);
ifstream fcoef(filename);
for(Int_t i=0;i<208;i++){fcoef>>coef[i]>>dum; if(step==1) coef[i]=1.;}
//for(Int_t i=0;i<208;i++){cout<<i<<" "<<coef[i]<<endl;}

cout<<"Writing coefficients to file..."<<endl;
sprintf(filename,"results/coeff_pi0_4_LH2_iter%d.txt",step);
ofstream fcalib(filename);
for(Int_t i=0;i<208;i++){fcalib<<C(0,i)*coef[i]<<" "<<TMath::Sqrt(A(i,i))<<endl;}
cout<<"Done!"<<endl;

}

