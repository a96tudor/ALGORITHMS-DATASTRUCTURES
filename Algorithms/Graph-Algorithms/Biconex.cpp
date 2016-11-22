/**
 *      Program that separates a given graph into biconex components
 *
 *       BICONEX COMPONENT = sub-graph that has no joint-points
 *          (i.e. any node can be removed and the sub-graph would
 *                  still be connected)
 *
 * Created by Tudor Avram on 22/11/16.
*/

#include<vector>
#include<cstdio>
#include<stack>
#include<utility>
#include<algorithm>

#define V_MAX 100001
#define E_MAX 200001
#define pb push_back
#define iterator vector<int>::iterator
#define mp make_pair
#define pair_ints pair<int, int>
using namespace std;

stack < pair_ints > STK;
vector<int> G[V_MAX];
vector<int> cop;
vector< vector<int> > SOL;

int F[V_MAX], low[V_MAX], lvl[V_MAX], a[V_MAX];
bool used[V_MAX];
int cnt;

void print_results() {
    printf("%d\n", SOL.size());
    for (int i=0;i<SOL.size();++i) {
        for (iterator it = SOL[i].begin(); it != SOL[i].end(); it++)
            printf("%d ",*it);
        printf("\n");
    }
}

void ins(int node, int lvl) {
    if (a[node] == lvl) return;
    cop.pb(node);
    a[node] = lvl;
}

void load_solution(int node, int father, int count) {
    cop.clear();
    int x,y;
    do {
        x = STK.top().first;
        y = STK.top().second;
        STK.pop();
        ins(x, count); ins(y, count);
    } while (x!=node && y!=father);
    SOL.pb(cop);
}

void DFS(int node, int k) {
    lvl[node] = low[node] = k;
    used[node] = true;
    for (iterator it = G[node].begin(); it != G[node].end(); it++) {
        if (!used[*it]) {
            used[*it] = true; F[*it] = node; STK.push(mp(node, *it));
            DFS(*it, k+1);
            low[node] = min(low[node], low[*it]); cnt++;
            if (low[*it] >= lvl[node]) {
                // we have a joint-point
                load_solution(node, F[node], cnt);
            }
        } else {
            low[node] = min(low[node], lvl[*it]);
        }
    }
}

void Solve(int N) {
    for (int i = 1; i <= N; i++) {
        if (!used[i]) {
            DFS(i,1);
        }
    }
}

void read_data(int &N) {
    int M;
    scanf("%d%d", &N, &M);

    for(int i = 1; i <= M; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].pb(y);
        G[y].pb(x);
    }

    for (int i = 1; i <= N; i++) {
        F[i] = 0;
        used[i] = false;
    }
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
