#include"ClassEvento.h"
#include <TMath.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>

/*
class Evento
{
public:
int NEventi;
int NHit;
std::vector<int> Strip;
std::vector<int> Layer;
};
*/
void Track()
{
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

TFile *input = new TFile("Dati/DatiTree/TkrDataTaking_333000376.root","read");
TTree *tree = (TTree*)input->Get("tree");
TGraph *trackxz = new TGraph();
TGraph *trackyz = new TGraph();


Evento evento;
Evento *p = &evento;
tree->SetBranchAddress("eventoprova", &p); 
int NHit;
int NEventi;	
int NHitPerLayer = 0;
std::vector<int> Strip;
std::vector<int> Layer;

double StripPitch = 0.0228; //centimetri
double EdgeWidth = 0.1; //centimetri
double LadderSeparation = 0.02; //centimetri
double StripCoordinate;
double x,y,z;
	
int entries = tree->GetEntries();
cout <<"entries "<< entries << endl;

tree->GetEntry(762520);
NHit = evento.NHit;
NEventi = evento.NEventi;
for (int j = 0; j<NHit; j++)
{
	StripCoordinate = EdgeWidth + StripPitch*evento.Strip[j] + (LadderSeparation + 2*EdgeWidth - StripPitch)*int(evento.Strip[j]/384); //centimetri

	if(evento.Layer[j] < 15) //hit appartiene ai piani X
	{
		z = LayerCoordinate(evento.Layer[j]);
		x = StripCoordinate; //centimetri
	//	x = evento.Strip[j];
		trackxz->SetPoint(trackxz->GetN(), x, z);
	}
	
	if(evento.Layer[j] > 15) //hit appartiene ai piani Y
	{
		z = LayerCoordinate(evento.Layer[j]);
		y = StripCoordinate; //centimetri
	//	y = evento.Strip[j];
		trackyz->SetPoint(trackyz->GetN(), y, z);
	}
	
}



/*
for(int i = 0; i<entries; i++)
{
	tree->GetEntry(i);
	NHit = evento.NHit;
	NEventi = evento.NEventi;
	for(int j = 0; j< NHit; j++)
	{
		if (evento.Layer[j] == X4)
		{
			hist->Fill(evento.Strip[j]);
		}
	}
}
*/

/*
TCanvas *c1 = new TCanvas();
trackxz->Draw("A*");
trackxz->SetTitle("Traccia piano XZaaa; x [cm];z [cm]");
trackxz->SetMarkerStyle(20);

TCanvas *c2 = new TCanvas();
trackyz->Draw("A*");
trackyz->SetTitle("Traccia piano YZ; y [cm];z [cm]");
trackyz->SetMarkerStyle(20);*/

/*TCanvas *c3 = new TCanvas();
hist->Draw(); */

TGraphErrors *XZ = new TGraphErrors();        
TrackXZ(evento, XZ);

TCanvas *c3 = new TCanvas();
XZ->Draw("A*");
XZ->SetMarkerStyle(20);

TGraphErrors *YZ = new TGraphErrors();        
TrackYZ(evento, YZ);

TCanvas *c4 = new TCanvas();
YZ->Draw("A*");
YZ->SetMarkerStyle(20);
}







