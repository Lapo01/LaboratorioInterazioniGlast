#include"ClassEvento.h"
#include <TMath.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>
void Tracking(const std::string file){

 int X0 = 10;
 int X1 = 11;   
 int X2 = 12;   
 int X3 = 13;   
 int X4 = 14;   
 int Y0 = 20;
 int Y1 = 21;   
 int Y2 = 22;   
 int Y3 = 23;   
 int Y4 = 24;  


std::map<int, std::string> mapping;
mapping.insert(std::make_pair(10,"X0"));
mapping.insert(std::make_pair(11,"X1"));
mapping.insert(std::make_pair(12,"X2"));
mapping.insert(std::make_pair(13,"X3"));
mapping.insert(std::make_pair(14,"X4"));
mapping.insert(std::make_pair(20,"Y0"));
mapping.insert(std::make_pair(21,"Y1"));
mapping.insert(std::make_pair(22,"Y2"));
mapping.insert(std::make_pair(23,"Y3"));
mapping.insert(std::make_pair(24,"Y4"));

 
int stringa[10]  = {X0, X1, X2, X3, X4, Y0, Y1, Y2, Y3, Y4};

TH1F *hist = new TH1F("hist", "Chi2/NDF", 5000, 0, 500);
//TH1F *hist2 = new TH1F("hist2", "NDF", 10, 0, 10);
TH1F *histx = new TH1F("histx", "Chi2/NDF X plane", 5000, 0, 500);
//TH1F *histx2 = new TH1F("histx2", "NDF X plane", 10, 0, 10);
TH1F *histy = new TH1F("histy", "Chi2/NDF Y plane", 5000, 0, 500);
//TH1F *histy2 = new TH1F("histy2", "NDF Y plane", 10, 0, 10);
TH1F *histChi1X = new TH1F("histChi1X", "Chi2, piano X, NDF = 1", 500, 0, 100);
TH1F *histChi2X = new TH1F("histChi2X", "Chi2, piano X NDF = 2", 500, 0, 100);
TH1F *histChi3X = new TH1F("histChi3X", "Chi2, piano X NDF = 3", 500, 0, 100);
TH1F *histChi1Y = new TH1F("histChi1Y", "Chi2, piano Y, NDF = 1", 500, 0, 100);
TH1F *histChi2Y = new TH1F("histChi2Y", "Chi2, piano Y NDF = 2", 500, 0, 100);
TH1F *histChi3Y = new TH1F("histChi3Y", "Chi2, piano Y NDF = 3", 500, 0, 100);

int N=0;

TString TitleZ;
std::vector<TH1D*> ResiduiZ;
for (int i = 0; i < 10; ++i) 
{
	TitleZ ="Residui Layer" + mapping[stringa[i]]+"asse Z con shift";
	TH1D* istogrammaZ = new TH1D(Form("residuiZ_%d", stringa[i]), TitleZ, 2001, -2, 2);
	ResiduiZ.push_back(istogrammaZ);
}
std::map<int, TH1D*> MappaResiduiZ;
for (int i = 0; i<ResiduiZ.size(); i++)
{
	MappaResiduiZ.insert(std::make_pair(stringa[i],ResiduiZ[i]));	
}

TString Title;
std::vector<TH1D*> Residui;
for (int i = 0; i < 10; ++i) 
{
	Title ="Residui Layer" + mapping[stringa[i]]+" con shift";
	TH1D* istogramma = new TH1D(Form("residui_%d", stringa[i]), Title, 2001, -2, 2);
	Residui.push_back(istogramma);
}
std::map<int, TH1D*> MappaResidui;
for (int i = 0; i<Residui.size(); i++)
{
	MappaResidui.insert(std::make_pair(stringa[i],Residui[i]));	
}




std::vector<TCanvas*> CanvasVector;

for (int i = 0; i < 10; ++i) 
{
	TCanvas* canvas = new TCanvas();
	CanvasVector.push_back(canvas);
}

TF1 *lineX = new TF1("lineX", "[0] + [1]*x");
	lineX->SetParName(0,"q");
	lineX->SetParName(1,"m");
	
TF1 *lineY = new TF1("lineY", "[0] + [1]*x");
	lineY->SetParName(0,"q");
	lineY->SetParName(1,"m");  

	

	TString FileName= file;
	TFile *input = new TFile(FileName,"read");
	TTree *tree = (TTree*)input->Get("tree");
	Evento evento;
	Evento *p = &evento;
	cout<<&evento<<'\n';
	tree->SetBranchAddress("eventoprova", &p); 
	int entries = tree->GetEntries();
	cout<<"entries "<<entries<<endl;
	

double mx,qx,my,qy;
//std::vector<double> mx;
//std::vector<double> my;
double chi2X, chi2AttX, chi2Y, chi2AttY;
double res, resZ;

for(int i= 0; i< entries; i++)
{
	tree->GetEntry(i);
	if((evento.Flags[0] == 1)&(evento.Flags[1] == 1)&(evento.Flags[2] == 1))
	{
		N++;	
	//    if(i == 3){
			TGraphErrors *XZ = new TGraphErrors();
			TGraphErrors *YZ = new TGraphErrors();
		
			TrackFitXZ(evento, XZ);
			TrackFitYZ(evento, YZ);
			
			
			XZ->Fit("lineX","qEX0");
			mx = lineX->GetParameter(1);
			qx = lineX->GetParameter(0);
			chi2X = lineX->GetChisquare();
			chi2AttX = XZ->GetN() - 2;
			//dchi2Att = sqrt(2*chi2Att);
			//mx.push_back(m);
			
			//TFitResultPtr fitResultX = XZ->Fit("lineX", "S");
			//cout<<fitResultX<<endl;
	
			
			YZ->Fit("lineY","qEX0");
			my = lineY->GetParameter(1);
			qy = lineY->GetParameter(0);
			chi2Y = lineY->GetChisquare();
			chi2AttY = YZ->GetN() - 2;
			//dchi2Att = sqrt(2*chi2Att);
			//my.push_back(m);
			
			//TFitResultPtr fitResultY = YZ->Fit("lineY", "S");
			//cout<<fitResultY<<endl;
			if(chi2AttX==0)
			{
				//cout<<i<<endl;
				//cout<<XZ->GetN()<<endl;
				cout<<"ziopera "<<evento.NEventi<<endl;
			}
			
			if((chi2AttX>=1)&(chi2AttY>=1))
			{	
				hist->Fill(chi2X/chi2AttX);	
				histx->Fill(chi2X/chi2AttX);
				hist->Fill(chi2Y/chi2AttY);	
				histy->Fill(chi2Y/chi2AttY);
				//hist2->Fill(chi2AttX);
				//histx2->Fill(chi2AttX);
				//hist2->Fill(chi2AttY);
				//histy2->Fill(chi2AttY);
	 		}
	 		
	 		if((chi2AttX==1)&(chi2AttY>=1))
	 		{
	 			histChi1X->Fill(chi2X);
	 		}
	 		if((chi2AttX==2)&(chi2AttY>=1))
	 		{
	 			histChi2X->Fill(chi2X);
	 		}
	 		if((chi2AttX==3)&(chi2AttY>=1))
	 		{
	 			histChi3X->Fill(chi2X);
	 		}
	 		
	 		if((chi2AttY==1)&(chi2AttX>=1))
	 		{
	 			histChi1Y->Fill(chi2Y);
	 		}
	 		if((chi2AttY==2)&(chi2AttX>=1))
	 		{
	 			histChi2Y->Fill(chi2Y);
	 		}
	 		if((chi2AttY==3)&(chi2AttX>=1))
	 		{
	 			histChi3Y->Fill(chi2Y);
	 		}
	 		
	 		
	 		//if(chi2X/chi2AttX>100){cout<<i<<endl;}
	 		if(chi2AttX==2){
			for(auto ii:stringa) //ciclo for per ogni layer
	 		{

	 			for(int jj =0; jj<evento.ClusterLayer.size();jj++) //ciclo for per ogni layer del cluster
	 			{
					if(ii == evento.ClusterLayer[jj])
					{
						if(ii<15)
						{
							resZ =  LayerCoordinate(ii)- (evento.ClusterPosizione[jj] - qx)/mx;
							MappaResiduiZ[ii]->Fill(resZ);
							res =  evento.ClusterPosizione[jj] - lineX->Eval(LayerCoordinate(ii));
							MappaResidui[ii]->Fill(res);
							//if((ii==X4)&(res>0.02)&(res<0.06))
							//{
							//	cout<<i<<endl;
							//}
	 					}
						if(ii>15)
						{
							resZ =  LayerCoordinate(ii)- (evento.ClusterPosizione[jj] - qy)/my;
							MappaResiduiZ[ii]->Fill(resZ);
							res =  evento.ClusterPosizione[jj] - lineY->Eval(LayerCoordinate(ii));
							MappaResidui[ii]->Fill(res);
	 					}
	 				}
	 			}
	 		}
//		}
	}
	}
}
cout<<"Eventi che soddisfano i flag "<<N<<endl;
TString TitleFile;
/*
TCanvas *c1 = new TCanvas();
hist->Draw();

//TCanvas *c2 = new TCanvas();
//hist2->Draw();

TCanvas *c3 = new TCanvas();
histx->Draw();

//TCanvas *c4 = new TCanvas();
//histx2->Draw();

TCanvas *c5 = new TCanvas();
histy->Draw();

//TCanvas *c6 = new TCanvas();
//histy2->Draw();


TCanvas *c6 = new TCanvas();
histChi1X->Draw();

TCanvas *c7 = new TCanvas();
histChi2X->Draw();

TCanvas *c8 = new TCanvas();
histChi3X->Draw();

TCanvas *c9 = new TCanvas();
histChi1Y->Draw();

TCanvas *c10 = new TCanvas();
histChi2Y->Draw();

TCanvas *c11 = new TCanvas();
histChi3Y->Draw();
*/

for(int i =0; i<10; i++)
{
	TitleFile = "Grafici/Residui/ZLayer" + mapping[stringa[i]] + "Shift.png";
	CanvasVector[i]->cd();
	Residui[i]->Draw();
	//CanvasVector[i]->SaveAs(TitleFile);
}


}
