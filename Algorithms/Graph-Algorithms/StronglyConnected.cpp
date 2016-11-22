/**
 *      Program that separates a given oriented graph into strongly connected components
 *
 *       STRONGLY CONNECTED COMPONENT = sub-graph with the following property : whatever vertices u and v,
 *                  there exists a path both from u to v and from v to u
 *
 *       Note : implements Tarjan's algorithm :
 *                 https://en.wikipedia.org/wiki/Tarjan's_strongly_connected_components_algorithm
 *       Complexity : O(V+E)
 *
 * Created by Tudor Avram on 22/11/16.
*/

#include<vector>
#include<cstdio>
#include<stack>
#include<algorithm>

#define V_MAX 100010
#define pb push_back
using namespace std;

vector<int> G[V_MAX], cop;
vector< vector<int> > SOL;
stack<int> STK;

bool used[V_MAX];
int lvl[V_MAX], low[V_MAX], on_stack[V_MAX];
int ind;

void print_results() {
    printf("%d\n", SOL.size());
    for (vector<int> component : SOL) {
        for (int v : component)
            printf("%d ", v);
        printf("\n");
    }
}


void strong_connect(int v) {
    lvl[v] = ind; low[v] = ind; ind++;
    STK.push(v); on_stack[v] = true;
    used[v] = true;

    for (int w : G[v]) {
        if (!used[w]) {
            strong_connect(w);
            low[v] = min(low[v], low[w]);
        } else if (on_stack[w]) {
            low[v] = min(low[v], lvl[w]);
        }
    }

    if (lvl[v] == low[v]) {
        cop.clear();
        int w;
        do {
            w = STK.top();
            STK.pop();
            on_stack[w] = false;
            cop.pb(w);
        } while(w != v);
        SOL.pb(cop);
    }
}

void Solve(int N) {
    ind = 0;
    for (int i = 1; i <= N; i++) {
        if (!used[i]) {
            strong_connect(i);
        }
    }
}

void read_data(int &N) {
    int M;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].pb(y);

    }
    for (int i = 1; i <= N; i++)
        used[i] = false;
}

int main() {
    int N;
    read_data(N);
    Solve(N);
    print_results();

    fclose(stdin);
    fclose(stdout);
    return 0;
}