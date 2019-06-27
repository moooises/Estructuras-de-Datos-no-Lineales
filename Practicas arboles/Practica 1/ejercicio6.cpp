#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "abin_E-S.h"
#include "abin.h"
using namespace std;

typedef char tElto;
const tElto fin='#';

template <typename T>
int desequilibrio(const Abin<T>& A,typename Abin<T>::nodo n){
  if(n==Abin<T>::NODO_NULO)return 0;
  else{
    int des=abs(A.alturaB(A.hijoDrchoB(n))-A.alturaB(A.hijoIzqdoB(n)));// Esto es para dejarlo mas claro
    return max(max(desequilibrio(A,A.hijoDrchoB(n)),desequilibrio(A,A.hijoIzqdoB(n))),des);
  }
}

/**
Esta forma tb vale, pero es mas correcta y eficiente la de arriba

template <typename T>
int desequilibrio(Abin<T>& A,typename Abin<T>::nodo n,int maxi){
  if(n!=Abin<T>::NODO_NULO){
    int aux=abs(A.alturaB(A.hijoDrchoB(n))-A.alturaB(A.hijoIzqdoB(n)));
    if(aux>maxi)maxi=aux;
    return max(desequilibrio(A,A.hijoDrchoB(n),maxi),desequilibrio(A,A.hijoIzqdoB(n),maxi));
  }
  else{
    return maxi;
  }

}
*/
template <typename T>
int desequilibriorec(const Abin<T>& A, typename Abin<T>::nodo n){
  return desequilibrio(A,A.raizB());
}

int main(){
  Abin<tElto> A;
  ifstream fe("abin.dat");
  rellenarAbin(fe,A);
  fe.close();
  cout << "\n*** Mostrar árbol binario***\n";
  imprimirAbin(A);
cout<<"El maximo desequilibrio del arbol es "<<desequilibriorec(A,A.raizB());

}
