
#include "alg_grafoPMC.h"
#include <iostream>

using namespace std;

template <typename tCoste>
tCoste diametro(const GrafoP<tCoste>& G)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  matriz<vertice> P(G.numVert());
  matriz<tCoste> M=Floyd(G,P);
  cout<<endl;
  for(int i=0;i<G.numVert();++i)
  {
    for(int j=0;j<G.numVert();++j)
    {
      cout<<" "<<M[i][j];
    }
    cout<<endl;
  }
  cout<<"FLoyd"<<endl;
  //cout<<M;
  cout<<endl;
  tCoste minaux[2]={0,0};//Guardamos el menor en la poscion 1
  tCoste diametro=GrafoP<tCoste>::INFINITO;
  vertice pseudocentro;


  for(vertice i=0;i<G.numVert();++i)
  {
    for(vertice j=0;j<G.numVert();++j)
    {
      if(M[i][j]>=minaux[0])//Mayor o igual porque puede haber costes repetidos
      {
        minaux[1]=minaux[0];
        minaux[0]=M[i][j];
      }
      else
      {
        if(M[i][j]>=minaux[1])
        {
          minaux[1]=M[i][j];
        }
      }
    }
    if(diametro>minaux[0]+minaux[1])
    {
      diametro=minaux[0]+minaux[1];
      pseudocentro=i;
    }
    cout<<minaux[0]<<" "<<minaux[1]<<endl;

    minaux[0]=0;
    minaux[1]=0;
  }
  cout<<"Pseudocentro: Vertice "<<pseudocentro<<endl;
  return diametro;
}

int main()
{
  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  GrafoP<int> G(a);
  int n=G.numVert();
  cout<<G;

  cout<<"diametro: "<<diametro(G)<<endl;

}
