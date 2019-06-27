#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

#include "ABB.h"

template <typename T>
void mostrarhijosderch(const Abb<T>& A,T t);

template <typename T>
void mostrarhijosizq(const Abb<T>& A,T t);

using namespace std;

template <typename T>
void rellenar(Abb<T>& A){
  for(int i=10;i<=20;++i)
  {
    A.insertar(i);
  }
  for(int i=0;i<10;++i)
  {
    A.insertar(i);
  }
}

template <typename T>
void mostrarhijosizq(const Abb<T>& A,T t)
{
  if(!A.vacio())
  {
    cout<<"Hijo izquierdo de "<<t<<": "<<A.elemento()<<endl;
    mostrarhijosizq(A.izqdo(),A.elemento());
    mostrarhijosderch(A.drcho(),A.elemento());
  }
}

template <typename T>
void mostrarhijosderch(const Abb<T>& A,T t)
{
  if(!A.vacio())
  {
    cout<<"Hijo derecho de "<<t<<": "<<A.elemento()<<endl;
    mostrarhijosizq(A.izqdo(),A.elemento());
    mostrarhijosderch(A.drcho(),A.elemento());
  }
}

template <typename T>
void mostrar(const Abb<T>& A)
{
  cout<<"Raiz del Arbol: "<<A.elemento()<<endl;
  mostrarhijosizq(A.izqdo(),A.elemento());
  mostrarhijosderch(A.drcho(),A.elemento());
}

template <typename T>
void inorden(vector<T>& v,const Abb<T>& A)//lo puedes hacer en preorden y te ahorras el sort
{
  if(!A.vacio())
  {
  v.push_back(A.elemento());
  inorden(v,A.izqdo());
  inorden(v,A.drcho());
  }
}


template <typename T>
void equilibrar(Abb<T>& B,vector<T>& v,int ini,int fin)
{
  if(ini!=fin)
  {
      int pos=ini+((fin-ini)/2);
      B.insertar(v[pos]);
      equilibrar(B,v,ini,pos);
      equilibrar(B,v,pos+1,fin);

  }

}


template <typename T>
Abb<T> AVL(Abb<T> A){
  vector<T> v;
  inorden(v,A);
  sort(v.begin(),v.end());
  Abb<T> B;
  int n;
  n=v.size();
  equilibrar(B,v,0,n);
  return B;
}


int main(){
  Abb<int> A;
  rellenar(A);
  mostrar(A);
  cout<<endl;
  //cout<<11/2<<endl;=5
  A=AVL(A);
  mostrar(A);
}
