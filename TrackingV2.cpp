#include"ClassEvento.h"
#include <TMath.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>
void TrackingV2(const std::string file){

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
TH1F *histChi1X = new TH1F("histChi1X", "Chi2, piano X, NDF = 1 senza shift su Z", 500, 0, 100);
TH1F *histChi2X = new TH1F("histChi2X", "Chi2, piano X NDF = 2 senza shift su Z", 500, 0, 100);
TH1F *histChi3X = new TH1F("histChi3X", "Chi2, piano X NDF = 3 senza shift su Z", 500, 0, 100);
TH1F *histChi1Y = new TH1F("histChi1Y", "Chi2, piano Y, NDF = 1 senza shift su Z", 500, 0, 100);
TH1F *histChi2Y = new TH1F("histChi2Y", "Chi2, piano Y NDF = 2 senza shift su Z", 500, 0, 100);
TH1F *histChi3Y = new TH1F("histChi3Y", "Chi2, piano Y NDF = 3 senza shift su Z", 500, 0, 100);
TH2F *hist2d = new TH2F("hist2d","residui X4 vs posizione Y4", 2001, 0, 50, 2001, -2, 2);

int N=0;

TString TitleZ;
std::vector<TH1D*> ResiduiZ;
for (int i = 0; i < 10; ++i) 
{
	TitleZ ="Residui Layer" + mapping[stringa[i]]+"asse Z";
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
	Title ="Residui Layer" + mapping[stringa[i]]+" ";
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
double chi2X, chi2AttX, chi2Y, chi2AttY;
double res, resZ;
int indice;
int shift;

for(int i= 0; i< entries; i++)
{
	tree->GetEntry(i);
	if((evento.Flags[0] == 1)&(evento.Flags[1] == 1))
	{
	for (auto ii:stringa)
	{
		shift = 0;
		N++;	
			TGraphErrors *XZ = new TGraphErrors();
			TGraphErrors *YZ = new TGraphErrors();
		
			TrackFitXZ(evento, XZ, ii);
			TrackFitYZ(evento, YZ, ii);
			
		
			XZ->Fit("lineX","qEX0");
			mx = lineX->GetParameter(1);
			qx = lineX->GetParameter(0);
			chi2X = lineX->GetChisquare();
			chi2AttX = XZ->GetN() - 2;
			
			YZ->Fit("lineY","qEX0");
			my = lineY->GetParameter(1);
			qy = lineY->GetParameter(0);
			chi2Y = lineY->GetChisquare();
			chi2AttY = YZ->GetN() - 2;

			
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
	 				}
					if(ii>15)
					{
						resZ =  LayerCoordinate(ii)- (evento.ClusterPosizione[jj] - qy)/my;
						MappaResiduiZ[ii]->Fill(resZ);
						res =  evento.ClusterPosizione[jj] - lineY->Eval(LayerCoordinate(ii));
						MappaResidui[ii]->Fill(res);
	 				}
					indice = IndiceVettore(evento.ClusterLayer, 24);
	 				if((ii == 14)&(indice>=0))
	 				{
	 					hist2d->Fill(evento.ClusterPosizione[indice], res);
	 				}
	 			}
	 		}
	 	}
	}
	}

cout<<"Eventi che soddisfano i flag "<<N<<endl;
TString TitleFile;


for(int i =0; i<10; i++)
{
	TitleFile = "Grafici/Residui/ZLayer" + mapping[stringa[i]] + "Shift.png";
	CanvasVector[i]->cd();
	Residui[i]->Draw();
	//CanvasVector[i]->SaveAs(TitleFile);
}

TCanvas *asdf = new TCanvas();
hist2d->Draw();

}
