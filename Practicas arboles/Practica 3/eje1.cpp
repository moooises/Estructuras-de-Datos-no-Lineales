#include <iostream>
#include <fstream>
#include <algorithm>
#include "agen.h"
#include "agen_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin='#';

template <typename T>
int grado_rec(const Agen<T>& A, typename Agen<T>::nodo n)
{
  if(n==Agen<T>::NODO_NULO)return 0;
  else{
    int hijosnodoN=contarhijos(A,n);
    return max(grado_rec(A,A.hijoIzqdo(n)),max(hijosnodoN,grado_rec(A,A.hermDrcho(n))));
    }
  }

template <typename T>
int contarhijos(const Agen<T>& A, typename Agen<T>::nodo n){
  if(n==Agen<T>::NODO_NULO)return 0;
  else{

  int aux=0;
  n=A.hijoIzqdo(n);


  while(n!=Agen<T>::NODO_NULO)
  {
    aux++;
    n=A.hermDrcho(n);
  }
  cout<<aux<<endl;
  return aux;
  }
}

template <typename T>
int grado(const Agen<T>& A)
{
grado_rec(A,A.raiz());
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

  cout<<"El grado del arbol es: "<<grado(A)<<endl;
}
