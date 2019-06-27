#include "alg_grafoPMC.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "particion.cpp"
using namespace std;
template <typename tCoste>
GrafoP<tCoste> EMASAJER( const GrafoP<tCoste>& distancias, const GrafoP<tCoste>& caudal,tCoste subvencion,tCoste coste,matriz<tCoste>& distancia)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  GrafoP<tCoste> canal(distancias.numVert());
  matriz<vertice> M;
  distancia=Floyd(distancias,M);//debemos minimazar las distancias primero

  for(int i=0;i<canal.numVert();++i)
  {
    for(int j=0;j<canal.numVert();++j)
    {
      canal[i][j]=(distancia[i][j]*coste)-(caudal[i][j]*subvencion);

    }
  }



  GrafoP<tCoste> K= Kruskall(canal);
  return K;
}

int main()
{
  string a="nf.txt";
  string b="nf2.txt";
GrafoP<int> distancia(a);
GrafoP<int> caudal(b);
cout<<caudal<<endl;

int subvencion=2;
int costekm=5;
matriz<int> distancias;
GrafoP<int> canal=EMASAJER(distancia,caudal,subvencion,costekm,distancias);
//cout<<canal<<endl;

for(int i=0;i<canal.numVert();++i)
{
  for(int j=0;j<canal.numVert();++j)
  {
    if(canal[i][j]!=GrafoP<int>::INFINITO){
      cout<<"Canal de ciudad "<<i<<" con canal ciudad "<<j<<" de distancia "<<canal[i][j]<<" con caudal "<<caudal[i][j]<<" y con coste "<<canal[i][j]<<endl;
    }
  }
}

}
