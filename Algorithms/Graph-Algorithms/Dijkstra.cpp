/**
 *      Dijkstra's algorithm implementation
 *
 *          complexity : O(E*log(V))
 *          disadvantage : does not support negative costs on the edges
 *
 * Created by Tudor Avram on 22/11/16.
*/

#include<vector>
#include<set>
#include<cstdio>
#include<utility>

#define INF ~(1<<31)
#define pb push_back
#define mp make_pair
#define pairs pair<int, int>
#define N_MAX 50001
#define iterator vector< pair<int, int> >::iterator
using namespace std;

vector< pairs > G[N_MAX];
multiset< pairs > H;

int D[N_MAX];
bool visited[N_MAX];

void print_results(int N) {
    for (int i = 2; i <= N; i++) {
        if (D[i] == INF) printf("0 ");
        else printf("%d ", D[i]);
    }
    printf("\n");
}

void Solve() {
    while (!H.empty()) {
        pairs s = *(H.begin());
        int cost = s.first, node = s.second;
        H.erase(H.begin());
        visited[node] = true;
        for (iterator it = G[node].begin(); it!=G[node].end(); it++) {
            s = *it;
            if (!visited[s.first] && s.second + cost < D[s.first]) {
                if (D[s.first] != INF) {
                    // it has already been visited, so we need to replace it in the multiset
                    H.erase(H.find(make_pair(D[s.first], s.first)));
                }
                D[s.first] = s.second + cost;
                H.insert(mp(D[s.first], s.first));
            }
        }
    }
}

void read_data(int &N) {
    int M;
    scanf("%d%d", &N, &M);

    for (int i = 0; i < M; i++) {
        int x, y, c;
        scanf("%d%d%d", &x, &y, &c);
        G[x].pb(mp(y,c));
    }

    for (int i = 2; i <= N; i++) {
        D[i] = INF;
        visited[i] =false;
    }
    D[1] = 0; H.insert(mp(0, 1));
}

int main() {
    int N;
    read_data(N);
    Solve();
    print_results(N);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
