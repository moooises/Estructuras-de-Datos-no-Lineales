#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <typename tCoste>
tCoste coste(typename GrafoP<tCoste>::vertice C,const GrafoP<tCoste>& Isla)
{
  //La mejor ciudad sera a la que cueste menos ir

  typedef typename GrafoP<tCoste>::vertice vertice;

  vector<vertice> P;
  vector<tCoste> distancias=DijkstraInv(Isla,C,P);

  tCoste aux=0;
  for(int i=0;i<distancias.size();++i)
  {
    aux=aux+distancias[i];
  }
  return aux;
}

template <typename tCoste>
typename GrafoP<tCoste>::vertice bestcity(const vector<typename GrafoP<tCoste>::vertice>& C,const GrafoP<tCoste>& Isla)
{
  //devolvemos la ciudad con menor coste de viaje(Hacia ella)
  typedef typename GrafoP<tCoste>::vertice vertice;

  vertice best=C[0];

  for(int i=1;i<C.size();++i)
  {
    if(coste(best,Isla)>coste(C[i],Isla))
    {
      best=C[i];
    }
  }

  return best;

}

template <typename tCoste>
vector<typename GrafoP<tCoste>::vertice> dosciudades(const GrafoP<tCoste>& Fobos,const GrafoP<tCoste>& Deimos,const vector<typename GrafoP<tCoste>::vertice>& C1,const vector<typename GrafoP<tCoste>::vertice>& C2)
{
    //Como todos los caminos son igual de importantes, nos basta con elegir las ciudades con mejores conexiones de cada isla

    typedef typename GrafoP<tCoste>::vertice vertice;

    vertice best1=bestcity(C1,Fobos);
    vertice best2=bestcity(C2,Deimos);

    vector<vertice> mejores;
    mejores.push_back(best1);
    mejores.push_back(best2);

    return mejores;
}

int main()
{

  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  string b="nf2.txt";

  GrafoP<int> Fobos(a);
  GrafoP<int> Deimos(b);

  vector<vertice> C1;
  vector<vertice> C2;

  C1.push_back(1);
  C1.push_back(2);
  C1.push_back(4);
  C2.push_back(2);
  C2.push_back(3);

  vector<vertice> r=dosciudades(Fobos,Deimos,C1,C2);

  cout<<"Las mejores ciudades son: "<<endl;
  cout<<" Ciudad "<<r[0]<<" para Fobos"<<endl;
  cout<<" Ciudad "<<r[1]<<" Para Deimos"<<endl;

}
