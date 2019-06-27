#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <typename tCoste>
int tresmedios(const GrafoP<tCoste>& Bus,const GrafoP<tCoste>& Tren,const GrafoP<tCoste>& Avion,typename GrafoP<tCoste>::vertice origen,typename GrafoP<tCoste>::vertice destino,tCoste trenbus,tCoste avionbustren,vector<typename GrafoP<tCoste>::vertice>& P)
{

  typedef typename GrafoP<tCoste>::vertice vertice;

  GrafoP<tCoste> t(Bus.numVert()+Tren.numVert()+Avion.numVert());

  //Inicializamos la matriz
  for(int i=0;i<Bus.numVert();++i)
  {
    for(int j=0;j<Bus.numVert();++j)
    {
      t[i][j]=Bus[i][j];
    }
  }

  for(int i=Bus.numVert();i<Bus.numVert()+Tren.numVert();++i)
  {
    for(int j=Bus.numVert();j<Bus.numVert()+Tren.numVert();++j)
    {
      t[i][j]=Tren[i-Bus.numVert()][j-Bus.numVert()];
    }
  }

  for(int i=Bus.numVert()+Tren.numVert();i<Bus.numVert()+Tren.numVert()+Avion.numVert();++i)
  {
    for(int j=Bus.numVert()+Tren.numVert();j<Bus.numVert()+Tren.numVert()+Avion.numVert();++j)
    {
      t[i][j]=Avion[i-(Bus.numVert()+Tren.numVert())][j-(Bus.numVert()+Tren.numVert())];
    }
  }

  cout<<t<<endl;

  //Ahora las tasas
  //Primero las de bus-tren y viceversa


    int i=0;
    int j=Bus.numVert();
    while(j!=Bus.numVert()+Tren.numVert())
      {
        t[i][j]=trenbus;
        i++;
        j++;
      }

    i=Bus.numVert();
    j=0;
    while(j!=Bus.numVert())
      {
        t[i][j]=trenbus;
        i++;
        j++;
      }

    //Despues las del aeropuerto

    i=0;
    j=Bus.numVert()+Tren.numVert();
    while(j!=Bus.numVert()+Tren.numVert()+Avion.numVert())
    {
      t[i][j]=avionbustren;
      i++;
      j++;
    }

    i=Bus.numVert();
    j=Bus.numVert()+Tren.numVert();
    while(j!=Bus.numVert()+Tren.numVert()+Avion.numVert())
    {
      t[i][j]=avionbustren;
      i++;
      j++;
    }

    i=Bus.numVert()+Tren.numVert();
    j=0;
    while(j!=Bus.numVert())
    {
      t[i][j]=avionbustren;
      i++;
      j++;
    }

    i=Bus.numVert()+Tren.numVert();
    j=Bus.numVert();
    while(j!=Bus.numVert()+Tren.numVert())
    {
      t[i][j]=avionbustren;
      i++;
      j++;
    }

    i=Bus.numVert()+Tren.numVert();
    j=Bus.numVert()+Tren.numVert();
    while(j!=Bus.numVert()+Tren.numVert()+Avion.numVert())
    {
      t[i][j]=avionbustren;
      i++;
      j++;
    }
    cout<<t<<endl;

    vector<vertice> P1(Tren.numVert()+Bus.numVert()+Avion.numVert());
    vector<vertice> P2(Tren.numVert()+Bus.numVert()+Avion.numVert());
    vector<vertice> P3(Tren.numVert()+Bus.numVert()+Avion.numVert());

    vector<tCoste> c1= Dijkstra(t,origen,P1);
    vector<tCoste> c2= Dijkstra(t,origen+Bus.numVert(),P2);
    vector<tCoste> c3= Dijkstra(t,origen+Bus.numVert()+Tren.numVert(),P3);

    tCoste d1=min(c1[destino],min(c1[destino+Bus.numVert()],c1[destino+Bus.numVert()+Tren.numVert()]));
    tCoste d2=min(c2[destino],min(c2[destino+Bus.numVert()],c2[destino+Bus.numVert()+Tren.numVert()]));
    tCoste d3=min(c3[destino],min(c3[destino+Bus.numVert()],c3[destino+Bus.numVert()+Tren.numVert()]));


    if(d1<d2)
    {
      if(d1<d3)
      {
        P=P1;
        return d1;
      }
      else
      {
        P=P3;
        return d3;
      }
    }
    else
    {
      if(d2<d3)
      {
        P=P2;
        return d2;
      }
      else
      {
        P=P3;
        return d3;
      }
    }







}


int main()
{

  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  string b="nf2.txt";
  string c="nf3.txt";

  GrafoP<int> Bus(a);
  GrafoP<int> Tren(b);
  GrafoP<int> Avion(c);

  vector<vertice> P;
  int trenbus=5;
  int avionbustren=10;
  vertice origen=0;
  vertice destino=3;

  int coste=tresmedios(Bus,Tren,Avion,origen,destino,trenbus,avionbustren,P);
  cout<<"El coste min es :"<<coste<<endl;
  cout<<"El camino es :"<<endl;

  for(int i=0;i<P.size();++i)
  {
    cout<<" "<<P[i];
  }

}
