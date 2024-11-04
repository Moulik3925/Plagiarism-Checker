#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> ans;
        int pt = k - 1;
        while(pt)
        {
            if(pt == 2)
            {
                ans.push_back(1);
                ans.push_back(1);
                break;
            }
            if(pt == 1)
            {
                ans.push_back(1);
                break;
            }
            ans.push_back(pt / 2 + (pt & 1));
            pt /= 2;
        }
        if(k + 1 <= n)
        {
            ans.push_back(k + 1);
            int tp = 2 * k;
            ans.push_back(3 * k);
            while(tp <= n) ans.push_back(tp), tp *= 2;
        }
        cout << ans.size() << "\n";
        for(auto i : ans) cout << i << " ";
        cout << "\n";
    }
    return 0;
}