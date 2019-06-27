#include <iostream>
#include <fstream>
#include "abin_E-S.h"
#include "abin.h"
using namespace std;

typedef char tElto; //esto indica el tipo del arbol
const tElto fin = '#'; //caracter de fin de lectura

int max(int a,int b){
  if(a>b) return a;
  else return b;
}

template <typename T>
int altura(Abin<T>& A, typename Abin<T>::nodo n){
  if(n==Abin<T>::NODO_NULO)return 0;
  else{

  if(A.hijoDrchoB(n)==Abin<T>::NODO_NULO && A.hijoIzqdoB(n)==Abin<T>::NODO_NULO)return 1;
  else return 1+max(altura(A,A.hijoIzqdoB(n)),altura(A,A.hijoDrchoB(n)));
  }
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
cout<<"La altura del arbol es "<<altura(A,A.raizB())<<endl;
}
