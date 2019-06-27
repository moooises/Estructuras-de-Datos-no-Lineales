#include "alg_grafoPMC.h"
#include "alg_grafoP_E-S.h"
#include <stdlib.h>

size_t N; // va a ser una laberinto de 3 x 3casillas
typedef typename GrafoP<size_t>::vertice vertice;

struct casilla
{
    vertice x;
    vertice y;
    casilla(vertice x_ = 0, vertice y_ = 0) : x(x_), y(y_){}
    bool operator ==(casilla b){return (this->x == b.x) && (this->y == b.y);  }
};

struct pared
{
    casilla uno;
    casilla dos;
    pared(casilla uno_=casilla(0,0), casilla dos_=casilla(0,0)): uno(uno_), dos(dos_){}
    bool operator ==(pared b){return (this->uno == b.uno) && (this->dos == b.dos);  }

};

casilla verticeToCasilla(const vertice v)
{
    casilla c;

    c.x = v/N;
    c.y = v%N;

    return c;
}

vertice casillaToVertice(const casilla c)
{
    vertice v;

    v = c.x*N + c.y;

    return v;
}

bool esAdyacente(const vertice a, const vertice b )
{
    casilla uno, dos;

    uno = verticeToCasilla(a);
    dos = verticeToCasilla(b);

    return ( abs(uno.x-dos.x) + abs(uno.y-dos.y) ) == 1;
}

typename GrafoP<size_t>::tCamino calcularCamino(GrafoP<size_t> &G, const Lista<pared> &L, const casilla entrada, const casilla salida, size_t &len)
{
    casilla a, b;
    vector<size_t> vCosteMin(G.numVert());
    vector<size_t> vCaminMin(G.numVert());

    typename GrafoP<size_t>::tCamino camin;

    for(vertice i = 0; i<G.numVert(); i++)
    {
        a= verticeToCasilla(i);
        for(vertice j = 0; j<G.numVert(); j++)
        {
            b= verticeToCasilla(j);
            if(esAdyacente(i,j) && L.buscar(pared(a,b))== L.fin() )
                G[i][j] = 1;
            else
                if( i == j)
                  G[i][j] = 0;
                else
                    G[i][j] = GrafoP<size_t>::INFINITO;
        }
    }

    vCosteMin = Dijkstra(G, casillaToVertice(entrada), vCaminMin);

    camin = camino<size_t>(casillaToVertice(entrada), casillaToVertice(salida), vCaminMin);

    len = vCosteMin[casillaToVertice(salida)];

    return camin;


}
