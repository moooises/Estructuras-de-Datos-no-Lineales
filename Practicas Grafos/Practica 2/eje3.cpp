#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template<typename tCoste>
int distribucion(const GrafoP<tCoste>& G,vector<tCoste>& cant_distribuidas,vector<tCoste>& capacidad,int& stock,vector<double>& subvencion,typename GrafoP<tCoste>::vertice& origen)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  vector<vertice> P;
  vector<tCoste> transporte=Dijkstra(G,origen,P);
  tCoste coste=0;
  //Ahora aplicamos las subvenciones
  for(int i=0;i<transporte.size();++i)
  {
    //Para no aplicar nada al origen
    if(i!=origen)transporte[i]=transporte[i]-(transporte[i]*(subvencion[i]/100));
  }

  //eliminamos la posicion del origen para facilitarnos todo
  transporte.erase(transporte.begin()+origen);

  for(int i=0;i<transporte.size();++i)
  {
    //Para no aplicar nada al origen
    if(i!=origen)transporte[i]=transporte[i]-(transporte[i]*(subvencion[i]/100));
    cout<<" "<<transporte[i];
  }
  cout<<endl;

  tCoste m;
  tCoste pos;

  while(stock!=0)
  {
    m=GrafoP<tCoste>::INFINITO;
    for(tCoste i=0;i<transporte.size();++i)
    {
    //  cout<<capacidad[i]<<" & "<<transporte[i]<<endl;
      if(m>transporte[i] && capacidad[i]!=0)
      {
        m=transporte[i];
        pos=i;
      }
    }

    if(capacidad[pos]==0)return coste;

    while(capacidad[pos]!=0 && stock!=0)
    {
      capacidad[pos]=capacidad[pos]-1;

      cant_distribuidas[pos]=cant_distribuidas[pos]+1;

      stock=stock-1;

      coste=coste+transporte[pos];
    }

  }
  return coste;

}

int main()
{
  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  GrafoP<int> G(a);
  vector<int> cant_distribuidas;
  cant_distribuidas.push_back(0);
  cant_distribuidas.push_back(0);
  cant_distribuidas.push_back(0);
  cant_distribuidas.push_back(0);
  vector<int> capacidad;
  capacidad.push_back(5);
  capacidad.push_back(10);
  capacidad.push_back(20);
  capacidad.push_back(5);
  int stock=30;
  vector<double> subvencion;
  subvencion.push_back(50);
  subvencion.push_back(80);
  subvencion.push_back(5);
  subvencion.push_back(60);
  vertice origen=1;
  int coste=distribucion(G,cant_distribuidas,capacidad,stock,subvencion,origen);
  cout<<"Stock: "<<stock<<endl;
  cout<<"Coste: "<<coste<<endl;
  for(int i=0;i<cant_distribuidas.size();++i)
  {
    cout<<" "<<cant_distribuidas[i];
  }
}
