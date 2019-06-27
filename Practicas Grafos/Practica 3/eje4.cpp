#include "alg_grafoPMC.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "particion.cpp"
using namespace std;

int main()
{
  string a="nf.txt";//No me funciona el infinito
  GrafoP<int> g(a);
  cout<<g<<endl;
  GrafoP<int> G=KruskallInv(g);//Esto te lo pide el eje4
  //Esta en alg_grafoPMC.h
  cout<<G<<endl;

}
