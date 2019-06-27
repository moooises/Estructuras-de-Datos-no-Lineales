//Cuantos nodos de un arbol son rebeldes, un nodo es rebelde si es distinto de la MAYORIA de sus ancestros, los nodos son booleanos

//Dato importante, el padre de la raiz es NODO_NULO
#include<iostream>
#include "abin.h"
using namespace std;

int contarFalse(const Abin<bool>& A,Abin<bool>::nodo n){//Cuenta los acestros falso
  if(n==Abin<bool>::NODO_NULO)return 0;
  else{
    if(A.elemento(n)==false)return 1+contarFalse(A,A.padreB(n));
    else return contarFalse(A,A.padreB(n));
  }
}

int contarTrue(const Abin<bool>& A,Abin<bool>::nodo n){//Cuenta los ancestro verdaderos

  if(n==Abin<bool>::NODO_NULO)return 0;
  else{
    if(A.elemento(n)==true)return 1+contarTrue(A,A.padreB(n));
    else return contarTrue(A,A.padreB(n));
  }
}

int rebeldesreco(const Abin<bool>& A, Abin<bool>::nodo n){
  if(n==Abin<bool>::NODO_NULO) return 0;//Condicion de salida
  else{
    if(A.elemento(n)==true){//si es verdadero y tiene mas ancestros falsos es rebelde
        if(contarFalse(A,A.padreB(n))>contarTrue(A,A.padreB(n))) return 1+(rebeldesreco(A,A.hijoIzqdoB(n))+rebeldesreco(A,A.hijoDrchoB(n)));
        else return rebeldesreco(A,A.hijoIzqdoB(n))+rebeldesreco(A,A.hijoDrchoB(n));
    }
    else{//Viceversa
      if(contarTrue(A,A.padreB(n))>contarFalse(A,A.padreB(n))) return 1+(rebeldesreco(A,A.hijoIzqdoB(n))+rebeldesreco(A,A.hijoDrchoB(n)));
      else return rebeldesreco(A,A.hijoIzqdoB(n))+rebeldesreco(A,A.hijoDrchoB(n));
    }
  }
}

int rebeldes(const Abin<bool>& A){
  if(A.arbolVacioB())return 0;
  else return rebeldesreco(A,A.raizB());//Vamos a suponer que la raiz es rebelde si no lo fuera tendriamos que modificar esta funcion de la siguiente manera
}

/**
int rebeldes(const Abin<bool>& A){
  if(A.arbolVacioB()==true)return 0;
  return rebeldesreco(A,A.hijoIzqdoB(A.raizB()))+rebeldesreco(A,A.hijoDrchoB(A.raizB()));
}
*/

int main(){
  Abin<bool> A;
  A.insertarRaizB(true);
  A.insertarHijoIzqdoB(A.raizB(),false);
  A.insertarHijoIzqdoB(A.hijoIzqdoB(A.raizB()),false);
  A.insertarHijoIzqdoB(A.hijoIzqdoB(A.hijoIzqdoB(A.raizB())),false);
  A.insertarHijoIzqdoB(A.hijoIzqdoB(A.hijoIzqdoB(A.hijoIzqdoB(A.raizB()))),true);
  A.insertarHijoDrchoB(A.raizB(),true);
  A.insertarHijoDrchoB(A.hijoDrchoB(A.raizB()),true);
  A.insertarHijoDrchoB(A.hijoDrchoB(A.hijoDrchoB(A.raizB())),false);
  //Dibujad el arbol, son dos ramas de tres nodos, partiendo de la raiz

  cout<<"Hay "<<rebeldes(A)<<" nodos rebeldes"<<endl;


}
