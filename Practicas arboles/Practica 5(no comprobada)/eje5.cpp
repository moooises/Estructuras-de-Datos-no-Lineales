#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "agen.h"
#include "agen_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin='#';
int B=1;//Blanco
int N=0;//Negro
int S=2;//Ninguno de los dos

template <typename T>
bool AllWhite(const int& M[][],int inifila,int fincol,int inicol,int fincol)//Comprueba si en el cuadrante son todos blancos
{
  for(int i=inifila;i<=finfila;++i)//Ojo, menor o igual
  {
    for(int j=inicol;j<=fincol;++j)
    {
      if(M[i][j]==N)return false;
    }
  }
  return true;
}

template <typename T>
bool AllBlack(const int& M[][],int inifila,int fincol,int inicol,int fincol)//
{
  for(int i=inifila;i<=finfila;++i)
  {
    for(int j=inicol;j<=fincol;++j)
    {
      if(M[i][j]==B)return false;
    }
  }
  return true;
}

template <typename T>
void arbol_plano(const int& M[][],Agen<T>& A,typename Agen<T>::nodo n,int inifila,int finfila,int inicol,int fincol)//recoredomes que la matriz es cuadrada
{
  if(n!=Agen<T>::NODO_NULO)
  {
    if(AllBlack(M,inifila,finfila/2,inicol,fincol/2))
    {
        A.insertarHijoIzqdo(n,N);
    }
    else
    {
      if(AllWhite(M,inifila,finfila/2,inicol,fincol/2))
      {
        A.insertarHijoIzqdo(n,B);
      }
      else
      {
        A.insertarHijoIzqdo(n,S);
        arbol_plano(M,A,A.hijoIzqdo(n),inifila,finfila/2,inicol,fincol/2);
      }
    }

    n=A.hijoIzqdo(n);

    if(AllBlack(M,inifila,finfila/2,fincol/2+1,fincol))
    {
        A.insertarHermDrcho(n,N);
    }
    else
    {
      if(AllWhite(M,inifila,finfila/2,fincol/2+1,fincol))
      {
        A.insertarHermDrcho(n,B);
      }
      else
      {
        A.insertarHermDrcho(n,S);
        arbol_plano(M,A,A.hijoIzqdo(n),inifila,finfila/2,fincol/2+1,fincol);
      }
    }

    n=A.hermDrcho(n);

    if(AllBlack(M,inifila/2+1,finfila,fincol/2+1,fincol))
    {
        A.insertarHermDrcho(n,N);
    }
    else
    {
      if(AllWhite(M,inifila/2+1,finfila,fincol/2+1,fincol))
      {
        A.insertarHermDrcho(n,B);
      }
      else
      {
        A.insertarHermDrcho(n,S);
        arbol_plano(M,A,A.hijoIzqdo(n),inifila/2+1,finfila,fincol/2+1,fincol);
      }
    }

    n=A.hermDrcho(n);

    if(AllBlack(M,inifila/2+1,finfila,inicol,fincol/2))
    {
        A.insertarHermDrcho(n,N);
    }
    else
    {
      if(AllWhite(M,inifila/2+1,finfila,inicol,fincol/2))
      {
        A.insertarHermDrcho(n,B);
      }
      else
      {
        A.insertarHermDrcho(n,S);
        arbol_plano(M,A,A.hijoIzqdo(n),inifila/2+1,finfila,inicol,fincol/2);
      }
    }

  }
}

template <typename T>
Agen<T> Plana(const int& M[][],Agen<T>& A,int k)
{
if(AllBlack(M,0,pow(2,k),0,pow(2,k)))
  {
    A.insertarRaiz(N);
    return A;
  }
  else
  {
    if(AllWhite(M,0,pow(2,k),0,pow(2,k)))
    {
      A.insertarRaiz(B)
    }
    else
    {
    A.insertarRaiz(S);
    arbol_plano(M,A,A.raiz(),0,pow(2,k)-1,0,pow(2,k)-1);
    return A;
    }
  }
}

int main(){
  Agen<tElto> A;
  int k=3;
  int M [pow(2,k)][pow(2,k)]={
    {B,B,B,B,B,B,B,B},
    {B,B,B,B,B,B,B,B},
    {B,B,B,B,N,B,B,B},
    {B,B,N,N,N,B,B,B},
    {N,N,N,N,N,N,B,B},
    {N,N,N,N,N,N,B,B},
    {B,B,B,B,N,N,N,B},
    {B,B,B,B,N,N,N,N}
  };
//B=1,N=0
  Agen<char> A;
  A=Plana(M,A,k);
}
