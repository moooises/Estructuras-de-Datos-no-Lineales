#include <iostream>
#include <fstream>
#include <algorithm>
#include "agen.h"
#include "agen_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin='#';


int main(){
  Agen<tElto> A;

  cout<<"*** Lectura del arbol A***\n";
  rellenarAgen(A,fin);

  ofstream fs("agen2.dat");
  imprimirAgen(fs,A,fin);
  fs.close();
  cout<<"\n*** Arbol A guardado en fichero age.dat***\n";

  cout<<"\n*** Lectura de arbol A de agen.dat ***\n";
  ifstream fe("agen2.dat");
  rellenarAgen(fe,A);
  fe.close();
  }
