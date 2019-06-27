#ifndef ABIN_ALT_H
#define ABIN_ALT_H
#include <cassert>
#include <cmath>
#include <algorithm>

using namespace std;

template <typename T> class Abin_Alt
{

struct celda;

public:
typedef int nodo;
static const nodo NODO_NULO;
Abin_Alt(size_t altura);
void insertarRaizB(const T& e);
void insertarHijoIzqdoB(nodo n,const T& e);
void insertarHijoDrchoB(nodo n,const T& e);
void eliminarHijoIzqdoB(nodo n);
void eliminarHijoDrchoB(nodo n);
void eliminarRaizB();
~Abin();
bool arbolVacioB() const;
const T& elemento(nodo n);
T& elemento(nodo n);
nodo raizB() const;
nodo padreB() const;
nodo hijoIzqdoB(nodo n) const;
nodo hijoDrchoB(nodo n) const;
Abin(const Abin<T>& a);

private:
  struct celda {
  T elto;
  };



celda* nodos;
int maxNodos;
int numNodos;
int alt;

void destruirNodos(nodo& n);
}

template <typename T>
const typename Abin_Alt<T>::nodo Abin_Alt<T>::NODO_NULO(-1);

template <typename T>
inline Abin_Alt<T>::Abin_Alt(size_t altura): nodos( new celda[pow(2,altura)-1]),maxNodos(pow(2,altura)-1),numNodos(0),alt(altura)
{
  for(int i=0;i<(pow(2,altura)-1);++i){
    nodos[i]=NODO_NULO;
  }
}

template <typename T>
void Abin_Alt<T>::insertarRaizB(const T& e)
{
  assert(numNodos==0);
  assert(maxNodos/2==NODO_NULO);

  numNodos=1;
  nodos[maxNodos/2].elto=e;

}

template <typename T>
void Abin_Alt<T>::insertarHijoIzqdoB(Abin_Alt<T>::nodo n,const T& e)
{
    assert(numNodos<maxNodos);
    assert(n>=0 && n<numNodos);
    nodo pos=(n/2)-1;
    assert(pos>=0);
    nodos[pos].elto=e;

}

template <typename T>
void Abin_Alt<T>::insertarHijoDrchoB(Abin_Alt<T>::nodo n,const T& e)
{
    assert(numNodos<maxNodos);
    assert(n>=0 && n<numNodos);
    nodo pos=(n/2)+n+1;
    assert(pos<maxNodos);
    nodos[pos].elto=e;

}


template <typename T>
int Abin_Alt<T>::ProfunidadB(Abin_Alt<T>::nodo n,int inic=0,int fin=maxNodos){
  int mitad=(inic+fin)/2;
  if n==mitad return 0;
  else{
    if n<mitad return 1+ProfundidadB(n,inic,mitad-1);
    else return 1+ProfundidadB(n,mitad+1,fin);
  }
}

/**
template <typename T>
int Abin_Alt<T>::ProfundidadB(Abin_Alt<T>::nodo n,Abin_Alt<T>::nodo referente)
{
  if(n==referente) return 0;
  else{
    if(n==NODO_NULO)return -alt;
    else return 1+max(ProfundidadB(n,n/2),ProfundidadB(n,(n/2)+(maxNodos/2)+1));
  }
}
*/

template <typename T>
inline typename Abin_Alt<T>::nodo Abin_Alt<T>::padreB(Abin_Alt<T>::nodo n)const
{
  int raiz=maxnodos/2;
  assert(n!=raiz);
  if(n<raiz)return n+(maxNodos+1)/(pow(2,ProfundidadB(n,raiz)));
  else return n-(maxNodos+1)/(pow(2,ProfundidadB(n,raiz)));
}


/**
template <typename T>
void Abin_Alt<T>::insertarHijoIzqdoB(Abin_Alt<T>::nodo n,const T& e)
{
  assert(n>=0 && n<numNodos);
  assert(nodos[n].hizq==NODO_NULO);
  assert(numNodos<maxNodos);

  nodos[n].hizq=n/2;
  nodos[(n/2)-1].elto=e;
  nodos[(n/2)-1].padre=n;
  nodos[(n/2)-1].hizq=NODO_NULO;
  nodos[(n/2)-1].hder=NODO_NULO;
  numNodos++;
}

template <typename T>
void Abin_Alt<T>::insertarHijoDrchoB(Abin_Alt<T>::nodo n,const T& e)
{
  assert(n>=0 && n<numNodos);
  assert(nodos[n].hder==NODO_NULO);
  assert(numNodos<maxNodos);

  nodos[n].hder=n/2+n;
  nodos[(n/2+n)+1].elto=e;
  nodos[(n/2+n)+1].padre=n;
  nodos[(n/2+n)+1].hizq=NODO_NULO;
  nodos[(n/2+n)+1].hder=NODO_NULO;
  numNodos++;
}

template <typename T>
void Abin_Alt<T>::eleminarHijoIzqdoB(Abin_Alt<T>::nodo n)
{
  nodo hizqdo;
  assert(n>=0 && n<numNodos);
  hizqdo=nodos[n].hizq;
  assert(hizqdo!=NODO_NULO);
  assert(nodos[hizqdo].hizq==NODO_NULO && nodos[hizqdo].hder==NODO_NULO);

  nodos[n].hizq=NODO_NULO;
  nodos[(n/2)-1]=NODO_NULO;
  numNodos--;


}

template <typename T>
void Abin_Alt<T>::elemtoHijoDrchoB(Abin_Alt<T>::nodo n)
{
  nodo hdrcho;
  assert(n>=0 && n<numNodos);
  hdrcho=nodos[n].hder;
  assert(hdrcho!=NODO_NULO);
  assert(nodos[hdrcho].hizq==NODO_NULO && nodos[hdrcho].hder==NODO_NULO);

  nodos[n].hder=NODO_NULO;
  nodos[(n/2)+n+1]
}

template <typename T>
inline void Abin_Alt<T>::eliminarRaizB()
{
  assert(numNodos==1);
  numNodos=0;
  nodos[maxNodos/2]=NODO_NULO;
}

template <typename T>
inline Abin_Alt<T>::~Abin_Alt()
{
  delete[] nodos;
}

template <typename T>
inline bool Abin_Alt<T>::arbolVacioB() const{
  return (numNodos==0);
}

template <typename T>
inline const T& Abin_Alt<T>::elemento(Abin_Alt<T>::nodo n) const
{
  assert(n>=0 && n<numNodos);
  return nodos[n].elto;
}

template <typename T>
inline T& Abin_Alt<T>::elemento(Abin_Alt<T>::nodo n)
{
  assert(n>=0 && n<numNodos);
  return nodos[n].elto;
}

template <typename T>
inline typename Abin_Alt<T>::nodo Abin_Alt<T>::raizB() const
{
  return (numNodos>0) ? maxNodos/2: NODO_NULO;
}

template <typename T>
inline typename Abin_Alt<T>::nodo Abin_Alt<T>::padreB(Abin_Alt<T>::nodo n)const
{
assert(n>=0 && n<numNodos);
return nodos
}
*/
