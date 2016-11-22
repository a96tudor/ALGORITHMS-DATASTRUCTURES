/**
 *      Bellman-Ford's algorithm implementation
 *
 *          complexity : O(E*V*log(V))
 *          advantage : supports negative costs on the edges
 *
 * Created by Tudor Avram on 22/11/16.
*/
#include<cstdio>
#include<vector>
#include<queue>

#define MAX_SIZE 50001
#define INF ~(1<<31)
#define pairs pair<int, int>
#define iterator vector< pair<int, int> >::iterator
using namespace std;

vector< pairs > G[MAX_SIZE];
queue<int> Q;

int D[MAX_SIZE], seen[MAX_SIZE];
bool used[MAX_SIZE];

void print_results(int N, bool cycle) {
    if (cycle) {
        printf("Negative cycle!\n");
        return;
    }
    for (int i = 2; i <= N; i++) {
        if (D[i] == INF) printf("0 ");
        else printf("%d ", D[i]);
    }
    printf("\n");
}

bool Solve(int N) {
    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();
        used[current] = false;
        for (iterator it = G[current].begin(); it != G[current].end(); it++) {
            pairs e = *it;
            int dest = e.first, cost = e.second;
            if (D[dest] > cost + D[current]) {
                D[dest] = cost + D[current];
                seen[dest]++;
                if (seen[dest] > N) return true;    // we have a cycle
                if (!used[dest]) {
                    Q.push(dest);
                    used[dest] = true;
                }
            }
        }
    }
    return false;
}

void read_data(int &N) {
    int M;
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= M; i++) {
        int x,y,c;
        scanf("%d%d%d", &x, &y, &c);
        G[x].push_back(make_pair(y,c));
    }

    for (int i = 2; i <= N; i++) {
        D[i] = INF;
        used[i] = false;
    }

    Q.push(1); D[1] = 0; used[1] = true; seen[1] = 1;
}

int main() {
    freopen("bellmanford.in","r",stdin);
    freopen("bellmanford.out","w",stdout);
    int N;

    read_data(N);
    print_results(N, Solve(N));

    fclose(stdin);
    fclose(stdout);
    return 0;
}
