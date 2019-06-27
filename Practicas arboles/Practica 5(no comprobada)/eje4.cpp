#include <iostream>
#include <fstream>
#include <algorithm>
#include "agen.h"
#include "agen_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin='#';

template <typename T>
bool rec_ternario(const Agen<T>& A, typename Agen<T>::nodo n)
{
    bool aux=true;
    int cont=0;
    n=A.hijoIzqdo(n);
    while(n!=Agen<T>::NODO_NULO && aux)//el aux esta para parar la busqueda en el momento que haya un false
    {
      aux=aux && rec_ternario(A,A.hijoIzqdo(n));
      n=A.hermDrcho(n);
      cont++;
    }
    if(!aux) return false;
    else{
      if(cont!=0 && cont!= 3)return false;//podriamos poner aqui el aux, pero asi se ve mas claro
      else
      {
        return true;
      }
    }
}

template <typename T>
bool ternario(const Agen<T>& A)
{

  return rec_ternario(A,A.raiz());
}

int main(){
  Agen<tElto> A;
  cout<<"\n*** Lectura de arbol A de agen.dat ***\n";
  ifstream fe("agen.dat");
  rellenarAgen(fe,A);
  fe.close();

  cout<<"\n *** Mostrar arbol***\n";
  imprimirAgen(A);

  if(ternario(A))cout<<"El arbol es Ternario"<<endl;
  else cout<<"No es ternario"<<endl;
}
