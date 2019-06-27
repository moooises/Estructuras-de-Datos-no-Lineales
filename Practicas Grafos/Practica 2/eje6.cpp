#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template<typename tCoste>
matriz<tCoste> agencia(const GrafoP<tCoste>& Tren,const GrafoP<tCoste>& Bus,typename GrafoP<tCoste>::vertice ciudad)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  matriz<vertice> P(Tren.numVert());
  matriz<tCoste> MT=Floyd(Tren,P);
  matriz<tCoste> MB=Floyd(Bus,P);
  matriz<tCoste> tarifa(Tren.numVert());
  tCoste aux1,aux2;

  for(tCoste i=0;i<Tren.numVert();++i)
  {
    for(tCoste j=0;j<Tren.numVert();++j)
    {
      if(i==j)tarifa[i][j]=0;
      else
      {
        aux1=min(MT[i][j],MB[i][j]);
        aux2=min(MT[i][ciudad]+MB[ciudad][j],MB[i][ciudad]+MT[ciudad][j]);
        tarifa[i][j]=min(aux1,aux2);
      }
    }
  }
  return tarifa;
}

int main()
{
  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  string b="nf2.txt";

  GrafoP<int> Tren(a);
  GrafoP<int> Bus(b);

  vertice ciudad=1;

  matriz<int> tarifa=agencia(Tren,Bus,ciudad);

  for(int i=0;i<Tren.numVert();++i)
  {
    for(int j=0;j<Tren.numVert();++j)
    {
      cout<<" "<<tarifa[i][j];
    }
    cout<<endl;
  }
}
