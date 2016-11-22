/**
 *      Program that implements the DFS search in an unoriented graph
 *
 *      It retunrs the number of connex components that can be found in the graph
 */

#include <vector>
#include <fstream>
#include <iostream>

#define iterator vector<int>::iterator
#define MAX_SIZE 100001
using namespace std;

ifstream fin("dfs.in");
ofstream fout("dfs.out");

vector<int> G[MAX_SIZE];
bool visited[MAX_SIZE];

void DFS(int node) {
    visited[node] = true;

    for (iterator it = G[node].begin(); it != G[node].end(); it++){
        if (!visited[*it]) {
            DFS(*it);
        }
    }
}

void solve(int N) {
    int components = 0;

    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            DFS(i);
            components++;
        }
    }

    fout << components << "\n";
}

void read_data(int &N) {
    int M;
    fin >> N >> M;

    for (int i = 0; i <M; i++) {
        int x,y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    for (int i = 1; i <= N; i++)
        visited[i] = false;
}

int main() {

    int N;
    read_data(N);
    solve(N);

    fin.close();
    fout.close();
    return 0;
}
