#include "alg_grafoPMC.h"
#include <iostream>

using namespace std;
//typedef typename GrafoP<int>::vertice vertice;

template <typename tCoste>
bool aciclico(const GrafoP<tCoste>& H)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  //Es necesario hacer floyd7
  matriz<vertice> P(H.numVert());

  matriz<tCoste> G=Floyd(H,P);

  for(vertice i=0;i<H.numVert();++i)
  {
    if(G[i][i]!=GrafoP<tCoste>::INFINITO)return false;
    //cout<<G[i][i]<<endl;

  }
  return true;
}

int main()
{

  string a="nf.txt";
  GrafoP<int> G(a);
  int n=G.numVert();
  cout<<G;
  if(aciclico(G))cout<<"El grafo es aciclico"<<endl;
  else cout<<"El grafo no es aciclico"<<endl;


}
