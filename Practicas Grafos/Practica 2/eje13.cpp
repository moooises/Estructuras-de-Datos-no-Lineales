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
  //En este algoritmo solo devolvemos la posicion en el grafo Isla de la ciudad
  //Para poder trabajar con el archipielago
  typedef typename GrafoP<tCoste>::vertice vertice;

  vertice best=0;

  for(int i=1;i<C.size();++i)
  {
    if(coste(best,Isla)>coste(C[i],Isla))
    {
      best=i;
    }
  }

  return best;

}

template <typename tCoste>
GrafoP<tCoste> archipielago(const GrafoP<tCoste>& I1,const GrafoP<tCoste>& I2,const GrafoP<tCoste>& I3)
{

  //Creamos el archipielago en grafo
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

return t;
}

template <typename tCoste>
tCoste sumarmatrices(matriz<tCoste>& m,int N1,int N2,int N3)
{
  tCoste aux=0;

  for(int i=0;i<N1+N2+N3;++i)
  {
    for(int j=0;j<N1+N2+N3;++j)
    {
        aux=aux+m[i][j];
    }
  }

  return aux;
}

template <typename tCoste>
tCoste coste1(GrafoP<tCoste>& t,int N1,int N2,int N3,typename GrafoP<tCoste>::vertice b1,typename GrafoP<tCoste>::vertice b2,typename GrafoP<tCoste>::vertice b3)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
//Necesitamos crear un grafo para cada caso, no se me ocurria una forma sencilla de generalizarlo
  t[b1][N1+b2]=0;
  t[b1][N1+N2+b3]=0;
  t[N1+b2][b1]=0;
  t[N1+N2+b3][b1]=0;

  matriz<vertice> M;

  matriz<tCoste> m=Floyd(t,M);

  tCoste r=sumarmatrices(m,N1,N2,N3);
  return r;

}
template <typename tCoste>
tCoste coste2(GrafoP<tCoste>& t,int N1,int N2,int N3,typename GrafoP<tCoste>::vertice b1,typename GrafoP<tCoste>::vertice b2,typename GrafoP<tCoste>::vertice b3)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  t[N1+b2][b1]=0;
  t[N1+b2][N1+N2+b3]=0;
  t[b1][N1+b2]=0;
  t[N1+N2+b3][N1+b2]=0;

  matriz<vertice> M;

  matriz<tCoste> m=Floyd(t,M);

  tCoste r=sumarmatrices(m,N1,N2,N3);
  return r;

}

template <typename tCoste>
tCoste coste3(GrafoP<tCoste>& t,int N1,int N2,int N3,typename GrafoP<tCoste>::vertice b1,typename GrafoP<tCoste>::vertice b2,typename GrafoP<tCoste>::vertice b3)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  t[N1+N2+b3][b1]=0;
  t[N1+N2+b3][N1+b2]=0;
  t[b1][N1+N2+b3]=0;
  t[N1+b2][N1+N2+b3]=0;

  matriz<vertice> M;

  matriz<tCoste> m=Floyd(t,M);

  tCoste r=sumarmatrices(m,N1,N2,N3);
  return r;

}

template <typename tCoste>
vector<typename GrafoP<tCoste>::vertice> TresCiudades(const GrafoP<tCoste>& Isla1,const GrafoP<tCoste>& Isla2,const GrafoP<tCoste>& Isla3,const vector<typename GrafoP<tCoste>::vertice>& C1,const vector<typename GrafoP<tCoste>::vertice>& C2,const vector<typename GrafoP<tCoste>::vertice>& C3)
{
  typedef typename GrafoP<tCoste>::vertice vertice;

  vertice best1=bestcity(C1,Isla1);//Ahora devuelve la posicion, no el vertice
  vertice best2=bestcity(C2,Isla2);
  vertice best3=bestcity(C3,Isla3);

  vector<vertice> pares;

  GrafoP<tCoste> t=archipielago(Isla1,Isla2,Isla3);
//A diferencia del dos hay tres caminos posibles en lugar de alguno
//Isla 2<->Isla 1<->Isla 3
//Isla 1<->Isla 3<->Isla 2
//Isla 3<->Isla 2<->Isla 1
//Luego tenemos que tratar los tres casos
//Elligiremos el mejor a traves de la suma de los costes de la matriz reducidad(Floyd)

  tCoste c1=coste1(t,Isla1.numVert(),Isla2.numVert(),Isla3.numVert(),best1,best2,best3);
  tCoste c2=coste2(t,Isla1.numVert(),Isla2.numVert(),Isla3.numVert(),best1,best2,best3);
  tCoste c3=coste3(t,Isla1.numVert(),Isla2.numVert(),Isla3.numVert(),best1,best2,best3);

  cout<<c1<<endl;
  cout<<c2<<endl;
  cout<<c3<<endl;


  if(c1<c2)
  {
    if(c1<c3)
    {
      pares.push_back(C2[best2]);
      pares.push_back(C1[best1]);
      pares.push_back(C3[best3]);
      pares.push_back(2);//Estos tres valores es para que quede bonita la solucion en el main
      pares.push_back(1);
      pares.push_back(3);
      //best2->best1->best3
    }
    else
    {
      pares.push_back(C2[best2]);
      pares.push_back(C1[best1]);
      pares.push_back(C3[best3]);
      pares.push_back(2);//Estos tres valores es para que quede bonita la solucion en el main
      pares.push_back(3);
      pares.push_back(1);
      //best2->best3->best1
    }
  }
  else
  {
    pares.push_back(C2[best2]);
    pares.push_back(C1[best1]);
    pares.push_back(C3[best3]);
    pares.push_back(2);//Estos tres valores es para que quede bonita la solucion en el main
    pares.push_back(1);
    pares.push_back(3);
    //best2->best3->best1
  }

  return pares;
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

  vector<vertice> C1;
  vector<vertice> C2;
  vector<vertice> C3;

  C1.push_back(1);
  C1.push_back(2);
  C1.push_back(4);
  C2.push_back(2);
  C2.push_back(3);
  C3.push_back(1);
  C3.push_back(3);
  C3.push_back(4);

  vector<vertice> ciudades=TresCiudades(Isla1,Isla2,Isla3,C1,C2,C3);
  cout<<endl;
  cout<<"Losp Puentes se contruyen en: "<<endl;
  int tam=ciudades.size()/2;
  for(int i=0;i<tam;++i)
  {
    if(i!=0)cout<<"con";

    cout<<" Ciudad "<<ciudades[i];
    if(ciudades[i+tam]==1)
    {
      cout<<" de la Isla 1 ";
    }
    else
    {
      if(ciudades[i+tam]==2)
      {
        cout<<" de la Isla 2 ";
      }
      else
      {
        cout<<" de la Isla 3 ";
      }
    }
  }
  cout<<endl;

}
