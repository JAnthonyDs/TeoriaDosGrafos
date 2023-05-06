#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 10005;
const int INF = 0x3f3f3f3f;

vector<pii> adj[MAXN];
int dist[MAXN];
bool vis[MAXN];
int parent[MAXN];
vector<pii> mst;

void prim(int source)
{
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    for (int i = 1; i < MAXN; i++)
    {
        dist[i] = INF;
        vis[i] = false;
        parent[i] = -1;
    }

    dist[source] = 0;
    pq.push(make_pair(0, source));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (vis[u])
            continue;

        vis[u] = true;

        for (auto e : adj[u])
        {
            int v = e.first;
            int w = e.second;

            if (!vis[v] && dist[v] > w)
            {
                dist[v] = w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    for (int i = 2; i <= MAXN; i++)
    {
        if (parent[i] != -1)
        {
            mst.push_back(make_pair(min(i, parent[i]), max(i, parent[i])));
        }
    }
}

int main(int argc, char *argv[])
{
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

    int n, m;
    fin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        fin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    fin.close();

    prim(source);

    if (!(output_file == ""))
    {
        ofstream fout(output_file);
        if (!fout)
        {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }

        std::sort(mst.begin(), mst.end());

        for (int i = 0; i < min((int)mst.size() - 1, m); i++)
        {
            fout << "(" << mst[i].first << "," << mst[i].second << ") ";
        }
        cout << endl;

        fout.close();
    }

    if (show_solution)
    {
        std::sort(mst.begin(), mst.end());

        for (int i = 0; i < min((int)mst.size() - 1, m); i++)
        {
            cout << "(" << mst[i].first << "," << mst[i].second << ") ";
        }
        cout << endl;
    }

    return 0;
}
