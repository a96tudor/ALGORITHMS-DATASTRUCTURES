/**
 *      Topological Sort for an acyclic, oriented graph
 *
 *      Created by Tudor Avram on 23/11/16.
 */

#include<vector>
#include<cstdio>
#include<queue>

#define V_MAX 50001
#define pb push_back
using namespace std;

vector<int> G[V_MAX];
queue<int> Q;

bool used[V_MAX];
int deg[V_MAX];

void Solve() {

    if (Q.empty()) {
        // we are done
        printf("\n");
        return;
    }

    int node = Q.front();

    printf("%d ",node);

    for (int dest : G[node]) {
        deg[dest]--;
        if (!used[dest] && deg[dest] == 0) {
            used[dest] = true;
            Q.push(dest);
        }
    }

    Q.pop();
    Solve();
}

void read_data() {
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        G[x].pb(y);
        deg[y]++;
    }
    for (int i = 1; i <= N; i++ ){
        if (deg[i] != 0) {
            used[i] = false;
        } else {
            Q.push(i);
            used[i] = false;
        }
    }
}

int main() {
    freopen("sortaret.in", "r", stdin);
    freopen("sortaret.out", "w", stdout);

    read_data();
    Solve();

    fclose(stdin);
    fclose(stdout);
    return 0;
}

