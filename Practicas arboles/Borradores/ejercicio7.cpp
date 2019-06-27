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
bool pseudocompleto(const Abin<T>& A,typename Abin<T>::nodo n,int altura){
  if(altura>1){
    if(A.hijoDrchoB(n)!=Abin<T>::NODO_NULO && A.hijoIzqdoB(n)!=Abin<T>::NODO_NULO){
      return pseudocompleto(A,A.hijoDrchoB(n),altura-1) && pseudocompleto(A,A.hijoIzqdoB(n),altura-1);
    }
    else{
      if(A.hijoDrchoB(n)!=Abin<T>::NODO_NULO) return pseudocompleto(A,A.hijoDrchoB(n),altura-1);
      else{
        if(A.hijoIzqdoB(n)!=Abin<T>::NODO_NULO)return pseudocompleto(A,A.hijoIzqdoB(n),altura-1);
        else return true;//entendemos que si un nodo no tiene ningun hijo y no se encuentra en el penultimo nivel del arbol cumple
                        //las condiciones para ser pseudocompleto
      }
    }
  }
  else{
    if((A.hijoDrchoB(n)==Abin<T>::NODO_NULO && A.hijoIzqdoB(n)==Abin<T>::NODO_NULO) || (A.hijoDrchoB(n)!=Abin<T>::NODO_NULO && A.hijoIzqdoB(n)!=Abin<T>::NODO_NULO)) return true;
    else return false;
  }

}


int main(){
  Abin<tElto> A;
  ifstream fe("abin.dat");
  rellenarAbin(fe,A);
  fe.close();
  cout<<"\n*** Mostrar árbol binario***\n";
  imprimirAbin(A);
  cout<<"Altura del arbol: "<<A.alturaB(A.raizB());

  if((pseudocompleto(A,A.raizB(),A.alturaB(A.raizB())))==true)cout<<"Es pseudocompleto"<<endl;
  else cout<<"No es pseudocompleto"<<endl;
}
