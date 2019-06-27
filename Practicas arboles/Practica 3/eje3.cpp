//TERMINARRRRRRRRRRRRRRRRRRRRRRRRRR
#include <iostream>
#include <fstream>
#include <algorithm>
#include "agen.h"
#include "agen_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin='#';

template <typename T>
int altura_rec(typename Agen<T>::nodo n, const Agen<T>& A){
  if(n == Agen<T>::NODO_NULO){
    return 0;
  }
  else{
    //cout << "Elemento: " << A.elemento(n) << endl;
    int maxima_hijos = -1; //Altura maxima de los hijos. Yo soy -1
    n = A.hijoIzqdo(n);

    while(n != Agen<T>::NODO_NULO){
      maxima_hijos = std::max(maxima_hijos, altura_rec(n, A));
      n = A.hermDrcho(n);
    }

    return 1 + maxima_hijos;
  }
}

template<typename T>
int alturaMin_rec(typename Agen<T>::nodo n, const Agen<T>& A){
  if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO){ //Es un nodo hoja.
    return 0;
  }
  else{
    int minima_hermanos = 1000; //Altura minima de los hijos.
    n = A.hijoIzqdo(n);

    while(n != Agen<T>::NODO_NULO){
      minima_hermanos = std::min(minima_hermanos, alturaMin_rec(n, A));
      n = A.hermDrcho(n);
    }

    return 1 + minima_hermanos;
  }
}

template <typename T>
int desequilibrio_rec(typename Agen<T>::nodo n, const Agen<T>& A){
  //Recorrer el arbol recogiendo el desequilibrio max encontrado.
  if(n == Agen<T>::NODO_NULO)
    return 0;
  else{
    int desequilibrio_propio, desequilibrio_hijos = -1;
    desequilibrio_propio = altura_rec(n,A) - alturaMin_rec(n,A);

    n = A.hijoIzqdo(n);

    while(n != Agen<T>::NODO_NULO){
      desequilibrio_hijos = std::max(desequilibrio_hijos, desequilibrio_rec(n,A));
      n = A.hermDrcho(n);
    }

    return std::max(desequilibrio_hijos, desequilibrio_propio);
  }
}

template <typename T>
int desequilibrio(const Agen<T>& A){
  return desequilibrio_rec(A.raiz(), A);
}


int main(){
  Agen<tElto> A;
  cout<<"\n*** Lectura de arbol A de agen.dat ***\n";
  ifstream fe("agen.dat");
  rellenarAgen(fe,A);
  fe.close();

  cout<<"\n *** Mostrar arbol***\n";
  imprimirAgen(A);


  cout<<"Desequilibrio: "<<desequilibrio(A)<<endl;

}
