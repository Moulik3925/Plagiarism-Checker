#include<bits/stdc++.h>
using namespace std;

unsigned long long large_num = 998244353;
#define sort_array(array) sort(array.begin(), array.end());
#define print_with_spaces(array, n) for (unsigned int i = 0; i < n; i++){cout << array[i] << " ";}
#define print_with_lines(array, n) for (unsigned int i = 0; i < n; i++){cout << array[i] << "\n";}
#define iterate(n) for (unsigned int i = 0; i < n; i++)
#define yes cout << "YES\n"
#define no cout << "NO\n"
#define is_possible cout << ((possible) ? "YES\n": "NO\n")

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    unsigned long test_cases; cin>>test_cases;
    for (unsigned long p = 0; p < test_cases; p++){
        unsigned long n; cin>>n;
        unsigned long k; cin>>k;
        unsigned int index=0;
        while (k >= (1<<(index+1))){
            index++;
        }
        vector<unsigned long long> array{};
        if (k != n) array.push_back(k+1);
        unsigned long long power=1;
        unsigned long long value=0;
        for (unsigned int i = 0; i < 22; i++){
            if (i!=index) array.push_back(power);
            else {value=k-power; if (value != 0) array.push_back(value); array.push_back(k+power*2);}
            power*=2;
            if (power > n){
                break;
            }
        }
        cout << array.size() << "\n";
        for (unsigned long long a: array){
            cout << a << " ";
        }
    }
}