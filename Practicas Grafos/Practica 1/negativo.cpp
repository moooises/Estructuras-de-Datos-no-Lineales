#include "alg_grafoPMC.h"
#include <iostream>
//no funciona con costes negativos
using namespace std;


int main()
{
  typedef typename GrafoP<int>::vertice vertice;

string a="negativo.txt";
GrafoP<int> G(a);

cout<<G<<endl;

vector<vertice> P;
vertice o=0;
vertice d=1;
vector<int> c=Dijkstra(G,o,P);
cout<<endl;
for(int i=0;i<c.size();++i)
{
  cout<<" "<<c[i];
}


cout<<endl;
for(int i=0;i<P.size();++i)
{
  cout<<" "<<P[i];
}
typename GrafoP<int>::tCamino cam=camino(o,d,P);

cout<<endl;
for(vertice i=0;i<P.size();++i)
{
  cout<<" "<<cam[i];
}

matriz<vertice> M;
matriz<int> f=Floyd(G,M);

for(int i=0;i<f.dimension();++i)
{
  cout<<endl;
  for(int j=0;j<f.dimension();++j)
  {
    cout<<" "<<f[i][j];
  }

}



}
