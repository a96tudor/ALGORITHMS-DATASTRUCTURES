/**
 *      Program that implements the BFS search in an oriented graph
 *
 *      Determines, for every node X in the graph, the shortest
 *              distance to a source node, S
 */

#include<vector>
#include<fstream>
#include<iostream>
#include<queue>
#include<utility>

#define node first
#define cost second
#define MAX_SIZE 100001
#define iterator vector<int>::iterator
using namespace std;

ifstream fin("bfs.in");
ofstream fout("bfs.out");

queue <pair<int, int> > Q;  // queue used for BFS
vector<int> a[MAX_SIZE];    // adjacency list
int dist[MAX_SIZE];         // array of distances

int S, N;

void BFS() {
    if(Q.empty()) return;
    pair<int, int> x = Q.front();
    Q.pop();
    int NODE = x.node;
    int COST = x.cost;
    // getting to all the neighbours of NODE
    for (iterator it = a[NODE].begin(); it != a[NODE].end(); it++) {
        if (dist[*it] == -1) {
            // it has not been visited yet
            dist[*it] = COST + 1;
            Q.push(make_pair(*it, COST+1));
        }
    }
    BFS();
}

void read_data() {
    // reading data
    int M;
    fin >> N >> M >> S;

    for (int i = 0; i < M; i++ ) {
       int x, y;
        fin >> x >> y;
        a[x].push_back(y);
    }

    // initialising the distances array
    for (int i = 1; i <= N;  i++ ) {
        dist[i] = (i == S) ? 0 : -1;
    }
}

void print_distances() {
    for (int i = 1; i < N; i++)
        fout << dist[i] << " ";
    fout << dist[N] << "\n";
}

int main() {

    read_data();
    Q.push(make_pair(S, 0));
    BFS();
    print_distances();

    fin.close();
    fout.close();
    return 0;
}