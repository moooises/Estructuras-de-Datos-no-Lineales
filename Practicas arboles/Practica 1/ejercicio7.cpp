#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "abin_E-S.h"
#include "abin.h"
using namespace std;

typedef char tElto;
const tElto fin='#';

//Hacer haciendo uso de la altura del nodo
template <typename T>
bool pseudocompleto(const Abin<T>& A, typename Abin<T>::nodo n){
  if(A.alturaB(n)<2){//NO OLVIDAR COMO ESTA DEFINIDO ALTURA
      if((n==Abin<T>::NODO_NULO) || (A.hijoDrchoB(n)!=Abin<T>::NODO_NULO && A.hijoIzqdoB(n)!=Abin<T>::NODO_NULO)
          || (A.hijoDrchoB(n)==Abin<T>::NODO_NULO && A.hijoIzqdoB(n)==Abin<T>::NODO_NULO))return true;//Las tres condiciones que devuelve cierto
      else return false;
  }
  else{
    if(A.alturaB(A.hijoDrchoB(n))<A.alturaB(A.hijoIzqdoB(n))) return pseudocompleto(A,A.hijoIzqdoB(n));//Si la altura del hijo izq es mayor que la del derch
    else {                                                                                              //solo nos interesa el subarbol izq
       if(A.alturaB(A.hijoDrchoB(n))>A.alturaB(A.hijoIzqdoB(n))) return pseudocompleto(A,A.hijoDrchoB(n));//Si la altura del hijo derech es mayor que la del izq so
                                                                                                        //solo nos interesa el subarbol derch
       else return pseudocompleto(A,A.hijoDrchoB(n)) && pseudocompleto(A,A.hijoIzqdoB(n));//Si la altura de ambos subarboles son iguales
  }
}


/**
template <typename T>
bool pseudocompleto(const Abin<T>& A,typename Abin<T>::nodo n,int altura){
  if(altura>1){//la unica forma de que sea menor que 1 es siend vacio, tenemos en cuente que un arbol de un solo nodo tiene altura 0 y si es vacio tb
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
    if(n==Abin<T>::NODO_NULO || (A.hijoDrchoB(n)==Abin<T>::NODO_NULO && A.hijoIzqdoB(n)==Abin<T>::NODO_NULO) || (A.hijoDrchoB(n)!=Abin<T>::NODO_NULO && A.hijoIzqdoB(n)!=Abin<T>::NODO_NULO)) return true;
    else return false;
  }

}
*/

int main(){
  Abin<tElto> A;
  ifstream fe("abin.dat");
  rellenarAbin(fe,A);
  fe.close();
  cout<<"\n*** Mostrar árbol binario***\n";
  imprimirAbin(A);
  cout<<"Altura del arbol: "<<A.alturaB(A.raizB())<<endl;

  if((pseudocompleto(A,A.raizB())==true))cout<<"Es pseudocompleto"<<endl;
  else cout<<"No es pseudocompleto"<<endl;
}
