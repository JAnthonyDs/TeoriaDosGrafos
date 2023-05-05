#include <iostream>

#include <queue>

using namespace std;

#define INFINITO 1000000

class Vertice{
    public:
        int node;
        int peso;

    Vertice(int node, int peso){
        this->node = node;
        this->peso = peso;
    }

    int getNode(){
        return node;
    }

    int getPeso(){
        return peso;
    }
};

struct CompPeso{
    bool operator()(Vertice& v0, Vertice& v1)
    {
        return v0.getPeso() > v1.getPeso();
    }
};

int main(){
    int v0 = 0;

    int n = 6;

    //exemplo de grafo
    //0 1 2
    //0 2 1
    //1 3 1
    //2 3 3
    //2 4 4
    //3 5 2
    //4 5 2

    int grafo[6][2] = {
        {1,2}, //0 se liga a 1 e 2
        {3,4}, //1 se liga a 3
        {3,4}, //2 se liga a 3 e 4
        {5}, //3 se liga a 5
        {5} //4 se liga a 5
    };

    //função de pesos - w
    int w[n][n];

    w[0][1] = 4; //aresta 0 para 1 tem peso 2
    w[0][2] = 5; //aresta 0 para 2 tem peso 1
    w[1][3] = 6; //aresta 1 para 3 tem peso 1
    w[1][4] = 1;
    w[2][3] = 3;
    w[2][4] = 9;
    w[3][5] = 4;
    w[4][5] = 6;
    //

    priority_queue<Vertice, vector<Vertice>, CompPeso> h; //lista de prioridade mínima de vértices

    // Vertice va(0,0), v1(1,2), v2(2,1);

    // h.push(v1);
    // h.push(v2);

    // Vertice v_top = h.top();

    // cout << "Vértice: " << v_top.getNode() << " Dist: " << v_top.getPeso() << endl;

    int dist[n];
    int prev[n];

    for(int i = 0; i<n;i++){
        dist[i] = INFINITO;
        prev[i] = -1;
    }

    dist[v0] = 0;

    //Adiciona os valores da dist na fila de prioridades
    for(int j=0;j < 6; j++){
        // Vertice va(j,dist[j]);
        Vertice va(j,INFINITO);
        h.push(va);
    }

    h.pop();
    Vertice va(0,0);
    h.push(va);

    // int tamArraey = sizeof grafo[0]/ sizeof grafo[0][0];  tamanho do array?
    int cont = 0;

    while (cont < 6){
        Vertice v = h.top(); //Pega o primeiro da fila e remove
        int u = v.node;
        h.pop();
        //percorre os vizinhos de u
        for(int i = 0; i < 2; i++){
            int v = grafo[u][i]; // vizinho de u
            if(dist[v] > dist[u] + w[u][v]){
                dist[v] = dist[u] + w[u][v];
                prev[v] = u;

                // h.erase(vec.end() - 1); remove o último
                Vertice va(v,dist[v]);
                h.push(va);

            }

        }
        cont++;  
    }

    
    for(int i = 0; i < 6; i++){
        cout << i << " : "<<dist[i] << endl;
    }

    cout << endl;

    for(int i = 0; i < 6; i++){
        cout << i << " : "<<prev[i] << endl;
    }

    return 0;

}