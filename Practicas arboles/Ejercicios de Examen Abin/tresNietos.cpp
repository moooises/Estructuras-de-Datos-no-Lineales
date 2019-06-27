//Cuantos nodos del arbol A tienen exactamente 3 nietos //Edit: esto era para un agen
//Cuanto nodos del arbol A tienen exactamente 3 descendentes

#include <iostream>
#include <fstream>
#include "abin_E-S.h"
#include "abin.h"
using namespace std;

typedef char tElto; //esto indica el tipo del arbol
const tElto fin = '#'; //caracter de fin de lectura

template <typename T>
int contar(Abin<T>& A, typename Abin<T>::nodo n){
  if(n==Abin<T>::NODO_NULO)return 0;
  else return 1+(contar(A,A.hijoIzqdoB(n))+contar(A,A.hijoDrchoB(n)));
}

template <typename T>
int tresNietosrecorrido(Abin<T>& A,typename Abin<T>::nodo n){
  if(n==Abin<T>::NODO_NULO)return 0;
  else{
    //cout<<A.elemento(n)<<" "<<(contar(A,A.hijoIzqdoB(n))+contar(A,A.hijoDrchoB(n)))<<endl;
    if((contar(A,A.hijoIzqdoB(n))+contar(A,A.hijoDrchoB(n)))==3) {
      cout<<"Tres"<<endl;
      return 1+(tresNietosrecorrido(A,A.hijoDrchoB(n))+tresNietosrecorrido(A,A.hijoIzqdoB(n)));
      }
    else return (tresNietosrecorrido(A,A.hijoDrchoB(n))+tresNietosrecorrido(A,A.hijoIzqdoB(n)));
  }
}

template <typename T>
int tresNietos(Abin<T>& A){
  return tresNietosrecorrido(A,A.raizB());
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


  cout<<"Hay "<<tresNietos(A)<<" nodos con 3 nietos en el arbol"<<endl;

}
