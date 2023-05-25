#include <bits/stdc++.h>
#include <limits.h>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

void Bellman(vector<vector<int>> Grafo, int n, int writeN, std::string arName, int src)
{
  vector<int> dist(n, INT_MAX);
  dist[src - 1] = 0;
  for (int i = 0; i < n; i++)
  {
    for (auto e : Grafo)
    {
      int u = e[0];
      int v = e[1];
      int w = e[2];
      if (dist[u] != INT_MAX && ((dist[u] + w) < dist[v]))
      {
        dist[v] = dist[u] + w;
      }
    }
  }
  int counter = 1;

  std::vector<std::string> write(n);

  for (auto i : dist)
  {
    write[counter - 1] = std::to_string(counter) + ":" + std::to_string(i);
    cout << counter << ":" << i << " ";
    counter++;
  }
  cout << endl;
  if (writeN != 0)
  {
    std::ofstream arquivo(arName);
    if (arquivo.is_open())
    {
      for (int i = 0; i < n - 1; i++)
      {
        arquivo << write[i] << "\n";
      }
      arquivo.close();
      std::cout << "Array escrita no arquivo com sucesso.\n";
    }
    else
    {
      std::cout << "Não foi possível criar o arquivo.\n";
    }
  }
}

void help()
{

  cout << "-h : mostra o help" << endl;
  cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
  cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
  cout << "-i : vértice inicial (para o algoritmo de Prim)" << endl;
}

int main(int argc, char const *argv[])
{

  int write = 0, file = 0, src = 0;
  std::string arName;
  std::string inputFile;

  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-h") == 0)
    {
      help();
    }
    else if (strcmp(argv[i], "-o") == 0)
    {
      write = 1;
      arName = argv[i + 1];
    }
    else if (strcmp(argv[i], "-f") == 0)
    {
      inputFile = argv[i + 1];
      file = 1;
    }
    else if (strcmp(argv[i], "-i") == 0)
    {
      src = std::stoi(argv[i + 1]);
    }
  }

  if (file != 1)
  {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> Grafo;
    for (int i = 0; i < m; i++)
    {
      int u, v, w;
      cin >> u >> v >> w;
      u--, v--;
      Grafo.push_back({u, v, w});
      Grafo.push_back({v, u, w});
    }

    if (src == 0)
    {
      src = 1;
    }

    Bellman(Grafo, n, write, arName, src);
  }
  else
  {
    std::ifstream arquivo(inputFile);
    int n, m;
    arquivo >> n >> m;

    vector<vector<int>> Grafo;
    for (int i = 0; i < m; i++)
    {
      int u, v, w;
      arquivo >> u >> v >> w;
      u--, v--;
      Grafo.push_back({u, v, w});
      Grafo.push_back({v, u, w});
    }

    if (src == 0)
    {
      src = 1;
    }

    Bellman(Grafo, n, write, arName, src);
  }
}