#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>
#include <cmath>
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

vector<coordenada> Tombuctu2(matriz<bool>& m,vector<coordenada> C)
{

  coordenada c1;
  int nIslas=m.dimension();
  Particion P(m.dimension());
  for(int i=0;i<m.dimension();++i)
  {

    for(int j=i+1;j<m.dimension();++j)
    {
        if(m[i][j] && (P.encontrar(i)!=P.encontrar(j)))
        {
              P.unir(P.encontrar(i),P.encontrar(j));
              --nIslas;
        }

    }
  }

/**
  for(int i=0;i<C.size();++i)
  {
    cout<<" "<<P.encontrar(i);
  }

cout<<endl;
*/

  int dist_min;
  vector<coordenada> v;
  GrafoP<size_t> aviones(m.dimension());
  coordenada c2;

  int minx=0;
  int miny=0;
  int representante=P.encontrar(0);
  int min=GrafoP<int>::INFINITO;
  for(int i=0;i<C.size();++i)
  {
    c1=C[i];
    if(representante!=P.encontrar(i))
    {
      min=GrafoP<int>::INFINITO;
      v.push_back(coordenada(minx,miny));
    }
    for(int j=0;j<C.size();++j)
    {
      //cout<<"Repre: "<<P.encontrar(i)<<" "<<P.encontrar(j)<<endl;
      if(P.encontrar(i)!=P.encontrar(j))
      {
        //cout<<"i: "<<i<<" j:"<<j<<endl;

          c2=C[j];
          int dist=distancia(c1.x,c1.y,c2.x,c2.y);
          cout<<dist<<endl;
          dist_min=GrafoP<int>::INFINITO;

          if(dist_min>dist)
          {

            aviones[i][j]=dist;
            if(min>dist)
            {
              min=dist;
              minx=i;
              miny=j;
            }

          }
      }
    }

  }

  cout<<aviones<<endl;



  return v;
}

int main()
{
  string a="nf2.txt";//No me funciona el infinito
  GrafoP<int> g(a);
  //GrafoP<int> G(g.numVert());
  matriz<bool>m= marcarcarreteras(g);
  marcarinfinito(g);
  cout<<g;
/**
  for(int i=0;i<m.dimension();++i)
  {
    cout<<endl;
    for(int j=0;j<m.dimension();++j)
    {
      cout<<m[i][j];
    }
  }
*/
  cout<<g.numVert()<<endl;
  vector<coordenada> coordenadas;
  coordenadas.push_back(coordenada(0,0));//hay cuatro ciudedes
  coordenadas.push_back(coordenada(1,1));
  coordenadas.push_back(coordenada(2,2));
  coordenadas.push_back(coordenada(3,3));


  //Particion P(g.numVert());

  vector<coordenada> v=Tombuctu2(m,coordenadas);
  cout<<"Las lineas aereas se colocarian en:"<<endl;
  for(int i=0;i<v.size();++i)
  {
    cout<<"X: "<<v[i].x<<" Y: "<<v[i].y<<endl;
  }

}
