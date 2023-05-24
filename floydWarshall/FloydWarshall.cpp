#include <iostream>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

#define INFINITO 1000000

int main(int argc, char *argv[]){
    string input_file = "";
    string output_file = "";
    bool show_solution = false;
    int source = 1;
    // Parsing command line arguments
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução (em ordem crescente)" << endl;
            cout << "-i: vértice inicial (para o algoritmo de Prim)" << endl;
                return 0;
        }
        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1)
        {
            output_file = argv[++i];
        }
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1)
        {
            input_file = argv[++i];
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            show_solution = true;
        }
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1)
        {
            source = atoi(argv[++i]);
        }
    }

    // If no input file is specified, exit the program.
    if (input_file == "")
    {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin)
    {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    

    fin.close();

    if (!(output_file == ""))
    {
        ofstream fout(output_file);
        if (!fout)
        {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }

        fout.close();
    }

    
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

    //Algoritmo de Floyd-Warshall

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
