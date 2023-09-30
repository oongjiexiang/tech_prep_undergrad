#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#define INF 2000000000
using namespace std;
typedef pair<int, int> ii;
vector< vector<ii> > AdjList;
int main()
{
    int s, V;
    cin >> s >> V;
    vector<int> dist(V, INF); dist[s] = 0;
    priority_queue< ii, vector<ii>, greater<ii> > pq;
    while(!pq.empty()){
        ii node = pq.top(); pq.pop();
        int node_cost = node.first, node_name = node.second;
        if(node_cost == dist[node_name]){
            for(int i = 0; i < AdjList[node_name].size(); i++){
                int neighbour_node = AdjList[node_name][i].second;
                int neighbour_cost = AdjList[node_name][i].first;
                if(dist[neighbour_node] > neighbour_cost + dist[node_name]){
                    dist[neighbour_node] = neighbour_cost + dist[node_name];
                    pq.push(ii(dist[neighbour_node], neighbour_node));
                }
            }
        }
    }
    return 0;
}
