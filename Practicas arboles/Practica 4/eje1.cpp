#include <iostream>
#include <algorithm>
#include <fstream>

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
void eliminar(Abb<T>& A,int e)
{
  Abb<T> B=A.buscar(e);
  int aux;
  while(!B.vacio())
  {
    aux=B.elemento();
    B.eliminar(aux);
    A.eliminar(aux);
  }
}

int main(){
  Abb<int> A;
  rellenar(A);
  mostrar(A);
  cout<<endl;
  eliminar(A,11);
  mostrar(A);
}
