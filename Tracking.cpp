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

TF1 *line = new TF1("line", "[0] + [1]*x");
    line->SetParameters(0, 1);
    line->SetParName(0,"q");
    line->SetParName(1,"m");
    
  

    

    TString FileName= file;
    TFile *input = new TFile(FileName,"read");
	TTree *tree = (TTree*)input->Get("tree");
	Evento evento;
    Evento *p = &evento;
    cout<<&evento<<'\n';
	tree->SetBranchAddress("eventoprova", &p); 
	int entries = tree->GetEntries();
	


for(int i= 0; i< entries; i++){
    tree->GetEntry(i);
    if((evento.Flags[0] == 1)&(evento.Flags[1] == 1)){
    
        if(i == 3){

        TGraphErrors *YZ = new TGraphErrors();
        TGraphErrors *XZ = new TGraphErrors();
        
        TrackYZ(evento, YZ);
        TrackXZ(evento, XZ);
        YZ->Fit("line","q");
        XZ->Fit("line","q");
        
        cout<<line->GetNDF()<<endl;
        cout<<line->GetChisquare()<<endl;
        cout<<line->GetProb()<<endl;
        }
    }




}





















}
