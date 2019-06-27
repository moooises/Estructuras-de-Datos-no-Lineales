#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "abin_E-S.h"
#include "abin.h"
using namespace std;

union operando{
  char op;
  double num;
}//NO sabia esto, union es un tipo de registro en el que solo se puede almacenar uno de los atributos que tiene

/**Paso muy fuerte de modificar el ABIN_E_S,asi que lo he hecho con char y transformandolo en entero
lo suyo seria hacerlo con 'operando' y usando el '.' para acceder a 'num' cuando sea nodo hoja y 'op' en otro caso
*/

/**
SOLO ES VALIDO CON ENTEROSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
Para hacerlo con doubles, crea un struct con un char y un double
*/
typedef char tElto;
//typedef nodo tElto;
const tElto fin='#';//necesitamos crear un nodo final

template <typename T>
double rec_expresion(const Abin<T>& A,typename Abin<T>::nodo n){
  if(A.hijoDrchoB(n)==Abin<T>::NODO_NULO && A.hijoIzqdoB(n)==Abin<T>::NODO_NULO) {
  //  cout<<(double)(A.elemento(n))<<endl;
    const char* b= new char(A.elemento(n));//borrar esta linea si trabajas con 'operando'
    return atof(b);                        //No le hagais esto a 'De la huerta', que os cruje y 'Simio' tb
    //cambiar la '33' por 'return oper.num' siendo 'oper' un tipo 'operando'
  }
  else{
    char ex= A.elemento(n);//Cambiar esta linea por 'char ex = oper.op;'
    switch(ex){
      case '+': return  rec_expresion(A,A.hijoIzqdoB(n)) + rec_expresion(A,A.hijoDrchoB(n)); break;
      case '-': return  rec_expresion(A,A.hijoIzqdoB(n)) - rec_expresion(A,A.hijoDrchoB(n)); break;
      case '*': return  rec_expresion(A,A.hijoIzqdoB(n)) * rec_expresion(A,A.hijoDrchoB(n)); break;// usamos * en lugar de x
      case '/': return  rec_expresion(A,A.hijoIzqdoB(n)) / rec_expresion(A,A.hijoDrchoB(n)); break;
      default: cout<<"Operacion no considerada"<<endl;break;
    }
  }
}

template <typename T>
double expresion(const Abin<T>& A){
  if(A.arbolVacioB())return 0;
  else return rec_expresion(A,A.raizB());
}

int main(){
  Abin<tElto> A;
  /**cout << "*** Lectura del árbol binario A ***\n";
  rellenarAbin(A, fin);      // desde std::cin
  ofstream fs("abin3.dat");   // abrir fichero de salida
  imprimirAbin(fs, A, fin);  // en fichero
  fs.close();
  cout << "\n*** Árbol A guardado en fichero abin.dat ***\n";
*/
  ifstream fe("abin3.dat");
  rellenarAbin(fe,A);
  fe.close();
  cout<<"\n*** Mostrar árbol binario***\n";
  imprimirAbin(A);
//Si quereis probar operando quitad de la linea 62 hasta la 66 y cambiar la plantilla del arbol a 'operando' en lugar de tElto
//y los meteis de forma manual, es decir, con instrucciones de insertar raiz, hijoderch, hijoizq
  cout<<"El resultado de la operacion es: "<<expresion(A)<<endl;
}
