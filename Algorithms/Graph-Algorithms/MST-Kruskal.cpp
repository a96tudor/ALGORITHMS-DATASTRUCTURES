/**
 *      MST implementation using Kruskal's algorithm
 *
 * Created by Tudor Avram on 22/11/16.
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX_SIZE 200001
#define pairs pair<int, int>
#define pairs_iterator vector< pair<int, int> >::iterator
#define edge_iterator vector<edge>::iterator
using namespace std;

// datastructure representing an edge (x, y) with an associated cost of c
struct edge{int x, y, c;};

vector<edge> G;
vector<pairs> SOL;

int r[MAX_SIZE], F[MAX_SIZE];

bool cmp(edge x, edge y) {return (x.c < y.c);}

void print_results(int cost) {
    printf("%d\n%d\n",cost,(int) SOL.size());
    for (pairs_iterator it = SOL.begin(); it != SOL.end(); it++)
        printf("%d %d\n",(*it).first,(*it).second);
}

void merge(int x, int y) {
    if (r[x]<r[y]) F[x] = y;
    else {
        F[y] = x;
        if (r[x] == r[y]) r[x]++;
    }
}

int find_set(int node) {
    if (F[node] != node) F[node] = find_set(F[node]);
    return F[node];
}

int Solve() {
    int cost = 0;
    sort(G.begin(), G.end(), cmp);

    for (edge_iterator it = G.begin(); it != G.end(); it++) {
        edge current = *it;
        int set_X = find_set(current.x);
        int set_Y = find_set(current.y);
        if (set_X != set_Y) {
            // we add the edge to the MST
            merge(set_X, set_Y);    // we merge the two sets
            cost += current.c;
            SOL.push_back(make_pair(current.x, current.y));
        }
    }
    return cost;
}

void read_data() {
    freopen("apm.in","r",stdin);
    freopen("apm.out","w",stdout);

    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1;  i <= M; i++) {
        edge e;
        scanf("%d%d%d", &e.x, &e.y, &e.c);
        G.push_back(e);
    }

    for (int i = 1; i <= N; i++ ) {
        F[i] = i;
        r[i] = 0;
    }
}

int main() {

    read_data();
    int cost = Solve();
    print_results(cost);

    fclose(stdin);
    fclose(stdout);
    return 0;
}