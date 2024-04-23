#include <TMath.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iterator>



class Evento
{
public:
	int NEventi;
	int NHit;
	std::vector<int> Strip;
	std::vector<int> Layer;
	std::vector<int> ClusterDimension;
	std::vector<int> InitialStrip;
	std::vector<int> ClusterLayer;
	std::vector<double> ClusterPosizione;
	int Flags[2] = {0,0};
};


class MyException : public exception { 
private: 
	std::string message; 
  
public: 
	// Constructor accepts a const char* that is used to set 
	// the exception message 
	MyException(const char* msg) 
		: message(msg) 
	{ 
	} 
  
	// Override the what() method to return our message 
	const char* what() const throw() 
	{ 
		return message.c_str(); 
	} 
}; 






double StripCoordinate(int Strip){
	const double StripPitch = 0.0228; //cm
	const double EdgeWidth = 0.1; //cm
	const double LadderSeparation = 0.02; //cm
	double coordinate = EdgeWidth + StripPitch*int(Strip) + (LadderSeparation + 2*EdgeWidth - StripPitch)*int(Strip/384); //formula sbagliata: non funziona...
return coordinate;};

double Error(int StripIn, int Dimension){
	int StripFin = StripIn + Dimension;
	double error = (StripCoordinate(StripFin)-StripCoordinate(StripIn))/(sqrt(12.));
	return error; 
}


double LayerCoordinate(int numero)
{
//ouble shift[10] = {-0.151,0.244,-0.242,0.138,0.023,0.073,-0.197,0.165,-0.189,0.177};
double shift[10] = {0.};

//double shift2[10] = {-0.001, 0.027, -0.032, -0.003, 0.025, 0.003, -0.024, 0.013, 0.050, -0.051};
double shift2[10] = {0.};

std::map<int, double> Zmap;
Zmap.insert(std::make_pair(10, 3.1 - shift[0] - shift2[0]));
Zmap.insert(std::make_pair(11, 6.3 - shift[1] - shift2[1]));
Zmap.insert(std::make_pair(12,16.9 - shift[2] - shift2[2]));
Zmap.insert(std::make_pair(13,20.1 - shift[3] - shift2[3]));
Zmap.insert(std::make_pair(14,31.2 - shift[4] - shift2[4]));
Zmap.insert(std::make_pair(20,-1.0 - shift[5] - shift2[5]));
Zmap.insert(std::make_pair(21,10.1 - shift[6] - shift2[6]));
Zmap.insert(std::make_pair(22,13.3 - shift[7] - shift2[7]));
Zmap.insert(std::make_pair(23,24.6 - shift[8] - shift2[8]));
Zmap.insert(std::make_pair(24,27.8 - shift[9] - shift2[9]));

double posizione = Zmap[numero];
return posizione;
}



void TrackXZ(Evento e, TGraphErrors *Graph){

double xpos;
double zpos;
double error;
double errorz = 0.; //cm
int n = 0;
Graph->SetTitle("Track XZ; X [cm]; Z [cm]");
for (int i = 0; i<e.ClusterLayer.size(); i++){
	if(e.ClusterLayer[i]<15)
	{
		xpos = e.ClusterPosizione[i];
		zpos = LayerCoordinate(e.ClusterLayer[i]);
		n = Graph->GetN();
		error = Error(e.InitialStrip[i], e.ClusterDimension[i]);
		//errorz = sqrt(0.01+ error*m*m*error);
		Graph->SetPoint(n,xpos, zpos);
		Graph->SetPointError(n,error,errorz);
	}
}
}

void TrackYZ(Evento e, TGraphErrors *Graph){

double ypos;
double zpos;
double error;
double errorz = 0.; //cm
int n = 0;
Graph->SetTitle("Track YZ; Y [cm]; Z [cm]");
for (int i = 0; i<e.ClusterLayer.size(); i++){
	if(e.ClusterLayer[i]>15)
	{
		ypos = e.ClusterPosizione[i];
		zpos = LayerCoordinate(e.ClusterLayer[i]);
		n = Graph->GetN();
		error = Error(e.InitialStrip[i], e.ClusterDimension[i]);
		//errorz = sqrt(0.01+ error*m*m*error);
		Graph->SetPoint(n,ypos, zpos);
		Graph->SetPointError(n,error,errorz);
	}
}
}

void TrackFitXZ(Evento e, TGraphErrors *Graph){ //inverte gli assi

double xpos;
double zpos;
double error;
double errorz = 0.; //cm
int n = 0;
Graph->SetTitle("Track XZ; Z [cm]; X [cm]");
for (int i = 0; i<e.ClusterLayer.size(); i++){
	if(e.ClusterLayer[i]<15)
	{
		xpos = e.ClusterPosizione[i];
		zpos = LayerCoordinate(e.ClusterLayer[i]);
		n = Graph->GetN();
		error = Error(e.InitialStrip[i], e.ClusterDimension[i]);
		//errorz = sqrt(0.01+ error*m*m*error);
		Graph->SetPoint(n,zpos, xpos);
		Graph->SetPointError(n,errorz,error);
	}
}
}

void TrackFitYZ(Evento e, TGraphErrors *Graph){ //inverte gli assi

double ypos;
double zpos;
double error;
double errorz = 0.; //cm
int n = 0;
Graph->SetTitle("Track YZ; Z [cm]; Y [cm]");
for (int i = 0; i<e.ClusterLayer.size(); i++){
	if(e.ClusterLayer[i]>15)
	{
		ypos = e.ClusterPosizione[i];
		zpos = LayerCoordinate(e.ClusterLayer[i]);
		n = Graph->GetN();
		error = Error(e.InitialStrip[i], e.ClusterDimension[i]);
		//errorz = sqrt(0.01+ error*m*m*error);
		Graph->SetPoint(n,zpos, ypos);
		Graph->SetPointError(n,errorz,error);
	}
}
}




void ClusterManualTest(Evento e){

	for (auto x:e.ClusterDimension){
		std:cout<<"Elenco le dimensioni dei cluster"<<'\n';
		std::cout<< x <<'\n';   
	}

	for (auto x :e.Strip){
		std::cout<<"Elenco tutte le strip dell'evento "<< x<<'\n';

	}
	for (auto x :e.Layer){
		std::cout<<"Elenco tutte i layer rispettivi dell'evento "<<x<<'\n';

	}
	for (auto x:e.InitialStrip){
		std::cout<<"Elenco le strip iniziali dei cluster "<< x<<'\n';

	}
	for (auto x:e.ClusterLayer){
		std::cout<<"Ora scrivo i layer delle prime strip dei cluster " << x <<'\n';


	}
	//Ora, se hai fatto il lavoro bene a monte, dovresti verificare che i layer associati ai cluster siano effettivamente  quelli giusti...



};



void UniTestCluster(Evento e){
	int position=0;


	/*for(int i = 0; i < e.ClusterDimension.size();i++){
		if(e.ClusterLayer[i] !=e.Layer[i+position]){
				try{
						throw MyException("Fratm il codice non funziona");				 
				}
				catch (MyException& exc) { 
					// Catch and handle our custom exception 
					cout << "Caught an exception: " << exc.what() << endl; 
					cout << e.ClusterLayer[i]<< " " <<e.Layer[i]<< " "<<i <<'\n';
				} 
		exit(0);
		}

		position += e.ClusterDimension[i]-1;
	}*/

	for(auto x:e.ClusterDimension){
		position += x;
	}
	if(e.NHit == position){
	std::cout<<"Test Passed: La somma delle dimensioni dei cluster e il numero degli hit coincidono."<<'\n';
	}
	else{
		try{
						throw MyException("La somma delle dimensioni dei cluster ed il numero di Hit non coincidono. Error");				 
				}
				catch (MyException& exc) { 
					// Catch and handle our custom exception 
					cout << "Caught an exception: " << exc.what() << endl; 
					std::cout<<position << " "<<e.NHit<<'\n';
				} 
	exit(0);



	}
	std::cout<<position << " "<<e.NHit<<'\n';

}









