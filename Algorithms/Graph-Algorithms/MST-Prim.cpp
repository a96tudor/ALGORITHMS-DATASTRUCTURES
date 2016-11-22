/**
 *      MST implementation using Prim's algorithm
 *
 * Created by Tudor Avram on 22/11/16.
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include<set>
#include<cstdio>

#define iterator vector< pair<int, int> >::iterator
#define MAX_SIZE 200001
#define INF ~(1<<31)
#define pairs pair<int, int>
using namespace std;

vector< pairs > G[MAX_SIZE];
vector< pairs > SOL;
multiset< pairs > H;

bool visited[MAX_SIZE];
int D[MAX_SIZE], F[MAX_SIZE];

/*ifstream fin("apm.in");
ofstream fout("apm.out");
*/

void print_results(int cost) {
    printf("%d\n%d\n",cost,SOL.size());
    for (iterator it = SOL.begin(); it != SOL.end(); it++)
       printf("%d %d\n",(*it).first,(*it).second);
}

int solve() {
    int total = 0;
    while (!H.empty()) {
        pairs x = *(H.begin());
        int cost = x.first;
        int node = x.second;
        H.erase(H.begin());
        if (F[node] != 0) {
            SOL.push_back(make_pair(F[node], node));
        }
        visited[node] = true;
        total += cost;
        for(iterator it = G[node].begin(); it != G[node].end(); it++) {
            x = *it;
            if (!visited[x.first] && x.second < D[x.first]) {
                if (D[x.first] != INF) {
                    // it has already been visited, so we need to replace it in the multiset
                    H.erase(H.find(make_pair(D[x.first], x.first)));
                }
                D[x.first] = x.second;
                H.insert(make_pair(x.second, x.first));
                F[x.first] = node;
            }
        }
    }
    return total;
}

void read_data() {
    freopen("apm.in","r",stdin);
    freopen("apm.out","w",stdout);

    int N, M;
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= M; i++) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        G[x].push_back(make_pair(y, c));
        G[y].push_back(make_pair(x, c));
    }

    for (int i = 1; i <= N; i++) {
        visited[i] = false;
        D[i] = INF;
    }

    D[1] = 0;
    H.insert(make_pair(0, 1));
}

int main() {

    read_data();
    int total_cost = solve();
    print_results(total_cost);

    fclose(stdin);
    fclose(stdout);
    return 0;
}