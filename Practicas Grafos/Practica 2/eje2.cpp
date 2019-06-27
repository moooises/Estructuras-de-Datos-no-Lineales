#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>
#include <stdlib.h>


using namespace std;

typedef typename GrafoP<size_t>::vertice vertice;

struct casilla
{
  int x;
  int y;
  casilla(vertice cc1=0,vertice cc2=0):x(cc1),y(cc2){}
  bool operator ==(casilla b){return (this->x == b.x) && (this->y == b.y);  }

};

struct pared
{
  int p1;//Estos dos deberian ser casillas
  int p2;
  pared(int c1=0,int c2=0):p1(c1),p2(c2){}

};

vertice CasillaVertice(casilla a,int N)
{
  return  a.x*N+a.y;
}

casilla VerticeCasilla(int v,int N)
{
  casilla c(v/N,v%N);
  return c;

}

bool juntas( int x, int y,int N)
{
  casilla uno, dos;

  uno = VerticeCasilla(x,N);
  dos = VerticeCasilla(y,N);

  int xx=abs(uno.x-dos.x);
  int yx=abs(uno.y-dos.y);
  //cout<<"suma: "<<xx+yx<<endl;

    return  ((xx+yx)==1);
}

bool haypared(casilla c1,casilla c2,vector<pared> paredes,int N)
{
  pared aux;
  vertice aux1,aux2;
  vertice paux1,paux2;
  for(int i=0;i<paredes.size();++i)
  {
    aux=paredes[i];
    aux1=CasillaVertice(c1,N);
    aux2=CasillaVertice(c2,N);
    paux1=aux.p1;//Usa aqui CasillaVertice
    paux2=aux.p2;
    cout<<"C1: "<<aux1<<" C2: "<<aux2<<" P1: "<<paux1<<" P2: "<<paux2<<endl;
    if(((paux1==aux1) && (paux2==aux2)) || ((paux1==aux2) && (paux2==aux1))) return true;


  }

  return false;
}

typename GrafoP<size_t>::tCamino laberinto(GrafoP<size_t>& lab,int N,casilla origen,casilla destino,vector<pared>& paredes)
{
  casilla c1,c2;
  int i=0;
  int j=0;

for( i=0;i<lab.numVert();i++)//N*N
{
  c1=VerticeCasilla(i,N);
  for( j=0;j<lab.numVert();j++)
  {
    c2=VerticeCasilla(j,N);
    if(i==j){
      lab[i][j]=0;

    }
    else
    {
    if(juntas(i,j,N))
    {
      //cout<<"i: "<<i<<" j: "<<j<<endl;

        if(haypared(c1,c2,paredes,N))
        {
          cout<<"Dentro"<<endl;

          lab[i][j]=0;
        }
        else
        {
          lab[i][j]=1;
        }

    }
    else
    {
       lab[i][j]=GrafoP<size_t>::INFINITO;
    }
  }
  }
}
cout<<lab<<endl;
vector<vertice> P;
vector<size_t> c=Dijkstra(lab,CasillaVertice(origen,N),P);

typename GrafoP<size_t>::tCamino camin=camino<size_t>(CasillaVertice(origen,N),CasillaVertice(destino,N),P);

  return camin;
}


int main()
{
  int N=4;
  GrafoP<size_t> lab(N*N);

  vector<pared> paredes;
  paredes.push_back(pared(0,4));
  paredes.push_back(pared(6,7));
  paredes.push_back(pared(11,15));


  casilla origen(0,0);
  casilla destino(3,3);

  typename GrafoP<size_t>::tCamino camino=laberinto(lab,N,origen,destino,paredes);

  typename GrafoP<size_t>::tCamino::posicion p=camino.primera();

  cout<<"El camino es: "<<endl;
  while(p!=camino.fin())
  {
    cout<<" "<<camino.elemento(p);
    p=camino.siguiente(p);
  }

  }
