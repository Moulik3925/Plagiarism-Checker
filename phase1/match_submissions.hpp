#include <array>
#include <iostream>
#include <span>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <queue>
#include <iterator>
// -----------------------------------------------------------------------------

// You are free to add any STL includes above this comment, below the --line--.
// DO NOT add "using namespace std;" or include any other files/libraries.
// Also DO NOT add the include "bits/stdc++.h"
#define ll long long

using std::cout;
using std::endl;

// lower_bound(const g) Returns an iterator to the first element that is equivalent to ‘g’ or definitely will not go before the element ‘g’ in the set.
// upper_bound(const g)    Returns an iterator to the first element that will go after the element ‘g’ in the set.
// OPTIONAL: Add your helper functions and data structures here
const int BASE = 31;
const int MODULUS = 1e9 + 9;
ll exponent(ll base, ll power)
{
    ll result = 1;
    while (power > 0)
    {
        if (power % 2 == 1)
        {
            result = (result * base) % MODULUS;
        }
        base = (base * base) % MODULUS;
        power /= 2;
    }
    return result;
}

ll compute_hash(std::vector<int> &submission, int start, int end)
{
    ll hash = 0;
    for (int i = start; i < end; i++)
    {
        hash = (hash * BASE + submission[i]) % MODULUS;
    }
    return hash;
}

ll update_hash(ll old_hash, int old_char, int new_char, int length)
{
    ll new_hash = (old_hash - old_char * exponent(BASE, length - 1)) % MODULUS;
    if (new_hash < 0)
    {
        new_hash += MODULUS;
    }
    new_hash = (new_hash * BASE + new_char) % MODULUS;
    return new_hash;
}
ll sum_of_k_greatest_elements(std::vector<ll> &arr, int k)
{
    std::sort(arr.begin(), arr.end(), std::greater<ll>());
    ll sum = 0;
    for (int i = 0; i < std::min(k, (int)arr.size()); i++)
    {
        sum += arr[i];
    }
    return sum;
}

void solve(std::unordered_map<ll, std::set<int>> &flags, std::vector<int> &submission1, std::vector<int> &submission2, int &start_index1, int &start_index2, int &best, int index1, int index2)
{
    int n = submission1.size() - index1;
    int m = submission2.size() - index2;
    std::vector<std::vector<int>> dpp(31, std::vector<int>(31, 0));
    for (int i = 1; i <= 30 && index1 + i - 1 < submission1.size(); ++i)
    {
        for (int j = 1; j <= 30 && index2 + j - 1 < submission2.size(); ++j)
        {
            if (submission1[index1 + i - 1] == submission2[index2 + j - 1])
                dpp[i][j] = dpp[i - 1][j - 1] + 1;
            else
                dpp[i][j] = std::max(dpp[i - 1][j], dpp[i][j - 1]);
        }
    }
    if (dpp[std::min(30, int(submission1.size() - index1))][std::min(30, int(submission2.size() - index2))] < 21)
        return;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (submission1[index1 + i - 1] == submission2[index2 + j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    for (int f = index2 + 30; f < submission2.size(); f++)
    {
        std::set<int> indices = flags[submission2[f]];
        auto it = indices.upper_bound(index1);
        for (; it != indices.end(); ++it)
        {
            int index = *it;
            double ratio = double(index - index1) / double(f - index2);
            if (ratio > 1.25 || ratio < 0.8)
                continue;
            int lcs = dp[index - index1][f - index2];
            if (double(lcs) >= (0.8) * double(std::max(index - index1, f - index2)) && lcs >= 30)
            {
                // if(index1 == 183 && index2 == 1) cout << index << ' ' << ratio << ' ' << lcs << ' ' << f << '\n';
                if (std::min(index - index1, f - index2) > best)
                {
                    start_index1 = index1;
                    start_index2 = index2;
                    best = std::min(index - index1, f - index2);
                }
            }
        }
    }
    // int n = submission1.size();
    // int m = submission2.size();
    // std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    // // Building dp[m+1][n+1] in bottom-up fashion
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= m; ++j) {
    //         if (submission1[i - 1] == submission2[j - 1])
    //             dp[i][j] = dp[i - 1][j - 1] + 1;
    //         else
    //             dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
    //     }
    // }
    // int best = 0;
    // for(int a = 0; a < n; a++){
    //     for(int b = 0; b < m; b++){
    //             int base = dp[a][b];
    //             int lastsucc = 0;
    //             for(int i = 1; (a + i <= n) && (b + i <= m); i++){
    //                     double rate = double(dp[a + i][b + i] - base) / double(i);
    //                     //DEBUG
    //                     if(a == b) cout << rate << ' ';

    //                     if (rate >= 0.80) lastsucc = i;
    //                     if(i > 30 && (rate < 0.68)) break;
    //             }
    //             if(best < lastsucc){
    //                     start_index1 = a;
    //                     start_index2 = b;
    //             }
    //             best = std::max(best, lastsucc);
    //     //        cout << best << ' ';
    //     }
    // }

    // dp[m][n] contains length of LCS for s1[0..m-1]
    // and s2[0..n-1]
}
std::vector<int> edit(std::vector<int> &submission1, std::vector<int> &submission2)
{
    int n = submission1.size();
    int m = submission2.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
    std::vector<std::vector<int>> parentn(n + 1, std::vector<int>(m + 1, 0));
    std::vector<std::vector<int>> parentm(n + 1, std::vector<int>(m + 1, 0));
    for (int e = 0; e <= n; e++)
    {
        dp[e][0] = e;
    }
    for (int e = 0; e <= m; e++)
    {
        dp[0][e] = e;
    }
    for (int a = 1; a <= n; a++)
    {
        for (int b = 1; b <= m; b++)
        {
            int c = 2;
            if (submission1[a - 1] == submission2[b - 1])
                c = 0;
            dp[a][b] = std::min(dp[a - 1][b] + 1, std::min(dp[a][b - 1] + 1, dp[a - 1][b - 1] + c));
            if (dp[a][b] == dp[a - 1][b - 1] + c)
            {
                parentn[a][b] = a - 1;
                parentm[a][b] = b - 1;
            }
            if (dp[a][b] == dp[a - 1][b] + 1)
            {
                parentn[a][b] = a - 1;
                parentm[a][b] = b;
            }
            if (dp[a][b] == dp[a][b - 1] + 1)
            {
                parentn[a][b] = a;
                parentm[a][b] = b - 1;
            }
        }
    }
    // int a = n, b = m;
    // int a = n, b = m;
    int overall_best = 0;
    int final_s1 = 0, final_s2 = 0;
    for (int i = n; i >= n - 200; i -= 40)
    {
        for (int j = m; j >= m - 200; j -= 40)
        {
            int a = i, b = j;
            std::vector<std::pair<int, int>> matches;
            while (a > 0 && b > 0)
            {
                int ta = parentn[a][b], tb = parentm[a][b];
                if (ta == a - 1 && tb == b - 1 && dp[a][b] == dp[a - 1][b - 1])
                    matches.push_back({a - 1, b - 1});
                a = ta;
                b = tb;
            }
            // for (auto x : matches)
            //     cout << x.first << " " << x.second << endl;
            int ms = matches.size();
            int best = 0;
            int s1 = 0, s2 = 0;
            for (int t = 0; t < ms; t++)
            {
                for (int w = t + 1; w < ms; w++)
                {
                    if (std::max(matches[t].second - matches[w].second + 1, matches[t].first - matches[w].first + 1) < 30)
                        continue;
                    double ratio = double(w - t + 1) / double(std::max(matches[t].second - matches[w].second + 1, matches[t].first - matches[w].first + 1));
                    if (ratio >= 0.8)
                    {
                        int score = std::max(matches[t].second - matches[w].second + 1, matches[t].first - matches[w].first + 1);
                        int old_score = score;
                        score = (int)(double(w - t + 1) / 0.8);
                        score = std::min(score, std::min(n, m));
                        if (best < score)
                        {
                            // s1 = matches[w].first;
                            s1 = std::max(matches[w].first + old_score - score, n - score);
                            // s2 = matches[w].second;
                            s2 = std::max(matches[w].second + old_score - score, m - score);
                            best = score;
                        }
                    }
                }
            }
            // cout<<n-i<<" "<<m-j<<" "<<s1<<" "<<s2<<endl;
            if (overall_best < best)
            {
                overall_best = best;
                final_s1 = s1;
                final_s2 = s2;


                // cout << a << " " << b << " " << n - a << ' ' << m - b << ' ' << best << ' ' << s1 << ' ' << s2 << endl;
            }
        }
    }
   // for (auto match : matches)
    //{
     //          cout << match.first << ' ' << match.second << '\n';
    //}
    return {overall_best, final_s1, final_s2};
    // return {best, s1, s2};
    // cout << best << ' ' << s1 << ' ' << s2 << '\n';
}
void check(std::vector<int> &submission1, std::vector<int> &submission2)
{

    std::vector<std::vector<int>> dpp(submission1.size() + 1, std::vector<int>(submission2.size() + 1, 0));

    for (int i = 1; i <= submission1.size(); ++i)
    {
        for (int j = 1; j <= submission2.size(); ++j)
        {
            if (submission1[i - 1] == submission2[j - 1])
                dpp[i][j] = dpp[i - 1][j - 1] + 1;
            else
                dpp[i][j] = std::max(dpp[i - 1][j], dpp[i][j - 1]);
        }
    }
    cout << dpp[639][513];
}

std::array<int, 5> match_submissions(std::vector<int> &submission1,
                                     std::vector<int> &submission2)
{
    // TODO: Write your code here
    int n = submission1.size();
    int m = submission2.size();
    cout<<"n: "<<n<<" m: "<<m<<endl;

    // std::reverse(submission1.begin(), submission1.end());
    // std::reverse(submission2.begin(), submission2.end());

    // check(submission1, submission2);
    //  for(int a = 0; a < n; a++) std::cout << submission1[a] << ' ';
    // std::cout << '\n';
    // for(int a = 0; a < m; a++) std::cout << submission2[a] << ' ';
    // std::cout << '\n';
    std::array<int, 5> result = {0, 0, 0, 0, 0};
    int plagiarism_flag = 0;
    int total_matching_length = 0;
    int longest_approx_match = 0;
    int start_index1 = 0;
    int start_index2 = 0;
    // std::unordered_set<ll> hashes;
    // std::unordered_map<ll, ll> hashes;
    std::unordered_map<ll, ll> indice_to_hash;
    std::unordered_map<ll, std::vector<ll>> hashes;
    std::unordered_map<ll, std::vector<ll>> hash_score;
    std::priority_queue<std::vector<ll>, std::vector<std::vector<ll>>, std::greater<std::vector<ll>>> all_matches;
    ll window_length = 10;
    ll hash1 = compute_hash(submission1, 0, window_length);
    ll rolling_hash = hash1;
    for (int i = 0; i <= n - window_length; i++)
    {
        // hashes.insert(hash1);
        // hash1 = compute_hash(submission1, i, i + window_length);
        hash1 = rolling_hash;
        hashes[hash1].push_back(i);
        indice_to_hash[i] = hash1;
        // cout<<hash1<<" "<<rolling_hash<<endl;

        if (i + window_length < n)
        {
            rolling_hash = update_hash(hash1, submission1[i], submission1[i + window_length], window_length);
            // hash1 = update_hash(hash1, submission1[i], submission1[i + window_length], window_length);
        }
        // else
        //     break;
    }
    ll hash2 = compute_hash(submission2, 0, window_length);
    ll rolling_hash2 = hash2;
    for (int j = 0; j <= m - window_length; j++)
    {
        hash2 = compute_hash(submission2, j, j + window_length);

        // hash2 = rolling_hash2;
        // hash2 = compute_hash(submission2, j, j + window_length);
        if (hashes.find(hash2) != hashes.end())
        {

            std::vector<ll> match_indices = hashes[hash2];
            if (match_indices.empty())
                continue;
            // int length_matching = 0;
            // while (j + length_matching < m && submission1[start_index1 + length_matching] == submission2[j + length_matching])
            // {
            //     length_matching++;
            // }
            // if(length_matching > total_matching_length)
            // {
            //     total_matching_length = length_matching;
            //     start_index2 = j;
            // }
            int max_length_matching = 0;
            int index_of_max_match = -1;
            for (auto match_index : match_indices)
            {
                int length_matching = 0;
                while (match_index + length_matching < n && j + length_matching < m && submission1[match_index + length_matching] == submission2[j + length_matching])
                {
                    length_matching++;
                }
                all_matches.push({match_index + length_matching - 1, j + length_matching - 1, length_matching});
                if (length_matching > max_length_matching)
                {
                    max_length_matching = length_matching;
                    index_of_max_match = match_index;
                }
            }
            // std::cout << "Match found at " << j << " of length " << length_matching << std::endl;
            for (int it = index_of_max_match + 1; it < index_of_max_match + max_length_matching; it++)
            {
                // hashes[indice_to_hash[it]].erase(std::remove(hashes[indice_to_hash[it]].begin(), hashes[indice_to_hash[it]].end(), it), hashes[indice_to_hash[it]].end());
                auto ptr = std::find(hashes[indice_to_hash[it]].begin(), hashes[indice_to_hash[it]].end(), it);
                if (ptr != hashes[indice_to_hash[it]].end())
                    hashes[indice_to_hash[it]].erase(ptr);
                // hashes[indice_to_hash[it]].erase(std::lower_bound(hashes[indice_to_hash[it]].begin(), hashes[indice_to_hash[it]].end(), it));
            }
            // hash_score[hash2] = std::max((ll)max_length_matching, hash_score[hash2]);
            hash_score[hash2].push_back(max_length_matching);
            total_matching_length += max_length_matching;
            j += max_length_matching;
            if (j > m - window_length)
            {
                break;
            }
            // hash2 = compute_hash(submission2, j, j + window_length);
            // rolling_hash2 = hash2;
        }
        if (j + window_length < m)
        {
            // rolling_hash2 = update_hash(hash2, submission2[j], submission2[j + window_length], window_length);
        }
        // else
        //     break;
    }
    // for (auto it : hash_score)
    // {
    //     total_matching_length += sum_of_k_greatest_elements(it.second, hashes[it.first].size());
    // }

    while (!all_matches.empty())
    {
        std::vector<ll> match = all_matches.top();
        all_matches.pop();
        if (match[2] > longest_approx_match)
        {
            longest_approx_match = match[2];
            start_index1 = match[0] - match[2] + 1;
            start_index2 = match[1] - match[2] + 1;
        }
    }
    if (total_matching_length > 0.3 * std::min(n, m))
    {
        plagiarism_flag = 1;
    }
    auto approx_matching_stats = edit(submission1, submission2);
    longest_approx_match = approx_matching_stats[0];
    start_index1 = approx_matching_stats[1];
    start_index2 = approx_matching_stats[2];

    // n to the power of 4 algo
    // First build the map that stores the
    int best = 0;
    int s1 = -1, s2 = -1;
    std::unordered_map<ll, std::set<int>> flags;
    for (int ind = 0; ind < n; ind++)
    {
        (flags[submission1[ind]]).insert(ind);
    }

    // int c = 0;
    // // Now we iterate through it as a way of finding the indices matching for a certain index in the second set
    // for (int it = 0; it < m; it++)
    // {
    //     for (auto ind : flags[submission2[it]])
    //     {
    //         // std::cout << ind << ' ';
    //         // cout << c << '\n';
    //         // solve(flags, submission1, submission2, s1, s2, best, ind, it);
    //     }
    //     c++;
    //     // cout << c;
    //     // std::cout << '\n';
    // }
    // start_index1 = s1;
    // start_index2 = s2;
    // hehe
    // longest_approx_match = best;

    result[0] = plagiarism_flag;
    result[1] = total_matching_length;
    result[2] = longest_approx_match;
    result[3] = start_index1;
    result[4] = start_index2;

    return result; // dummy return
    //  End TODO
}
