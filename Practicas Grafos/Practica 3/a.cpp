template <typename tCoste>
void tombuctu3(vector<std::pair<size_t,size_t>> coordenadas, const matriz<bool> carreteras)
{
typedef typename GrafoP<tCoste>::vertice v;
GrafoP<tCoste> archipielago(carreteras.dimension());
//ahora hay que ver, cuantas islas tenemos
//a la vez que lo hago, voy a reflejar el archipielago en una amtriz de costes..
int nIslas = carreteras.dimension();
Particion islas(carreteras.dimension());
for(v i = 0;i < carreteras.dimension() ; i++)
for(v j = i+1 ;j < carreteras.dimension() ; j++)
{
archipielago[i][j] = archipielago[j][i] = pitagoras(coordenadas[i].first,coordenadas[i].second,coor​denadas[j].first,coordenadas[j].second);​
if(carreteras[i][j] && (islas.encontrar(i) != islas.encontrar(j)) )
{
islas.unir(islas.encontrar(i),islas.encontrar(j));
nIslas--;
}
}

matriz<lineaAerea<tCoste>> lineasAereas(nIslas);
vector<v> representantes;
for(v i = 0; i < carreteras.dimension() ; i++)
if( std::find(representantes.begin(),representantes.end(),islas.encontrar(i)) == representantes.end() )
representantes.push_back(islas.encontrar(i));
//ya tenemos una lista con los representantes de cada una de las islas
//el indice de el vector, será cada una de las islas..
v i1,i2;
//ahora vamos a unir las islas de la forma mas eficiente
for(v i = 0;i < archipielago.numVert() ; i++)
for(v j = i+1 ;j < archipielago.numVert() ; j++)
if(islas.encontrar(i) != islas.encontrar(j))
{//son de distintas islas..
i1 = std::distance(representantes.begin(), std::find(representantes.begin(),representantes.end(),islas.encontrar(i))) -1;
i2 = std::distance(representantes.begin(), std::find(representantes.begin(),representantes.end(),islas.encontrar(j))) -1;
if(archipielago[i][j] < lineasAereas[i1][i2].coste)
lineasAereas[i1][i2] = lineaAerea<tCoste>(i,j,archipielago[i][j]);
}
}
