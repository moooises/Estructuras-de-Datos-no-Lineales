#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>
using namespace std;

template <typename tCoste>
matriz<tCoste> FloydInverso(const GrafoP<tCoste>& G,matriz<typename GrafoP<tCoste>::vertice>& P)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t n = G.numVert();
  matriz<tCoste> A(n);   // matriz de costes mínimos

  // Iniciar A y P con caminos directos entre cada par de vértices.
  P = matriz<vertice>(n);
  for (vertice i = 0; i < n; i++) {
     A[i] = G[i];                    // copia costes del grafo
   //  A[i][i] = 0;                    // diagonal a 0
     A[i][i]=-GrafoP<tCoste>::INFINITO;         //diagonal a INFINITO
     P[i] = vector<vertice>(n, i);   // caminos directos
  }
  // Calcular costes mínimos y caminos correspondientes
  // entre cualquier par de vértices i, j
  for (vertice k = 0; k < n; k++)
     for (vertice i = 0; i < n; i++)
        for (vertice j = 0; j < n; j++) {
           tCoste ikj = suma(A[i][k], A[k][j]);
           if (ikj > A[i][j]) {
              A[i][j] = ikj;
              P[i][j] = k;
           }
        }
  return A;
}

template <typename tCoste>
bool visitados(vector<tCoste>& v, tCoste i)
{
  typename vector<tCoste>::iterator f;
  f=find (v.begin(), v.end(), i);
  if(f!=v.end())return true;
  else return false;
}

template <typename tCoste>
tCoste elviajemascaro(const GrafoP<tCoste>& G,typename GrafoP<tCoste>::vertice& origen,typename GrafoP<tCoste>::vertice& destino)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  matriz<vertice> P(G.numVert());
  matriz<int> M=FloydInverso(G,P);//Debemos maximizar los costes del viaje, haciendo lo opuesto a floyd

  for(int i=0;i<G.numVert();++i)
  {
    for(int j=0;j<G.numVert();++j)
    {
      cout<<" "<<M[i][j];
    }
    cout<<endl;
  }

  vector<tCoste> visita;
  tCoste max=0;
  tCoste v;
  tCoste coste=0;
  for(tCoste r=0;r<G.numVert();++r)
  {
    for(tCoste i=0;i<G.numVert();++i)
    {
      if(!visitados(visita,i))
      {
        for(tCoste j=0;j<G.numVert();++j)
        {
          if(M[i][j]>max)
          {
            max=M[i][j];
            v=i;
          }
        }
      }
    }
    coste=coste+max;
    max=0;
    visita.push_back(v);
  }
  origen=visita[0];
  destino=visita[G.numVert()-1];
  return coste;

}

int main()
{
typedef typename GrafoP<int>::vertice vertice;

string a="nf.txt";
GrafoP<int> G(a);
vertice origen;
vertice destino;

int coste=elviajemascaro(G,origen,destino);
cout<<"Coste: "<<coste<<endl;
cout<<"Origen: "<<origen<<endl;
cout<<"Destino: "<<destino<<endl;
}
