//#ifndef "ClassEvento.h"
#include"ClassEvento.h"
#include <TMath.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>

void LetturaTree(const std::string file)
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









 int stringa[10]  = {X0, X1, X2, X3, X4, Y0, Y1, Y2, Y3, Y4};
 TString FileName= file;
 TString SaveDist = file+"HitDistribution" + "pdf";
	TFile *input = new TFile(FileName,"read");
    
	TTree *tree = (TTree*)input->Get("tree");
	
    
    TString Title1;
    TString Title2;
    TString Title3;
        TString Title4;
    TString SaveFileOcc;
    TString SaveFileHit;
    TString SaveFile3;
        TString SaveFile4;
	Evento evento;
    Evento *p = &evento;
    cout<<&evento<<'\n';
	tree->SetBranchAddress("eventoprova", &p); 
    int NHit;
    int NEventi;	
    int NHitPerLayer = 0;
    std::vector<int> Strip;
    std::vector<int> Layer;
	
	int entries = tree->GetEntries();
	cout << entries << endl;
/*
for (auto x:stringa){
    
    

    //int x = stringa[1];
    Title1 ="Strip Occupancy Layer" + mapping[x];
    Title2 ="Hit Distribution for Layer" + mapping[x];
    TH1F *hist = new TH1F("hist", "Hit Distribution", 100, 0, 100);
    TH1F *hist2 = new TH1F("hist", Title1, 1536, 0, 1536);
    TH1F *hist3 = new TH1F("hist", Title2, 10, 0, 10);
    for(int i= 0; i< entries; i++){
    tree->GetEntry(i);
    NHit = evento.NHit;
    hist->Fill(NHit);
    NEventi = evento.NEventi;
    for (int j = 0; j<NHit; j++){
    if (evento.Layer[j] == x){   // guarda qui
    
    hist2->Fill(evento.Strip[j]);
    NHitPerLayer++;
    //cout<<NHitPerLayer<<'\n';     
    }
    }
    hist3->Fill(NHitPerLayer); 
    NHitPerLayer = 0;
    //cout<<"Ho resettato NHitPerLAyer"<<'\n';
    
    
    }
    
    
    //cout<<evento.NHit<<'\n';
    TCanvas *c1 = new TCanvas();

    hist->Draw();

    TCanvas *c2 = new TCanvas();
    c2->SetLogy();    
    hist2->Draw();

    TCanvas *c3 = new TCanvas();
    hist3->Draw();
    
    SaveFileOcc = "StripOccupancyLayer" + mapping[x] + "pdf";
    SaveFileHit= "HitDistribution" +mapping[x] +"pdf";
    
    c2->SaveAs(SaveFileOcc);
    c3->SaveAs(SaveFileHit);
    c1->SaveAs(SaveDist);
    delete hist2;
    delete hist3;
    delete hist;
    delete c1;
    delete c2;
    delete c3;
    
   }*/
   /*for(int i= 0; i< entries; i++){
        tree->GetEntry(i);
        Cluster(evento); 
   }*/

   tree->GetEntry(101);
   std::cout<<"il numero di hit è " <<evento.NHit<<'\n';
   TrackYZ(evento); 
   ClusterManualTest(evento);
   //UniTestCluster(evento);


    TH1F *hist = new TH1F("hist", "Total Cluster Length Distribution Eventi", 50, 0, 50);
    TH1F *hist5 = new TH1F("hist", "Total Cluster Number Distribution Eventi", 100, 0, 100);
   int DimCluster =0;
   for(auto x:stringa){  
       Title1 ="Cluster Position Distribution Eventi" + mapping[x];
       Title2 ="Cluster Dimension Distribution Eventi" + mapping[x];
       Title3 ="Number of Cluster Distribution" + mapping[x];
    TH1F *hist2 = new TH1F("hist", Title1, 1536, 0, 1536);
    TH1F *hist3 = new TH1F("hist", Title2, 50, 0, 50);
    TH1F *hist4 = new TH1F("hist", Title3, 50, 0, 50);
    for(int i = 0; i <entries; i++){
        tree->GetEntry(i);

        //if (evento.BuonCluster == 1){

            for(int j = 0; j< evento.ClusterLayer.size(); j++){
                if(evento.ClusterLayer[j] == x){
                    hist2->Fill(evento.ClusterPosizione[j]);
                    hist3->Fill(evento.ClusterDimension[j]);
                    DimCluster++;
                }
                hist->Fill(evento.ClusterDimension[j]);
            }
           hist4->Fill(DimCluster);
           DimCluster =0; 
           hist5->Fill(evento.ClusterLayer.size());
        //}
    }
         TCanvas *c1 = new TCanvas();
         hist2->GetXaxis()->SetTitle("Position[Strip]");
         hist2->GetYaxis()->SetTitle("Counts");
         hist2->Draw();
         
         TCanvas *c2 = new TCanvas();
         c2->SetLogy();    
         hist3->GetXaxis()->SetTitle("Number of Strips in the Cluster");
         hist3->GetYaxis()->SetTitle("Counts");
         hist3->Draw();
         
         TCanvas *c4 = new TCanvas();
         c4->SetLogy();
         hist4->GetXaxis()->SetTitle("Number of Clusters");
         hist4->GetYaxis()->SetTitle("Counts");
         hist4->Draw();
         SaveFileOcc = "ClusterDimensionDistribution" + mapping[x] + "pdf";
         SaveFileHit= "ClusterPositionDistribution " +mapping[x] +"pdf";
         SaveFile3 = "ClusterNumberDistribution " + mapping[x]+"pdf";
         c1->SaveAs(SaveFileHit);  
         c2->SaveAs(SaveFileOcc); 
         c4->SaveAs(SaveFile3);
         delete hist2;
         delete c1;
         delete c2;
         delete hist3;
         delete c4;
         delete hist4;
    }
TCanvas *c3 = new TCanvas();
c3->SetLogy();  
hist->GetXaxis()->SetTitle("Number of Strips in the Cluster");
hist->GetYaxis()->SetTitle("Counts");  
hist->Draw();
c3->SaveAs("ClusterTotalDimensionDistributionEvento.pdf");   

TCanvas *c5 = new TCanvas();
c5->SetLogy();
hist5->GetXaxis()->SetTitle("Number of Clusters");
hist5->GetYaxis()->SetTitle("Counts");
hist5->Draw();
c5->SaveAs("ClusterNumberTotalDistributionEvento.pdf");
}


//#endif
