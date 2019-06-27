//Si el valor en entero de un nodo es mayor que el de todos sus ancestros y menor que todos sus descendientes

#include <iostream>
#include "abin.h"

bool ancestrosproperos(const Abin<int>& A, Abin<int>::nodo n,int valor){//puedes pasarle el nodo y dentro de la funcion sacar el valor si quieres
  if(n==Abin<int>::NODO_NULO)return true;//si sobrepasa la raiz es cierto
  else{
    if(A.elemento(n)>valor) return false;
    else return ancestrosproperos(A,A.padreB(n),valor);
  }
}

bool descendientesprosperos(const Abin<int>& A, Abin<int>::nodo n,int valor){
  if(n==Abin<int>::NODO_NULO)return true;//si sobrepasa una hoja es cierto
  else{
    if(A.elemento(n)<valor) return false;
    else return descendientesprosperos(A,A.hijoIzqdoB(n),valor) && descendientesprosperos(A,A.hijoDrchoB(n),valor);
  }
}

int prosperosrec(const Abin<int>& A, Abin<int>::nodo n){
  if(n==Abin<int>::NODO_NULO)return 0
  else{
    if(ancestrosproperos(A,A.hijoDrchoB(n),A.elemento(n)) && descendientesprosperos(A,A.hijoIzqdoB(n),A.elemento(n))) return 1+(prosperosrec(A,A.hijoIzqdoB(n))+prosperosrec(A,A.hijoDrchoB(n)));
    else return prosperosrec(A,A.hijoIzqdoB(n))+prosperosrec(A,A.hijoDrchoB(n));
  }
}

int prosperos(const Abin<int>& A){
  if(A.arbolVacioB())return 0;
  else return prosperosrec(A,A.raizB());//Lo mismo que en rebeldes
}

int main(){
  Abin<int> A;
  A.insertarRaizB(1);
  A.insertarHijoIzqdoB(A.raizB(),2);
  A.insertarHijoIzqdoB(A.hijoIzqdoB(A.raizB()),3);
  A.insertarHijoIzqdoB(A.hijoIzqdoB(A.hijoIzqdoB(A.raizB())),2);
  A.insertarHijoIzqdoB(A.hijoIzqdoB(A.hijoIzqdoB(A.hijoIzqdoB(A.raizB()))),2);
  A.insertarHijoDrchoB(A.raizB(),4);
  A.insertarHijoDrchoB(A.hijoDrchoB(A.raizB()),5);
  A.insertarHijoDrchoB(A.hijoDrchoB(A.hijoDrchoB(A.raizB())),6);

  cout<<"Hay "<<prosperos(A)<<" nodos prosperos"<<endl;
}
