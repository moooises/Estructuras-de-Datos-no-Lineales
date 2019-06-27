#include "alg_grafoPMC.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "particion.cpp"
using namespace std;

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

template<typename tCoste>
void marcarinfinito( GrafoP<tCoste>& g)
{
  for(int i=0;i<g.numVert();++i)
  {
    for(int j=0;j<g.numVert();++j)
    {
        if(g[i][j]<0)g[i][j]= GrafoP<tCoste>::INFINITO;
    }
  }
}
template<typename tCoste>
matriz<bool> marcarcarreteras( GrafoP<tCoste>& g)
{
  matriz<bool> b(g.numVert());
  for(int i=0;i<g.numVert();++i)
  {
    for(int j=0;j<g.numVert();++j)
    {
        if(g[i][j]<=0)b[i][j]=false;
        else b[i][j]=true;
    }
  }
  return b;
}

template <typename tCoste>
Particion Tombuctu(matriz<bool> m,vector<coordenada> C,GrafoP<tCoste>& G)
{
  typedef typename GrafoP<tCoste>::vertice vertice;


  coordenada c1;
  tCoste nIslas=C.size();
  Particion P(C.size());
  for(int i=0;i<C.size();++i)
  {
    c1=C[i];
    for(int j=i+1;j<C.size();++j)
    {

        if(m[i][j] && (P.encontrar(i)!=P.encontrar(j)))
        {
              P.unir(P.encontrar(i),P.encontrar(j));
              --nIslas;
        }

    }
  }
  cout<<"Hay "<<nIslas<<" islas"<<endl;

/**
    for(int i=0;i<C.size();++i)
    {
      cout<<" "<<P.encontrar(i);
    }

  cout<<endl;
*/
  int representante1,representante2;

  for(int i=0;i<C.size();++i)
  {
    representante1=P.encontrar(C[i].x);
    for(int j=0;j<C.size();++j)
    {
      representante2=P.encontrar(C[j].x);
      if(i==j)
      {
        G[i][j]=0;
      }
      else
      {
        if(representante1==representante2)
        {
          G[i][j]=distancia(C[i].x,C[i].y,C[j].x,C[j].y);
        }
        else
        {
          G[i][j]=GrafoP<tCoste>::INFINITO;
        }
      }
    }
  }

return P;

}

int main()
{
  string a="nf2.txt";//No me funciona el infinito
  GrafoP<int> g(a);
  GrafoP<int> G(g.numVert());
  matriz<bool>m= marcarcarreteras(g);

/**
  for(int i=0;i<m.dimension();++i)
  {
    cout<<endl;
    for(int j=0;j<m.dimension();++j)
    {
      cout<<m[i][j];
    }
  }

  cout<<g.numVert()<<endl;
  */
  vector<coordenada> coordenadas;
  coordenadas.push_back(coordenada(0,0));//hay cuatro ciudedes
  coordenadas.push_back(coordenada(1,1));
  coordenadas.push_back(coordenada(2,2));
  coordenadas.push_back(coordenada(3,3));
  coordenadas.push_back(coordenada(4,4));


  Particion P=Tombuctu(m,coordenadas,G);
  cout<<G<<endl;


}
