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
bool similares(const Abin<T>& A,const Abin<T>& B){
  if (A.raizB()==Abin<T>::NODO_NULO && B.raizB()==Abin<T>::NODO_NULO) return true;
  return rec_similares(A,B,A.raizB(),B.raizB());
}

//Intentar usar condiciones de salida con NODO_NULO
//De laHuerta approved

template <typename T>
bool rec_similares(const Abin<T>& A, const Abin<T>& B, typename Abin<T>::nodo a,typename Abin<T>::nodo b){
  if(a==Abin<T>::NODO_NULO && b==Abin<T>::NODO_NULO)return true;
  else{
    if((a==Abin<T>::NODO_NULO && b!=Abin<T>::NODO_NULO) || (a!=Abin<T>::NODO_NULO && b==Abin<T>::NODO_NULO))return false;
    else{
        return rec_similares(A,B,A.hijoDrchoB(a),B.hijoDrchoB(b)) && rec_similares(A,B,A.hijoIzqdoB(a),B.hijoIzqdoB(b));
    }
  }
}
/**
template <typename T>
bool rec_similares(const Abin<T>& A,const Abin<T>& B,typename Abin<T>::nodo a, typename Abin<T>::nodo b){
  if(A.hijoDrchoB(a)!=Abin<T>::NODO_NULO && A.hijoIzqdoB(a)!=Abin<T>::NODO_NULO && B.hijoDrchoB(b)!=Abin<T>::NODO_NULO && B.hijoIzqdoB(b)!=Abin<T>::NODO_NULO){
    return (rec_similares(A,B,A.hijoDrchoB(a),B.hijoDrchoB(b)) && rec_similares(A,B,A.hijoIzqdoB(a),B.hijoIzqdoB(b)));
  }
  else{
    if(A.hijoDrchoB(a)==Abin<T>::NODO_NULO && A.hijoIzqdoB(a)!=Abin<T>::NODO_NULO && B.hijoDrchoB(b)==Abin<T>::NODO_NULO && B.hijoIzqdoB(b)!=Abin<T>::NODO_NULO){
      return rec_similares(A,B,A.hijoIzqdoB(a),B.hijoIzqdoB(b));
    }
    else{
      if(A.hijoDrchoB(a)!=Abin<T>::NODO_NULO && A.hijoIzqdoB(a)==Abin<T>::NODO_NULO && B.hijoDrchoB(b)!=Abin<T>::NODO_NULO && B.hijoIzqdoB(b)==Abin<T>::NODO_NULO){
        return rec_similares(A,B,A.hijoDrchoB(a),B.hijoDrchoB(b));
      }
      else{
        if(A.hijoDrchoB(a)==Abin<T>::NODO_NULO && A.hijoIzqdoB(a)==Abin<T>::NODO_NULO && B.hijoDrchoB(b)==Abin<T>::NODO_NULO && B.hijoIzqdoB(b)==Abin<T>::NODO_NULO){
          return true;
        }
        else{
          return false;
        }
      }
    }
  }
}*/


int main(){
  Abin<tElto> A,B;
  ifstream fe1("abin.dat");
  rellenarAbin(fe1,A);
  fe1.close();
  cout<<"\n*** Mostrar árbol binario***\n";
  imprimirAbin(A);

  ifstream fe2("abin2.dat");
  rellenarAbin(fe2,B);
  fe2.close();
  cout<<"\n*** Mostrar árbol binario***\n";
  imprimirAbin(B);

  if(similares(A,B))cout<<"Son similares"<<endl;
  else cout<<"No son similares"<<endl;
}
