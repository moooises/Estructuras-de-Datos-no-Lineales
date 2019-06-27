//si un nodo solo tiene un hijo eliminar toda la descendencia de este hijo
//Iba a llamarlo 'aborto.cpp', pero me lo he pensado

#include <iostream>
#include <fstream>
#include "abin_E-S.h"
#include "abin.h"
using namespace std;

typedef char tElto; //esto indica el tipo del arbol
const tElto fin = '#'; //caracter de fin de lectura

template <typename T>//Similar al de arboles reflejados
void destruirNodo(Abin<T>& A,typename Abin<T>::nodo n){//Si se os ocurre usar 'delete', os crujen
  if(A.hijoIzqdoB(n)!=Abin<T>::NODO_NULO){
  destruirNodo(A,A.hijoIzqdoB(n));
  A.eliminarHijoIzqdoB(n);
  }

  if(A.hijoDrchoB(n)!=Abin<T>::NODO_NULO){
  destruirNodo(A,A.hijoDrchoB(n));
  A.eliminarHijoDrchoB(n);
  }
}

template <typename T>
void unhijo(Abin<T>& A,typename Abin<T>::nodo n){
  if(n!=Abin<T>::NODO_NULO){
    if(A.hijoDrchoB(n)!=Abin<T>::NODO_NULO && A.hijoIzqdoB(n)==Abin<T>::NODO_NULO)
    {
      destruirNodo(A,A.hijoDrchoB(n));
      //si se tuviera que destruir el propio nodo se añade la instruccion de eliminar hijo derecho aqui
    }
    else
    {
      if(A.hijoDrchoB(n)==Abin<T>::NODO_NULO && A.hijoIzqdoB(n)!=Abin<T>::NODO_NULO)
      {
        destruirNodo(A,A.hijoIzqdoB(n));
        //IDEM pero con el izquierdo
      }
      else
      {
        unhijo(A,A.hijoIzqdoB(n));
        unhijo(A,A.hijoDrchoB(n));
      }
    }
  }
}

template <typename T>
void eliminarprimojenitos(Abin<T>& A){
  if(!A.arbolVacioB()) unhijo(A,A.raizB());
}

int main(){
  Abin<tElto> A;
/**  cout << "*** Lectura del árbol binario A ***\n";
  rellenarAbin(A, fin);      // desde std::cin
  ofstream fs("abin.dat");   // abrir fichero de salida
  imprimirAbin(fs, A, fin);  // en fichero
  fs.close();
  cout << "\n*** Árbol A guardado en fichero abin.dat ***\n";
*/
  ifstream fe("abin.dat");   // abrir fichero de entrada
  rellenarAbin(fe, A);       // desde fichero
  fe.close();
  cout << "\n*** Mostrar árbol binario***\n";
  imprimirAbin(A);           // en std::cou

  eliminarprimojenitos(A);
cout<<endl;
  imprimirAbin(A);
}
