#include<bits/stdc++.h>
using namespace std;

unsigned long long large_num = 998244353;
#define sort_array(array) sort(array.begin(), array.end());
#define print_with_spaces(array, n) for (unsigned int i = 0; i < n; i++){cout << array[i] << " ";}
#define print_with_lines(array, n) for (unsigned int i = 0; i < n; i++){cout << array[i] << "\n";}
#define iterate(i,a,b) for (unsigned int i = a; i < b; i++)
#define yes cout << "YES\n"
#define no cout << "NO\n"
#define is_possible cout << ((possible) ? "YES\n": "NO\n")
#define vi vector<unsigned long long>
#define ull unsigned long long
#define ll long long
#define pb push_back
#define pi pair<unsigned long long, unsigned long long>
#define mp make_pair
#define read_array(array, n) for (unsigned int i = 0; i < n; i++){cin>>array[i];}

class Graph{
    public:
        unsigned int n;
        vector<vector<unsigned int>> adj;
        // Graph(unsigned int vertices);
        // void add_edge(unsigned int u, unsigned int v);
        vector<bool> visited;
        // void bfs(unsigned int node);
        vector<unsigned int> distances_from_root;

        Graph(unsigned int vertices){
            n=vertices;
            adj = vector<vector <unsigned int>>(n);
            for (unsigned int i = 0; i < n-1; i++){
                adj[i].pb(i+1);
            }
            distances_from_root = vector<unsigned int>(n, 0);
            visited = vector<bool>(n, false);
        }

        void add_edge(unsigned int u, unsigned int v){
            adj[u].pb(v);
        }

        void bfs(unsigned int node){
            visited[node] = true;
            queue<unsigned int> q;
            q.push(node);
            while (!q.empty()){
                unsigned int current = q.front();
                q.pop();
                for (unsigned int neighbor : adj[current]){
                    if (!visited[neighbor]){
                        visited[neighbor] = true;
                        distances_from_root[neighbor] = distances_from_root[current]+1;
                        q.push(neighbor);
                    }
                }
            }
        }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    unsigned long test_cases; cin>>test_cases;
    for (unsigned long p = 0; p < test_cases; p++){
        unsigned int n; cin>>n;
        unsigned int m; cin>>m;

        Graph g(n);
        vector<vector<unsigned int>> rev_adj(n);
        for (unsigned int i = 0; i < m; i++){
            unsigned int u, v; cin>>u>>v;
            g.add_edge(u-1, v-1);
            rev_adj[v-1].pb(u-1);
        }

        g.bfs(0);

        vector<ll int> possible(n+1,0);
        for (unsigned int i = 0; i < n; i++){
            if (rev_adj[i].size()==0){
                continue;
            }
            for (unsigned int neighbor : rev_adj[i]){
                unsigned int time_taken=g.distances_from_root[neighbor]+1;
                unsigned int lower_bound=neighbor+1;
                unsigned int upper_bound=i-time_taken-1;
                // cout << i << " " << neighbor << " " << time_taken << " ";
                // cout << lower_bound << " " << upper_bound << "\n";
                if (upper_bound < lower_bound){
                    continue;
                }
                possible[lower_bound]++;
                possible[upper_bound+1]--;
            }
        }
        for (unsigned int i = 0; i < n; i++){
            possible[i+1]+=possible[i];
        }
        for (unsigned int i = 0; i + 1< n; i++){
            if (possible[i]==0){
                cout << 1;
            }
            else {
                cout << 0;
            }
        }
        cout << "\n";
    }
}