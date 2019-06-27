#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <typename tCoste>
int transporte(const GrafoP<tCoste>& Tren,const GrafoP<tCoste>& Bus,typename GrafoP<int>::vertice origen,typename GrafoP<int>::vertice destino,tCoste taxi,vector<typename GrafoP<int>::vertice>& ruta)
{

  typedef typename GrafoP<tCoste>::vertice vertice;

  vector<vertice> ruta1(Tren.numVert()+Bus.numVert());
  vector<vertice> ruta2(Tren.numVert()+Bus.numVert());

  GrafoP<tCoste> t(Tren.numVert()+Bus.numVert());//si son iguales 2*Tren.numVert()
  //Inicializamos el nuevo vector
  for(int i=0;i<Tren.numVert();++i)
  {
    for(int j=0;j<Tren.numVert();++j)
    {
      t[i][j]=Tren[i][j];
    }
  }


  for(int i=Tren.numVert();i<Tren.numVert()+Bus.numVert();++i)
  {
    for(int j=Tren.numVert();j<Tren.numVert()+Bus.numVert();++j)
    {
      t[i][j]=Bus[i-Bus.numVert()][j-Bus.numVert()];
    }
  }
  //Ahora asignamos las tarifas del taxi


      int j=Tren.numVert();
      int i=0;
      while(j!=Tren.numVert()+Bus.numVert())
      {
        t[i][j]=taxi;
        ++i;
        ++j;
      }

      j=0;
      i=Tren.numVert();
      while(j!=Tren.numVert())
      {
        t[i][j]=taxi;
        ++i;
        ++j;
      }

  cout<<t;
  vector<tCoste> coste=Dijkstra(t,origen,ruta1);
  vector<tCoste> d=Dijkstra(t,origen+Tren.numVert(),ruta2);


  for(int i=0;i<coste.size();++i)
  {
    cout<<" "<<coste[i];
  }
cout<<endl;
  for(int i=0;i<d.size();++i)
  {
    cout<<" "<<d[i];
  }
  cout<<endl;


  if(coste[destino]<d[destino+Bus.numVert()])
  {
    ruta=ruta1;
    return coste[destino];
  }
  else{
    ruta=ruta2;
    return d[destino+Bus.numVert()];
  }

}

int main()
{
  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  string b="nf2.txt";

  GrafoP<int> Tren(a);
  GrafoP<int> Bus(b);
  vector<vertice> ruta(Tren.numVert()+Bus.numVert());


  vertice origen=0;
  vertice destino=3;
  int taxi=5;
  int coste=transporte(Tren,Bus,origen,destino,taxi,ruta);
  cout<<"El coste min es: "<<coste<<endl;
  cout<<"El camino es: ";
  for(int i=0;i<ruta.size();++i)
  {
    cout<<" "<<ruta[i];
  }


}
