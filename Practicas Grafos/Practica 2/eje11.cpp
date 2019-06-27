#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <typename tCoste>
GrafoP<tCoste> islas(const GrafoP<tCoste>& I1,const GrafoP<tCoste>& I2,const GrafoP<tCoste>& I3,vector<typename GrafoP<tCoste>::vertice>& P1,  vector<typename GrafoP<tCoste>::vertice>& P2)
{

  typedef typename GrafoP<tCoste>::vertice vertice;

  GrafoP<tCoste> t(I1.numVert()+I2.numVert()+I3.numVert());

  for(int i=0;i<I1.numVert();++i)
  {
    for(int j=0;j<I1.numVert();++j)
    {
      t[i][j]=I1[i][j];
    }
  }

  for(int i=I1.numVert();i<I1.numVert()+I2.numVert();++i)
  {
    for(int j=I1.numVert();j<I1.numVert()+I2.numVert();++j)
    {
      t[i][j]=I2[i-I1.numVert()][j-I1.numVert()];
    }
  }

  for(int i=I1.numVert()+I2.numVert();i<I1.numVert()+I2.numVert()+I3.numVert();++i)
  {
    for(int j=I1.numVert()+I2.numVert();j<I1.numVert()+I2.numVert()+I3.numVert();++j)
    {
      t[i][j]=I3[i-(I1.numVert()+I2.numVert())][j-(I1.numVert()+I2.numVert())];
    }
  }

cout<<t<<endl;

cout<<endl;
for(int i=0;i<P1.size();++i)
{
  cout<<"P1: "<<P1[i]<<" P2: "<<P2[i]<<endl;
  t[P1[i]][P2[i]]=0;
  t[P2[i]][P1[i]]=0;
}
cout<<t<<endl;

vector<vertice> P8;
vector<tCoste> coste=Dijkstra(t,1,P8);

for(int i=0;i<coste.size();++i)
{
  cout<<" "<<coste[i];
}
cout<<endl;
matriz<vertice> P;
int r=I1.numVert()+I2.numVert()+I3.numVert();

matriz<tCoste> C=Floyd(t,P);
for(int i=0;i<r;++i)
{
  for(int j=0;j<r;++j)
  {
    if(C[i][j]==4294967295) t[i][j]==GrafoP<tCoste>::INFINITO;
    else t[i][j]=C[i][j];
  }
}
return t;
  }


int main()
{

  typedef typename GrafoP<int>::vertice vertice;

  string a="nf.txt";
  string b="nf2.txt";
  string c="nf3.txt";

  GrafoP<int> Isla1(a);
  GrafoP<int> Isla2(b);
  GrafoP<int> Isla3(c);
  //Estos grafos son del mismo tamaño pero no tienen porque, ten eso en cuenta

  vector<vertice> P1;
  vector<vertice> P2;
  //Vamos a hacer dos vectores para indicar las ciudades conectadas
  //No me apetece hacer un struct
  //P1[1] esta conectado con P2[1]]

  P1.push_back(1);
  P2.push_back(Isla1.numVert()+Isla2.numVert()-2);
  P1.push_back(Isla1.numVert()+Isla2.numVert()-3);
  P2.push_back(Isla1.numVert()+Isla2.numVert()+Isla3.numVert()-3);
  P1.push_back(2);
  P2.push_back(Isla1.numVert()+Isla2.numVert()+Isla3.numVert()-1);


  GrafoP<int> coste=islas(Isla1,Isla2,Isla3,P1,P2);
  int r=Isla1.numVert()+Isla2.numVert()+Isla3.numVert();

  cout<<coste<<endl;

}
