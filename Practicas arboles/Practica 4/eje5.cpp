#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cassert>


#include "ABB.h"

template <typename T>
void mostrarhijosderch(const Abb<T>& A,T t);

template <typename T>
void mostrarhijosizq(const Abb<T>& A,T t);

using namespace std;

template <typename T>
void rellenar1(Abb<T>& A){
  for(int i=5;i<=10;++i)
  {
    A.insertar(i);
  }
  for(int i=0;i<5;++i)
  {
    A.insertar(i);
  }
}

template <typename T>
void rellenar2(Abb<T>& A)
{
  for(int i=5;i<=10;++i)
  {
    A.insertar(i);
  }
  for(int i=11;i<15;++i)
  {
    A.insertar(i);
  }
}

template <typename T>
void mostrarhijosizq(const Abb<T>& A,T t)
{
  if(!A.vacio())
  {
    cout<<"Hijo izquierdo de "<<t<<": "<<A.elemento()<<endl;
    mostrarhijosizq(A.izqdo(),A.elemento());
    mostrarhijosderch(A.drcho(),A.elemento());
  }
}

template <typename T>
void mostrarhijosderch(const Abb<T>& A,T t)
{
  if(!A.vacio())
  {
    cout<<"Hijo derecho de "<<t<<": "<<A.elemento()<<endl;
    mostrarhijosizq(A.izqdo(),A.elemento());
    mostrarhijosderch(A.drcho(),A.elemento());
  }
}

template <typename T>
void mostrar(const Abb<T>& A)
{
  cout<<"Raiz del Arbol: "<<A.elemento()<<endl;
  mostrarhijosizq(A.izqdo(),A.elemento());
  mostrarhijosderch(A.drcho(),A.elemento());
}

template <typename T>
void inorden(vector<T>& v,const Abb<T>& A)
{
  if(!A.vacio())
  {
  v.push_back(A.elemento());
  inorden(v,A.izqdo());
  inorden(v,A.drcho());
  }
}


template <typename T>
void equilibrar(Abb<T>& B,vector<T>& v,int ini,int fin)
{
  if(ini!=fin)
  {
    int pos=ini+((fin-ini)/2);
/**  cout<<"Inicio: "<<ini<<endl;
  cout<<v[pos]<<" Pos: "<<pos<<endl;
  cout<<"Fin: "<<fin<<endl;*/
      B.insertar(v[pos]);
      equilibrar(B,v,ini,pos);
      equilibrar(B,v,pos+1,fin);
    }


}


template <typename T>
Abb<T> AVL(vector<T> v)
{
  sort(v.begin(),v.end());
  Abb<T> B;
  //cout<<"KK"<<endl;
  //for(int i=0;i<v.size();++i)cout<<v[i]<<endl;
  //cout<<"QQ"<<endl;
//cout<<v.size()<<endl;
  equilibrar(B,v,0,v.size());
  return B;
}

int main(){
  Abb<int> A,B,C;
  rellenar1(A);
  mostrar(A);
  cout<<endl;
  rellenar2(B);
  mostrar(B);
  cout<<endl;
  vector<int> v1,v2,v;
  inorden(v1,A);
  inorden(v2,B);
  sort(v1.begin(),v1.end());
  sort(v2.begin(),v2.end());
  set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));

  //cout<<11/2<<endl;=5
  C=AVL(v);
  mostrar(C);
}
