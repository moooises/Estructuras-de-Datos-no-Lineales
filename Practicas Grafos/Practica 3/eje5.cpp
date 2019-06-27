#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "particion.cpp"
using namespace std;

int main()
{
  string a="nf.txt";//No me funciona el infinito
  GrafoP<int> g(a);
  cout<<g<<endl;
  GrafoP<int> G=Kruskall(g);
  cout<<G<<endl;
  int fibra=0;
  for(int i=0;i<G.numVert();++i)
  {
    for(int j=i;j<G.numVert();++j)//IMPORTANTE
    {
      if(G[i][j]!=GrafoP<int>::INFINITO)fibra=G[i][j]+fibra;
    }
  }
  cout<<"La longituda de la fibra debe ser: "<<fibra<<endl;
}
