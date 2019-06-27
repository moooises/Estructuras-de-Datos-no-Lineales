#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template<typename tCoste>
int tarifamin(const GrafoP<tCoste>& Tren,const GrafoP<tCoste>& Bus,typename GrafoP<int>::vertice origen,typename GrafoP<int>::vertice destino)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  vector<vertice> P;
  vector<tCoste> desdetren=Dijkstra(Tren,origen,P);
  vector<tCoste> desdebus=Dijkstra(Bus,origen,P);
  vector<tCoste> entren=DijkstraInv(Tren,destino,P);
  vector<tCoste> enbus=DijkstraInv(Bus,destino,P);
  tCoste tarifa;
  tCoste costetren=desdetren[destino];
  tCoste costebus=desdebus[destino];
  tCoste c=min(costebus,costetren);
  tCoste minimo=GrafoP<tCoste>::INFINITO;

    for(int i=0;i<Tren.numVert();++i)
    {
      if(i!=origen)
      {
        for(int j=0;j<Tren.numVert();++j)
        {
          if(j!=destino)
          {
            tCoste aux=min(suma(desdetren[i],enbus[j]),suma(desdebus[i],entren[j]));
            if(aux<minimo) minimo=aux;
          }
        }
      }
    }
    if(c<minimo)minimo=c;
  return minimo;

}

int main()
{
  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  string b="nf2.txt";

  GrafoP<int> Tren(a);
  GrafoP<int> Bus(b);

  vertice origen=0;
  vertice destino=3;

  int tarifa=tarifamin(Tren,Bus,origen,destino);
  cout<<"La tarifa minima es: "<<tarifa<<endl;

}
