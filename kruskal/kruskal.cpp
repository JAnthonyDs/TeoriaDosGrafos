#include <bits/stdc++.h>
using namespace std;

// Creating shortcut for an integer pair
typedef pair<int, int> iPair;

// Structure to represent a graph
struct Graph
{
    int V, E;
    vector<pair<int, iPair>> edges;

    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }

    int kruskalMST(vector<pair<int, int>> &mstPairs, int startVertex);
};

struct DisjointSets
{
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n + 1];
        rnk = new int[n + 1];

        for (int i = 1; i <= n; i++)
        {
            rnk[i] = 0;
            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        if (rnk[x] > rnk[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

int Graph::kruskalMST(vector<pair<int, int>> &mstPairs, int startVertex)
{
    int mst_wt = 0; // Initialize result

    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector<pair<int, iPair>>::iterator it;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {
            mstPairs.push_back({u, v});

            mst_wt += it->first;

            ds.merge(set_u, set_v);
        }
    }

    return mst_wt;
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

    int V, E;
    fin >> V >> E;
    Graph g(V, E);

    int a, b, wt;
    for (int i = 0; i < E; i++)
    {
        fin >> a >> b >> wt;
        g.addEdge(a, b, wt);
    }

    fin.close();

    vector<pair<int, int>> mstPairs;

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
            int mst_wt = g.kruskalMST(mstPairs, startVertex);

            for (const auto &pair : mstPairs)
            {
                fout << "(" << pair.first << "," << pair.second << ") ";
            }
            fout << endl;
        }
        else
        {
            int mst_wt = g.kruskalMST(mstPairs, startVertex);
            fout << mst_wt << endl;
        }

        fout.close();
    }

    if (show_solution)
    {
        int mst_wt = g.kruskalMST(mstPairs, startVertex);

        for (const auto &pair : mstPairs)
        {
            cout << "(" << pair.first << "," << pair.second << ") ";
        }
        cout << endl;
    }
    else
    {
        int mst_wt = g.kruskalMST(mstPairs, startVertex);
        cout << mst_wt << endl;
    }


    return 0;
}
