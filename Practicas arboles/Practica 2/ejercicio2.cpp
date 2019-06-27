#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "abin_E-S.h"
#include "abin.h"
using namespace std;

typedef char tElto;
const tElto fin='#';

//De la Huerta approved
template <typename T>
void rec_reflejado(Abin<T>& A,typename Abin<T>::nodo a,Abin<T>& B,typename Abin<T>::nodo b){//Es necesario pasar el arbol por referencia
    if(A.hijoIzqdoB(a)!=Abin<T>::NODO_NULO){
      B.insertarHijoDrchoB(b,A.elemento(A.hijoIzqdoB(a)));
      rec_reflejado(A,A.hijoIzqdoB(a),B,B.hijoDrchoB(b));
    }

      if(A.hijoDrchoB(a)!=Abin<T>::NODO_NULO){
        B.insertarHijoIzqdoB(b,A.elemento(A.hijoDrchoB(a)));
        rec_reflejado(A,A.hijoDrchoB(a),B,B.hijoIzqdoB(b));
      }

}

template <typename T>
Abin<T> reflejado(Abin<T>& A){// es necesario parar el arbol por referencia
Abin<T> B;
if(A.arbolVacioB())return B;
else {
  B.insertarRaizB(A.elemento(A.raizB()));
   rec_reflejado(A,A.raizB(),B,B.raizB());
   return B;
  }
}


int main(){
  Abin<tElto> B;
  ifstream fe("abin.dat");
  rellenarAbin(fe,B);
  fe.close();
  cout<<"\n*** Mostrar árbol binario***\n";
  imprimirAbin(B);
  Abin<tElto> BR=reflejado(B);
  cout<<"\n";
  imprimirAbin(BR);

}
