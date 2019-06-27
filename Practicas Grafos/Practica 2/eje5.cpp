#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <typename tCoste>
vector<bool> viaje(const GrafoP<tCoste>& G,const GrafoP<tCoste>& F,typename GrafoP<tCoste>::vertice origen, int dinero)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  vector<vertice> P;
  vector<bool> ciudades(G.numVert(),false);
  ciudades[origen]=true;
  tCoste m1,m2;
  tCoste pos1,pos2;
  bool aux;
  vector<tCoste> costeG;
  vector<tCoste> costeF;

  while(dinero>0)//en caso de que dinero=0
  {
    aux=true;
    for(tCoste i=0;i<ciudades.size();++i)
    {
      if(ciudades[i]==false)aux=false;
    }
    if(aux)return ciudades;//En casa de ya haya visitado todas las ciudades

    m1=GrafoP<tCoste>::INFINITO;
    m2=GrafoP<tCoste>::INFINITO;

    costeG=Dijkstra(G,origen,P);
    costeF=Dijkstra(F,origen,P);
    //Encontramos el minimo de cada grafo desde origen
    for(tCoste i=0;i<costeG.size();++i)
    {
    //  cout<<capacidad[i]<<" & "<<transporte[i]<<endl;
    //la ultima condicion del if es para no repetir ciudades
      if(m1>costeG[i] && costeG[i]!=0 && ciudades[i]!=true)//si es 0 es si mismo
      {
        m1=costeG[i];
        pos1=i;
      }
    }

    for(tCoste i=0;i<costeF.size();++i)
    {
    //  cout<<capacidad[i]<<" & "<<transporte[i]<<endl;
      if(m2>costeF[i] && costeF[i]!=0 && ciudades[i]!=true)
      {
        m2=costeF[i];
        pos2=i;
      }
    }

  //  cout<<m1<<" & "<<m2<<endl;
    if(m2>m1)
    {
      if((dinero-m1)<0)return ciudades;//En caso de que no tengamos suficiente dinero
      origen=pos1;
      ciudades[pos1]=true;
      dinero=dinero-m1;
    }
    else
    {
      if((dinero-m2)<0)return ciudades;
      origen=pos2;
      ciudades[pos2]=true;
      dinero=dinero-m2;
    }

  }
  return ciudades;//En caso de que tengamos el dinero exacto
}

int main()
{
  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  string b="nf2.txt";
  string c="nf3.txt";

  GrafoP<int> Carretera(a);
  GrafoP<int> Tren(b);
  GrafoP<int> Avion(c);
  vertice origen=1;
  int dinero=100;
  vector<bool> ciudades=viaje(Carretera,Tren,origen,dinero);
  for(int i=0;i<ciudades.size();++i)
  {
    cout<<" "<<ciudades[i];
  }
  cout<<endl;
}
