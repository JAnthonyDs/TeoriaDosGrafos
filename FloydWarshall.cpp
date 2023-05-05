#include <iostream>

using namespace std;

#define INFINITO 1000000

int main(){

    int d0[5][5] = {
        {0,3,8,INFINITO,-4},
        {INFINITO,0,INFINITO,1,7},
        {INFINITO,4,0,INFINITO,INFINITO},
        {2,INFINITO,-5,0,INFINITO},
        {INFINITO,INFINITO,INFINITO,6,0}
    }; //valores originais

    int d[5][5] = {
        {0,3,8,INFINITO,-4},
        {INFINITO,0,INFINITO,1,7},
        {INFINITO,4,0,INFINITO,INFINITO},
        {2,INFINITO,-5,0,INFINITO},
        {INFINITO,INFINITO,INFINITO,6,0}
    }; //Menor caminho

    int pi[5][5] = {
        {-1,1,1,-1,1},
        {-1,-1,-1,2,2},
        {-1,3,-1,-1,-1},
        {4,-1,4,-1,-1},
        {-1,-1,0,5,-1}
    }; //Arestas que passa

    //Floyd-Warshall

    for(int k = 0; k < 5; k++){
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                //distância de i para j, passando pelo k
                //i para j, diretamente
                int dij = d[i][j];
                //i para o k
                int dik = d[i][k];
                //k para o j
                int dkj = d[k][j];
                
                
                if( (dik != INFINITO && dkj != INFINITO) && (dij > dik + dkj)){
                        
                    d[i][j] = dik + dkj;
                    pi[i][j] = pi[k][j];
                        
                }
                
                 
            }
        }
    }

    cout << "D0: " << endl;    
    for(int i = 0; i < 5; i++ ){
        for(int j = 0; j < 5 ; j++){
            cout << d0[i][j] << '\t';
        }
        cout << '\n';
    }

    cout << '\n';
    cout << "D: " << endl;
    for(int i = 0; i < 5; i++ ){
        for(int j = 0; j < 5 ; j++){
            cout << d[i][j] << '\t';
        }
        cout << '\n';
    }

    cout << '\n';
    cout << "PI: " << endl;
    for(int i = 0; i < 5; i++ ){
        for(int j = 0; j < 5 ; j++){
            cout << pi[i][j] << '\t';
        }
        cout << '\n';
    }

    return 0;
}