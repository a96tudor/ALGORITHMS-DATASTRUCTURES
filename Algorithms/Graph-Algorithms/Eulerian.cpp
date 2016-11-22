/**
 *      Program that determines wether a given multigraph
 *   is eulerian or not. Prints :
 *
 *              (a) A nodes sequence that determines the
 *              eulerian cycle if it is one
 *              (b) -1 if it is not
 *
 *       EUCLIDIAN CYCLE  = a cycle where every edge
 *                  is visited only once
 *
 * Created by Tudor Avram on 22/11/16.
*/

#include<cstdio>
#include<vector>

#define N_MAX 100001
#define pb push_back
#define iterator vector<int>::iterator
#define mp make_pair
using namespace std;

vector<int> G[N_MAX];
vector<int> Q;
pair<int, int> edges[500001];

bool seen[500001];

void Solve() {

    while (!Q.empty()) {
        int src = Q.back();
        if (G[src].empty()) {
            Q.pop_back();
            printf("%d ", src);
        } else {
            int e = G[src].back();
            G[src].pop_back();
            if (!seen[e]) {
                seen[e] = true;
                if (edges[e].first == src) {
                    Q.pb(edges[e].second);
                } else {
                    Q.pb(edges[e].first);
                }
            }
        }
    }

}

bool read_data() {
    int N, M;
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= M; i++) {
        int x,y;
        scanf("%d%d", &x, &y);
        edges[i] = mp(x,y); seen[i] = false;
        G[x].pb(i);
        G[y].pb(i);
    }

    for (int i = 1; i <= N; i++) {
        if (G[i].size() % 2 == 1) {
            // we can't have a Eulerian cycle
            return false;
        }
    }
    return true;
}

int main() {

    bool possible = read_data();

    if (possible) {
        Q.pb(1);
        Solve();
        printf("\n");
    }
    else printf("-1\n");

    fclose(stdin);
    fclose(stdout);
    return 0;
}
