#include "ClassEvento.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>




void CreateTree(const std::string &fileinput, const std::string &fileoutput){


std::vector<int> OS ;
std::vector<int> ImStuffUwU;
std::vector<int> ClusterDimension;
std::vector<int> InitialStrip;
std::vector<int> LayerEvento;
std::vector<int> StripEvento;
std::vector<int> indices;

std::vector<int> StripLayer;

//std::vector<int> Clus;

int LengthCluster=1;
int check = 0;
int NEventi = 0;
int NHit= 0;
TString nomefile = fileoutput; //necessario renderlo come TString sennò si lamenta...
Evento eventoprova;
TFile *output = new TFile(nomefile, "recreate");
TTree *tree = new TTree("tree", "tree");
tree->Branch("eventoprova",&eventoprova);



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

std::vector<Evento> VettoreEventi;

std::map<std::string, int> mapping;
mapping.insert(std::make_pair("X0",10));
mapping.insert(std::make_pair("X1",11));
mapping.insert(std::make_pair("X2",12));
mapping.insert(std::make_pair("X3",13));
mapping.insert(std::make_pair("X4",14));
mapping.insert(std::make_pair("Y0",20));
mapping.insert(std::make_pair("Y1",21));
mapping.insert(std::make_pair("Y2",22));
mapping.insert(std::make_pair("Y3",23));
mapping.insert(std::make_pair("Y4",24));
//cout<< "Debugging:"<<mapping["X0"]<<'\n'; // unit testing della mappa (fatto dentro il codice stesso ma vabbè...)
//std::map<std::string, std::vector<int>> mymap;
std::string line;


int ciclo = 0;
int Xx[10]  = {X0, X1, X2, X3, X4, Y0, Y1, Y2, Y3, Y4};
int NumeroStripLayer=0;


std::vector<int> MutedStripX0;
std::vector<int> MutedStripX1;
std::vector<int> MutedStripX2;
std::vector<int> MutedStripX3;
std::vector<int> MutedStripX4;
std::vector<int> MutedStripY0;
std::vector<int> MutedStripY1;
std::vector<int> MutedStripY2;
std::vector<int> MutedStripY3;
std::vector<int> MutedStripY4;

std::vector<std::vector<int>> MutedVector = {MutedStripX0,MutedStripX1,MutedStripX2,MutedStripX3,MutedStripX4,MutedStripY0,MutedStripY1,MutedStripY2,MutedStripY3,MutedStripY4};



std::map<int, std::vector<int>> MapDeiVettoriMutati;
for (int i = 0; i<MutedVector.size(); i++) 
{
	MapDeiVettoriMutati.insert(std::make_pair(Xx[i],MutedVector[i]));	
}


std::vector<int> Strips;
int a;

std::ifstream myfile_in(fileinput);

for(auto x:Xx){//trovare strip mutate
ciclo =0;


TH1F *h = new TH1F("hist", "Hit Distribution", 1536, 0, 1536);

	if (myfile_in.is_open())
	{ cout<<"ok"<<endl;	   
		while(getline(myfile_in, line))
		{
			if(ciclo>0){ //questo esclude la prima linea del file, che è da scartare.


				std::istringstream iss{line};
				std::vector<std::string> words{
				std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>()
			};
			
			NHit = stoi(words[1]);
		
			for(int i = 0; i<NHit; i++)
			{
				if(mapping[words[i+2+4*i]] ==x){
				Strips.push_back(stoi(words[i+4+4*i]));
				
				}
			}

			for (auto y:Strips){
				h->Fill(y);
			}
		}
		ciclo++;
		Strips.clear();
		
		}

	}
   
	for(int i= 1; i<1537; i++)
	{
		a= h->GetBinContent(i);
		if(a==0)
		{
			//if(x==Y0){
			//cout<<i<<endl;}
			MapDeiVettoriMutati[x].push_back(i);
		}
	}

	myfile_in.clear();
	myfile_in.seekg(0);
	delete h;
}

ciclo = 0;
int NCluster =0;
int HitPerPiano[10] = {0};
int FalseTrigger = 0;
int Nx = 0;
int Ny = 0;

std::map<int, int> MapHitPerPiano;
for(int i=0; i<10;i++)
{
	MapHitPerPiano.insert(std::make_pair(Xx[i],HitPerPiano[i]));
}

if (myfile_in.is_open())
{cout<<"ok"<<endl;
while(getline(myfile_in, line))  //creare l'evento da mettere nel tree
{

//if(ciclo == 3){break;}
if(ciclo>0)
{ //questo esclude la prima linea del file, che è da scartare.


std::istringstream iss{line};
std::vector<std::string> words{
std::istream_iterator<std::string>(iss),
std::istream_iterator<std::string>()};



InitialStrip.clear();
ClusterDimension.clear();
eventoprova.Layer.clear();
eventoprova.Strip.clear();
eventoprova.ClusterLayer.clear();
StripEvento.clear();
LayerEvento.clear();
indices.clear();
eventoprova.ClusterDimension.clear();
eventoprova.InitialStrip.clear();
ImStuffUwU.clear();
OS.clear();
eventoprova.Flags[0] = 1;
eventoprova.Flags[1] = 1;
eventoprova.ClusterPosizione.clear();
for(auto x:Xx)
{
	MapHitPerPiano[x] = 0;
}


NEventi = ciclo;
NHit = stoi(words[1]);

eventoprova.NHit =NHit;
eventoprova.NEventi = NEventi;

//int Strip[NHit];
//int Layer[NHit];


for(int i = 0; i<NHit; i++)
{
	LayerEvento.push_back(mapping[words[i+2+4*i]]);
	StripEvento.push_back(stoi(words[i+4+4*i]));
	eventoprova.Layer.push_back(mapping[words[i+2+4*i]]);
	eventoprova.Strip.push_back(stoi(words[i+4+4*i]));
}

for(auto x: Xx) //creare clusters
{
	for(int i = 0; i<NHit; i++)
	{
		if(LayerEvento[i] == x)
		{
			StripLayer.push_back(StripEvento[i]);  //creo il vettore strip attivate nel layer x 
			NumeroStripLayer++;
			MapHitPerPiano[x] = MapHitPerPiano[x] +1;
		}
	}
	std::sort(StripLayer.begin(), StripLayer.end());
	OS = StripLayer;
	LengthCluster=1;
	check = 0;
	for(int j = 1; j< NumeroStripLayer; j++){ 
		if (NumeroStripLayer == 1)
		{
			ImStuffUwU.push_back(1); //se c'è un solo strip salta il ciclo for
			break;
		}
		ImStuffUwU.push_back(OS[j] - OS[j-1]); //vettore differenze numero strip
	}

	for(int j = 0; j<NumeroStripLayer; j++)
	{
		if((ImStuffUwU[j] == 1)&(j!=NumeroStripLayer-1))
		{
			if(check - j == 0)
			{
				LengthCluster++;
				check++;	  
			}
		}
		
		else if((LengthCluster>1))
		{
			check++;
			eventoprova.ClusterDimension.push_back(LengthCluster);
			eventoprova.InitialStrip.push_back(OS[j-LengthCluster+1]);
			eventoprova.ClusterLayer.push_back(x);
			eventoprova.ClusterPosizione.push_back((StripCoordinate(OS[j])+StripCoordinate(OS[j-LengthCluster+1]))/2.);
			for(auto y:MapDeiVettoriMutati[x])
			{
				if (OS[j-LengthCluster+1]-y ==1)
				{				
					eventoprova.Flags[0] = 0;
				}
				if (y-OS[j] ==1)
				{
					eventoprova.Flags[0] = 0;
				}		   	
			}
			NCluster++;
			LengthCluster = 1;
		}
		else 
		{
			eventoprova.ClusterDimension.push_back(LengthCluster);
			eventoprova.InitialStrip.push_back(OS[j]);
			eventoprova.ClusterLayer.push_back(x);
			eventoprova.ClusterPosizione.push_back(StripCoordinate(OS[j]));
			NCluster++;
			for(auto y:MapDeiVettoriMutati[x])
			{
				if (abs(y-OS[j]) ==1)
				{
					eventoprova.Flags[0] = 0;
				}  
			}
			check++;
		}
	}

	if(NCluster > 1)
	{
		eventoprova.Flags[1] = 0;
	}

	OS.clear();
	StripLayer.clear();
	ImStuffUwU.clear();
	NumeroStripLayer = 0;
	NCluster = 0;
}

Nx = 0;
Ny = 0;
for(int i=10; i<15; i++)
{
	if(MapHitPerPiano[i]>0){Nx++;}
	if(MapHitPerPiano[i+10]>0){Ny++;}
}

if((Nx>=3)&(Ny>=3))
{
	tree->Fill();
}
else
{
	FalseTrigger++;
}

}

ciclo++;

}
	output-> Write();
	output->Close();
	myfile_in.close();
	cout<<"eventi totali "<<(ciclo-1)<<endl;
	cout<<"eventi buoni "<<(ciclo-1-FalseTrigger)<<endl;
	cout<<"FalseTrigger "<<FalseTrigger<<endl;
}









}
