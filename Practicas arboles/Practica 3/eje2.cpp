//Es igual que el de arboles binarios, los arboles generales son distintos a la hora de bajar pero no a la de subir
#include <iostream>
#include <fstream>
#include <algorithm>
#include "agen.h"
#include "agen_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin='#';

template <typename T>
int profundidad(const Agen<T>& A,typename Agen<T>::nodo n){
  if(n==A.raiz()) return 0;
  else return 1+profundidad(A,A.padre(n));
}

int main(){
  Agen<tElto> A;
  cout<<"\n*** Lectura de arbol A de agen.dat ***\n";
  ifstream fe("agen.dat");
  rellenarAgen(fe,A);
  fe.close();

  cout<<"\n *** Mostrar arbol***\n";
  imprimirAgen(A);

  cout<<"La profundidad del arbol es "<<profundidad(A,A.hijoIzqdo(A.hijoIzqdo(A.raiz())))<<endl;
}
