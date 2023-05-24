#include <bits/stdc++.h>
using namespace std;

bool comparePairs(const pair<int, int> &a, const pair<int, int> &b)
{
    if (a.first != b.first)
    {
        return a.first < b.first;
    }
    else
    {
        return a.second < b.second;
    }
}

pair<vector<pair<int, int>>, int> prim(vector<pair<int, int>> adj[], int N, int startVertex)
{
    vector<pair<int, int>> result; // Vetor para armazenar os pares (vértice, pai)

    int parent[N + 1];
    int key[N + 1];
    bool mstSet[N + 1];

    for (int i = 1; i <= N; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[1] = 0;
    parent[1] = -1;
    pq.push({0, 1});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        mstSet[u] = true;

        for (auto it : adj[u])
        {
            int v = it.first;
            int weight = it.second;
            if (mstSet[v] == false && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    int totalCost = 0;
    for (int i = 2; i <= N; i++)
    {
        result.push_back(make_pair(i, parent[i]));
        totalCost += key[i];
    }

    return make_pair(result, totalCost);
}

int main(int argc, char *argv[])
{
    string input_file = "";
    string output_file = "";
    bool show_solution = false;
    int startVertex = 1;

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
            startVertex = atoi(argv[++i]);
        }
    }

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

    int N, m;
    fin >> N >> m;
    vector<pair<int, int>> adj[N + 1];

    int a, b, wt;
    for (int i = 0; i < m; i++)
    {
        fin >> a >> b >> wt;
        adj[a].push_back(make_pair(b, wt));
        adj[b].push_back(make_pair(a, wt));
    }

    fin.close();

    pair<vector<pair<int, int>>, int> result = prim(adj, N, startVertex);

    vector<pair<int, int>> pairsArray = result.first; // Extrair os pares do vetor result

    sort(pairsArray.begin(), pairsArray.end(), comparePairs); // Ordenar o vetor de pares

    if (!(output_file == ""))
    {
        ofstream fout(output_file);
        if (!fout)
        {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }
        if (show_solution)
        {
            for (auto it : pairsArray)
                fout << "(" << it.second << "," << it.first << ") ";
        }
        else
        {
            fout << " " << result.second << endl;
        }

        fout.close();
    }

    if (show_solution)
    {
        for (auto it : pairsArray)
            cout << "(" << it.second << "," << it.first << ") ";
    }
    else
    {
        cout << " " << result.second << endl;
    }

    return 0;
}

//CUSTO DO PRIM DA AGM, SE N COLOCAR O -S.
//KRUSKAL ==
//BOTAR OS BINARIOS NA PASTA BAT1 E RODAR O BAT1.SH
//./bat1.sh
