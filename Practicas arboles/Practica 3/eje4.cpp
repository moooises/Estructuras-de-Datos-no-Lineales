//MEJORARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
#include <iostream>
#include <fstream>
#include <algorithm>
#include "agen.h"
#include "agen_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin='#';

template <typename T>
void eliminar_ramas(Agen<T>& A,typename Agen<T>::nodo n)
{

  if(A.hermDrcho(n)!=Agen<T>::NODO_NULO)
  {
    eliminar_ramas(A,A.hermDrcho(n));
    A.eliminarHermDrcho(n);
  }

  if(A.hijoIzqdo(n)!=Agen<T>::NODO_NULO)
  {
    eliminar_ramas(A,A.hijoIzqdo(n));
    A.eliminarHijoIzqdo(n);
  }

}


template <typename T>
typename Agen<T>::nodo buscar(const Agen<T>& A,typename Agen<T>::nodo n,T t)
{

  if(n==Agen<T>::NODO_NULO)return Agen<T>::NODO_NULO;
  else
  {
    if(A.elemento(n)==t)return n;
    else
    {
      typename Agen<T>::nodo m;
      n=A.hijoIzqdo(n);
      while(n!=Agen<T>::NODO_NULO || A.elemento(m)!=t)
      {
        m=buscar(A.A.hijoIzqdo(n));
        n=A.hermDrcho(n);
      }
      return m;
    }
  }
}

template <typename T>
void podar(Agen<T>& A,T t)//La poda elimina el propio nodo tb
{
  typename Agen<T>::nodo n=buscar(A,A.raiz(),t);
  if(n!=Agen<T>::NODO_NULO)
  {
    if(A.padre(n)!=Agen<T>::NODO_NULO)
    {
      eliminar_ramas(A,A.hijoIzqdo(n));
      A.eliminarHijoIzqdo(n);
      n=A.padre(n);
      A.eliminarHijoIzqdo(n);

    }
  else
    {
      A.eliminarRaiz();
    }
  }
  else
  {
    cout<<"Elemento "<<t<<" no encontrado"<<endl;
  }
}

int main(){
  Agen<tElto> A;
/**
  cout<<"*** Lectura del arbol A***\n";
  rellenarAgen(A,fin);

  ofstream fs("agen.dat");
  imprimirAgen(fs,A,fin);
  fs.close();
  cout<<"\n*** Arbol A guardado en fichero age.dat***\n";
*/
  cout<<"\n*** Lectura de arbol A de agen.dat ***\n";
  ifstream fe("agen.dat");
  rellenarAgen(fe,A);
  fe.close();

  cout<<"\n *** Mostrar arbol***\n";
  imprimirAgen(A);

  podar(A,'g');

  cout<<"\n*** Lectura de arbol A despues de la poda ***\n";
  imprimirAgen(A);

}
