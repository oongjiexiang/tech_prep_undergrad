#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#define REP(i, a, b) for(int i = int(a); i < int(b); i++)
using namespace std;
typedef pair<int, int> ii;

vector<int> pset;
void initSet(int _size){ pset.resize(_size); REP(i, 0, _size) pset[i] = i; }
int findSet(int i){ return (pset[i] == i)? i: pset[i] = findSet(pset[i]); }
void unionSet(int i, int j){ pset[findSet(i)] = findSet(j); }
bool isSameSet(int i, int j){ return findSet(i) == findSet(j); }

int main(){
    int V; cin >> V;

    initSet(V);
    int mst_cost = 0;
    priority_queue< pair<int, ii> > EdgeList;
    while(!EdgeList.empty()){
        pair<int, ii> fron = EdgeList.top(); EdgeList.pop();
        if(!isSameSet(fron.second.first, fron.second.second)){
            mst_cost+=(-fron.first);
            unionSet(fron.second.first, fron.second.second);
        }
    }
}
