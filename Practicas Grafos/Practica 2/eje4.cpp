#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <typename tCoste>
int cementos(const GrafoP<tCoste> G,typename GrafoP<tCoste>::vertice capital,vector<tCoste>& parte_diario)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  matriz<vertice> P(G.numVert());
  matriz<int> M=Floyd(G,P);//Mejor hacerlo con dijkstra y dijkstra inverso

  for(int i=0;i<G.numVert();++i)
  {
    for(int j=0;j<G.numVert();++j)
    {
      cout<<" "<<M[i][j];
    }
    cout<<endl;
  }

  tCoste coste=0;
  int j=0;//esto nos indica la posicion en el parte de trabajo
  for(vertice i=0;i<G.numVert();++i)
  {
    if(i!=capital)
    {
      cout<<M[capital][i]+M[i][capital]<<"*"<<parte_diario[j]<<endl;

      coste=coste+(M[capital][i]+M[i][capital])*parte_diario[j];
      j++;
    }
  }

  return coste;
}

int main()
{
  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  GrafoP<int> G(a);
  vertice capital=3;
  vector<int> parte_diario;
  parte_diario.push_back(4);//ciudad 0
  parte_diario.push_back(3);//ciudad 1
  parte_diario.push_back(5);//ciudad 2
  parte_diario.push_back(7);//ciudad 4

  //Se llama a esta funcion por cada parte
  int coste=cementos(G,capital,parte_diario);
  cout<<"Kilometros recorridos: "<<coste<<endl;
}
