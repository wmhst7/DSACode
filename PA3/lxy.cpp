#include <stdio.h>

#define PBMC 0
#define INFINITY 1E6
#define UNDEFINED -1
#define MAXN 505

int c_max;            // c_max(always an even number): the maximum capacity of each station
int n;                // n: the total number of stations
int s_prob;           // s_prob: the index of the problem station
int m;                // m: the number of roads
int c_bike[MAXN];     // c_bike[S_i]: current number of bikes at station_i
                      // respectively
int cost[MAXN][MAXN]; // cost[S_i][S_j]: the time taken to move betwen stations
                      // i and j, namely an adjacent matrix

int dist[MAXN];  // shortest distance to source point
int prev[MAXN];  // the previous vertex on the shortest path
int visit[MAXN]; // if the vertex has been visited

int send[MAXN]; // need bike number of each vertex on the shortest path
int back[MAXN]; // excrescent bike number of each vertex on the shortest path

int max(int a, int b) { return (a > b) ? a : b; }

// An improved dijkstra algorithm to solve Public Bike Management problem.
// Select a shortest path through bicycle migration needs.
void dijkstra()
{
    for (int i = 0; i < n; ++i)
    { // initializeize arrays
        dist[i] = INFINITY;
        send[i] = back[i] = UNDEFINED;
    }
    dist[s_prob] = 0;                                  // start algorithm at problem station
    c_bike[PBMC] = c_max / 2;                          // ensure the difference bike number of PBMC is 0
    send[s_prob] = max(0, c_max / 2 - c_bike[s_prob]); // initialize need bike number
    back[s_prob] =
        max(0, c_bike[s_prob] - c_max / 2); // initialize excrescent bike number
    for (int i = 0; i < n; ++i)
    {
        int min = INFINITY, u = UNDEFINED;
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v] && dist[v] < min)
            { // current minimum distance neighbor
                min = dist[v];
                u = v;
            }
        }
        if (u == UNDEFINED) // no neighbor vertices, finish algorithm
            break;
        visit[u] = 1;  // mark the minimum distance vertex as visited
        if (u == PBMC) // arrive PBMC, finish algorithm
            return;
        for (int v = 0; v < n; ++v)
        {
            if (!visit[v])
            {                                               // judge an unvisited vertex
                int cur_send = send[u], cur_back = back[u]; // current migration needs
                int x = c_bike[v] -
                        c_max / 2; // bike number difference of current judging vertex
                if (x >= 0)
                {                      // excrescent bike
                    if (x <= cur_send) // if send all to u
                        cur_send -= x;
                    else
                    { // more than need of u
                        x -= cur_send;
                        cur_send = 0;
                        cur_back += x;
                    }
                }
                else               // lack of bike
                    cur_send -= x; // need more bikes
                if (dist[v] < 0 || dist[u] + cost[v][u] < dist[v] ||
                    dist[u] + cost[v][u] == dist[v] && cur_send < send[v] ||
                    dist[u] + cost[v][u] == dist[v] && cur_send == send[v] &&
                        cur_back < back[v])
                {   // judge if (u,v) is a shorter path or
                    // transport less bikes
                    dist[v] = dist[u] + cost[v][u];
                    send[v] = cur_send;
                    back[v] = cur_back;
                    prev[v] = u; // update path
                }
            }
        }
    }
}

int main()
{
    scanf("%d%d%d%d", &c_max, &n, &s_prob, &m);
    ++n;                         // include PBMC
    for (int i = 1; i < n; ++i)  // the stations are numbered from 1 to N
        scanf("%d", c_bike + i); // read bike number of each station
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
                cost[i][j] = 0; // the cost of path to oneself is 0
            else
                cost[i][j] = INFINITY; // initialize cost to infinity
        }
    }
    for (int i = 0; i < m; ++i)
    {
        int s_i, s_j, len;
        scanf("%d%d%d", &s_i, &s_j, &len);     // read cost
        cost[s_j][s_i] = cost[s_i][s_j] = len; // undirected graph
    }
    dijkstra(); // run algorithm
    printf("%d ", send[PBMC]);
    int v = PBMC;
    while (v != s_prob)
    { // print path
        printf("%d->", v);
        v = prev[v];
    }
    printf("%d %d\n", s_prob, back[PBMC]);
    return 0;
}
