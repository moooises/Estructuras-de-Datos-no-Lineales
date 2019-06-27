#include "alg_grafoPMC.h"
#include <iostream>

using namespace std;
typedef typename GrafoP<int>::vertice vertice;

template <typename tCoste>
void Zuelandia(GrafoP<tCoste>& G, vector<vertice> ciudades,matriz<bool> carreteras,vertice capital)
{
  //NOTA size_t==Vertice
  //Cortamos las carreteras a las ciudades
  //es decir, poner las columnas a infinito
  for(size_t i=0;i<ciudades.size();++i)
  {
    vertice aux=ciudades[i];
    for(vertice j=0;j<G.numVert();++j)
    {
      G[j][aux]=GrafoP<tCoste>::INFINITO;
      G[aux][j]=GrafoP<tCoste>::INFINITO;
    }
  }

  //Ahora cortamos las carreteras
  //es decir donde carreteras sea falso G es INFINITO
  for(size_t i=0;i<carreteras.dimension();++i)
  {
    for(size_t j=0;j<carreteras.dimension();++j)
    {
      if(carreteras[i][j]==false)G[i][j]=GrafoP<tCoste>::INFINITO;
    }
  }

  vector<vertice> P;

  vector<tCoste> alacapital;
  alacapital=DijkstraInv(G,capital,P);

  vector<tCoste> delacapital;
  delacapital=Dijkstra(G,capital,P);

  for(size_t i=0;i<G.numVert();++i)
  {
    for(size_t j=0;j<G.numVert();++j)
    {
      G[i][j]=suma(alacapital[i],delacapital[j]);
    }
  }

}

int main()
{

  string a="nf.txt";
  GrafoP<int> G(a);
  cout<<G<<endl;
  bool x=true;
  size_t n=G.numVert();
  matriz<bool> h(n,x);//matriz de carreteras
  vector<vertice> c={1};//ciudades tomadas por los rebeldes
  vertice capital=0;//capital de Zuelandia
  h[3][4]=false;
  h[2][1]=false;
  h[0][1]=false;
  h[1][3]=false;
  h[0][4]=false;
  Zuelandia(G,c,h,capital);
  cout<<G<<endl;
}
