#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <typename tCoste>
int caminomin(const GrafoP<tCoste>& Tren,const GrafoP<tCoste>& Bus, typename GrafoP<tCoste>::vertice cambio1,typename GrafoP<tCoste>::vertice cambio2,typename GrafoP<tCoste>::vertice origen,typename GrafoP<tCoste>::vertice destino,  vector<typename GrafoP<tCoste>::vertice>& ruta)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  ruta.push_back(origen);
  vector<vertice> P;
  vector<tCoste> desdetren=Dijkstra(Tren,origen,P);
  vector<tCoste> desdebus=DijkstraInv(Bus,destino,P);
  tCoste coste;
  if(suma(desdetren[cambio1],desdebus[cambio1])<suma(desdetren[cambio2],desdebus[cambio2]))
  {
    ruta.push_back(cambio1);
    coste=suma(desdetren[cambio1],desdebus[cambio1]);
  }
  else
  {
    ruta.push_back(cambio2);
    coste=suma(desdetren[cambio2],desdebus[cambio2]);
  }
  ruta.push_back(destino);
  return coste;
}

int main()
{

    typedef typename GrafoP<int>::vertice vertice;

    string a="nf.txt";
    string b="nf2.txt";

    GrafoP<int> Tren(a);
    GrafoP<int> Bus(b);

    vector<vertice> ruta;
    vertice cambio1=2;
    vertice cambio2=4;
    vertice origen=0;
    vertice destino=3;

    int coste= caminomin(Tren,Bus,cambio1,cambio2,origen,destino,ruta);

    cout<<"EL coste es: "<<coste<<endl;
    cout<<"La ruta es: ";
    for(size_t i =0;i<ruta.size();++i)
    {
      cout<<" "<<ruta[i];
    }



}
