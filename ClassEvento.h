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


void TrackXZ(Evento e, TGraph *Graph){

std::map<int, double> Zmap;
Zmap.insert(std::make_pair(10, 3.1));
Zmap.insert(std::make_pair(11, 6.3));
Zmap.insert(std::make_pair(12,16.9));
Zmap.insert(std::make_pair(13,20.1));
Zmap.insert(std::make_pair(14,31.2));
Zmap.insert(std::make_pair(20,-1.0));
Zmap.insert(std::make_pair(21,10.1));
Zmap.insert(std::make_pair(22,13.3));
Zmap.insert(std::make_pair(23,24.6));
Zmap.insert(std::make_pair(24,27.8));


        double xpos;
        double zpos;
        double error;
        double errorz = 0.1; //cm
        Graph->SetTitle("Track XZ; X [cm]; Z [cm]");
            for (int i = 0; i<e.ClusterLayer.size(); i++){
                if(e.ClusterLayer[i]<15){
                xpos = e.ClusterPosizione[i];
                zpos = Zmap[e.ClusterLayer[i]];
                error = Error(e.InitialStrip[i], e.ClusterDimension[i]);

                Graph->SetPoint(Graph->GetN(),xpos, zpos);
                }
            }   
};











void TrackYZ(Evento e, TGraph *Graph){

std::map<int, double> Zmap;
Zmap.insert(std::make_pair(10, 3.1));
Zmap.insert(std::make_pair(11, 6.3));
Zmap.insert(std::make_pair(12,16.9));
Zmap.insert(std::make_pair(13,20.1));
Zmap.insert(std::make_pair(14,31.2));
Zmap.insert(std::make_pair(20,-1.0));
Zmap.insert(std::make_pair(21,10.1));
Zmap.insert(std::make_pair(22,13.3));
Zmap.insert(std::make_pair(23,24.6));
Zmap.insert(std::make_pair(24,27.8));

        double ypos;
        double zpos;

        Graph->SetTitle("Track YZ; Y [cm]; Z [cm]");
        for (int i = 0; i<e.ClusterLayer.size(); i++){
            if(e.ClusterLayer[i]>15){
            ypos = e.ClusterPosizione[i];
            zpos = Zmap[e.ClusterLayer[i]];
            Graph->SetPoint(Graph->GetN(),ypos, zpos);
            }
        }   

};


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





double Error(int StripIn, int Dimension){
    int StripFin = StripIn + Dimension;
    double error = (StripFin-StripIn)/(sqrt(12.);
    return error; 
}




