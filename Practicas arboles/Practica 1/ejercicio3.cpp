#include <iostream>
#include <fstream>
#include "abin_E-S.h"
#include "abin.h"
using namespace std;

typedef char tElto;
const tElto fin = '#';

template <typename T>
int profundidad(const Abin<T>& A, typename Abin<T>::nodo n){//Importante debemos pasar el arbol por referencia
  if(n!=A.raizB()) return 1+profundidad(A,A.padreB(n));
  else return 0;
}

int main(){
  Abin<tElto> A;
  ifstream fe("abin.dat");
  rellenarAbin(fe,A);
  fe.close();
  cout<<"\n*** Mostrar árbol binario***\n";
  imprimirAbin(A);
  //if(n==Abin<tElto>::NODO_NULO)cout<<"Es nulo"<<endl;
  cout<<"La produndidad del nodo  es "<<profundidad(A,A.hijoIzqdoB(A.raizB()))<<endl;
}
