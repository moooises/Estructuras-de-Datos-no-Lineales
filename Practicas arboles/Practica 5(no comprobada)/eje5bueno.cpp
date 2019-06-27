#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "agen.h"
#include "agen_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin='#';

template <typename T>
int altura_rec(const Agen<T>& A,typename Agen<T>::nodo n){
  if(n == Agen<T>::NODO_NULO){
    return 0;
  }
  else{
    //cout << "Elemento: " << A.elemento(n) << endl;
    int maxima_hijos = -1; //Altura maxima de los hijos. Yo soy -1
    n = A.hijoIzqdo(n);

    while(n != Agen<T>::NODO_NULO){
      maxima_hijos = std::max(maxima_hijos, altura_rec(A,n));
      n = A.hermDrcho(n);
    }

    return 1 + maxima_hijos;
  }
}

template <typename T>
int altura(const Agen<T>& A)
{
  return altura_rec(A,A.raiz());
}

void rellenarBlanco(int& M[][],int inifila,int finfila,int inicol,int fincol)//representamos el blanco como 1
{
  for(int i=inifila;i<=finfila;++i)
  {
    for(int j=inicol;j<=fincol;++j)
    {
      M[i][j]=1;
    }
  }
}

void rellenarNegro(int& M[][],int inifila,int finfila,int inicol,int fincol)//representamos el negro como 0
{
  for(int i=inifila;i<=finfila;++i)
  {
    for(int j=inicol;j<=fincol;++j)
    {
      M[i][j]=0;
    }
  }
}

template <typename T>
void figura_rec(const Agen<T>& A,int& [][]M,typename Agen<T>::nodo n,int inifila,int finfila,int inicol,int fincol)
{
  if(n!=Agen<T>::NODO_NULO)
  {
    n=A.hijoIzqdo(n);

    if(A.elemento(n)=='N')
    {
      rellenarNegro(M,inifila,finfila/2,inicol,fincol/2);
    }
    else
    {
      if(A.elemento(n)=='B')
      {
        rellenarBlanco(M,inifila,finfila/2,inicol,fincol/2)
      }
      else
      {
        figura_rec(A,M,A.hijoIzqdo(n),inifila,finfila/2,inicol,fincol/2);
      }
    }

    n=A.hermDrcho(n);

    if(A.elemento(n)=='N')
    {
      rellenarNegro(M,inifila,finfila/2,(fincol/2)+1,fincol);
    }
    else
    {
      if(A.elemento(n)=='B')
      {
        rellenarBlanco(M,inifila,finfila/2,(fincol/2)+1,fincol)
      }
      else
      {
        figura_rec(A,M,A.hijoIzqdo(n),inifila,finfila/2,(fincol/2)+1,fincol);
      }
    }

    n=A.hermDrcho(n);

    if(A.elemento(n)=='N')
    {
      rellenarNegro(M,(finfila/2)+1,finfila,(fincol/2)+1,fincol);
    }
    else
    {
      if(A.elemento(n)=='B')
      {
        rellenarBlanco(M,(finfila/2)+1,finfila,(fincol/2)+1,fincol)
      }
      else
      {
        figura_rec(A,M,A.hijoIzqdo(n),(finfila/2)+1,finfila,(fincol/2)+1,fincol);
      }
    }

    n=A.hermDrcho(n);

    if(A.elemento(n)=='N')
    {
      rellenarNegro(M,(finfila/2)+1,finfila,inicol,fincol/2);
    }
    else
    {
      if(A.elemento(n)=='B')
      {
        rellenarBlanco(M,(finfila/2)+1,finfila,inicol,fincol/2)
      }
      else
      {
        figura_rec(A,M,A.hijoIzqdo(n),(finfila/2)+1,finfila,inicol,fincol/2);
      }
    }

  }
}

template <typename T>
void figura(const Agen<T>& A, int& M[][],int inifila,int finfila,int inicol,int fincol)
{
  if(A.elemento(A.raiz())=='S')figura_rec(A,M,A.raiz(),inifila,finfila,inicol,fincol);
  else
  {
    if(A.elemento(A.raiz())=='B')rellenarBlanco(M,inifila,finfila,inicol,fincol);
    else
    {
      rellenarNegro(M,inifila,finfila,inicol,fincol);
    }
  }
}


int main(){

Agen<tElto> A;

cout<<"*** Lectura del arbol A***\n";

cout<<"\n*** Lectura de arbol A de agen.dat ***\n";
ifstream fe("agenBN.dat");
rellenarAgen(fe,A);
fe.close();

cout<<"\n *** Mostrar arbol***\n";
imprimirAgen(A);

int k=altura(A);
cout<<"Altura: "<<k<<endl;
int M[pow(2,k)][pow(2,k)];
figura(A,M,0,pow(2,k)-1,0,pow(2,k)-1);//importante le restamos 1 al final
}
