#include "abin_E-S.h"
#include "abin.h"
using namespace std;

typedef char tElto; //esto indica el tipo del arbol
const tElto fin = '#'; //caracter de fin de lectura

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

//Estas operaciones estan implememtadas en 'abin.h', las dos primeras operaciones que son implememtadas
  cout<<"Altura del arbol: "<<A.alturaB(A.raizB())<<endl;
  cout<<"Profundidad del nodo: "<<A.profundidadB(A.hijoIzqdoB(A.raizB()))<<endl;

}
