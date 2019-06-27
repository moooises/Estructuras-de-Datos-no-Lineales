//El problema te exige que reconstruyas el archipielago primero, pero si no te lo pidiera
//podrias hacerlo como cualquiera de la practica 7, es decir,sin Kruskall

#include "alg_grafoPMC.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "particion.cpp"
using namespace std;

typedef typename GrafoP<size_t>::vertice vertice;

struct coordenada
{
  int x;
  int y;
  coordenada(int x_=0,int y_=0):x(x_),y(y_){}
};

int distancia(int x1,int y1,int x2,int y2)
{
  return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

int mejorpuente(vector<coordenada> c1,vector<coordenada> c2,vector<coordenada>& puente)
{
  coordenada cor1,cor2;
  coordenada min1,min2;
  int dist;
  int dist_min=GrafoP<int>::INFINITO;
  for(int i=0;i<c1.size();++i)
  {
    cor1=c1[i];
    for(int j=0;j<c2.size();++j)//la dist de A a B es la misma que de B a A
    {
      cor2=c2[j];
      dist=distancia(cor1.x,cor1.y,cor2.x,cor2.y);
      if(dist_min>dist)
      {
        dist_min=dist;
        min1.x=cor1.x;
        min1.y=cor1.y;

        min2.x=cor2.x;
        min2.y=cor2.y;

      }
    }
  }
  puente.push_back(min1);
  puente.push_back(min2);

  return dist_min;
}
template<typename tCoste>
GrafoP<tCoste> supergrafo(const GrafoP<tCoste>& Fobos,const GrafoP<tCoste>& Deimos)
{
  GrafoP<tCoste> G(Fobos.numVert()+Deimos.numVert());
  cout<<Fobos.numVert()<<endl;
  cout<<Deimos.numVert()<<endl;

  for(int i=0;i<Fobos.numVert();++i)
  {
    for(int j=0;j<Fobos.numVert();++j)
    {
    //  cout<<i<<endl;
      //cout<<j<<endl;
      G[i][j]=Fobos[i][j];
    }
  }

  for(int i=0;i<Deimos.numVert();++i)
  {
    for(int j=0;j<Deimos.numVert();++j)
    {
      //cout<<i<<endl;
      //cout<<j<<endl;
      G[Fobos.numVert()+i][Fobos.numVert()+j]=Deimos[i][j];
    }
  }
  return G;
}


template <typename tCoste>
tCoste viajar(GrafoP<tCoste>& Fobos,GrafoP<tCoste>& Deimos,GrafoP<tCoste>& G,vector<coordenada>& CFobos,vector<coordenada>& CDeimos,vector<coordenada>& CFobosCost,vector<coordenada>& CDeimosCost,coordenada origen,coordenada destino)
{
  coordenada c1,c2;
  for(int i=0;i<CFobos.size();++i)
  {
    c1=CFobos[i];
    for(int j=0;j<CFobos.size();++j)
    {
      if(i==j)
      {
        Fobos[i][j]=0;
      }
      else
      {
      c2=CFobos[j];
      Fobos[i][j]=distancia(c1.x,c1.y,c2.x,c2.y);
      }
    }
  }

  for(int i=0;i<CDeimos.size();++i)
  {
    c1=CDeimos[i];
    for(int j=0;j<CDeimos.size();++j)
    {
      if(i==j)
      {
        Deimos[i][j]=0;
      }
      else
      {
      c2=CDeimos[j];
      Deimos[i][j]=distancia(c1.x,c1.y,c2.x,c2.y);
      }
    }
  }

  Fobos=Kruskall(Fobos);
  Deimos=Kruskall(Deimos);
  cout<<Fobos<<endl;
  cout<<Deimos<<endl;
  //Con esto ya tenemos la distribucion de las nIslas
  //Ahora donde poner el puente, que debe ser uno

  vector<coordenada> puente;
  tCoste coste=mejorpuente(CFobosCost,CDeimosCost,puente);

  G=supergrafo(Fobos,Deimos);

  G[puente[0].x][puente[1].y]=coste;
  G[puente[1].x][puente[0].y]=coste;
  cout<<G<<endl;

  vector<vertice> P;
  vector<tCoste> D=Dijkstra(G,origen.x,P);

  return D[destino.x];

}

int main()
{

int N1=5;
int N2=6;
GrafoP<int> Fobos(N1);
GrafoP<int> Deimos(N2);
GrafoP<int> Grecoland(N1+N2);
vector<coordenada> CFobos;
vector<coordenada> CDeimos;
vector<coordenada> CFobosCost;
vector<coordenada> CDeimosCost;

CFobos.push_back(coordenada(0,0));
CFobos.push_back(coordenada(1,1));
CFobos.push_back(coordenada(2,2));
CFobos.push_back(coordenada(3,3));
CFobos.push_back(coordenada(4,4));

CDeimos.push_back(coordenada(5,5));
CDeimos.push_back(coordenada(6,6));
CDeimos.push_back(coordenada(7,7));
CDeimos.push_back(coordenada(8,8));
CDeimos.push_back(coordenada(9,9));
CDeimos.push_back(coordenada(10,10));

CFobosCost.push_back(coordenada(0,0));
CFobosCost.push_back(coordenada(2,2));

CDeimosCost.push_back(coordenada(5,5));
CDeimosCost.push_back(coordenada(7,7));
CDeimosCost.push_back(coordenada(9,9));

coordenada origen(CFobos[0]);
coordenada destino(CDeimos[N2-1]);

int coste=viajar(Fobos,Deimos,Grecoland,CFobos,CDeimos,CFobosCost,CDeimosCost,origen,destino);

cout<<"El coste de "<<origen.x<<" de Fobos a ciudad "<<destino.x<<" de Deimos es "<<coste;






}
