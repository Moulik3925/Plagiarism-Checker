#include <array>
#include <iostream>
#include <span>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>
// -----------------------------------------------------------------------------

// You are free to add any STL includes above this comment, below the --line--.
// DO NOT add "using namespace std;" or include any other files/libraries.
// Also DO NOT add the include "bits/stdc++.h"
#define ll long long

using std::cout;
using std::endl;
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

std::array<int, 5> match_submissions(std::vector<int> &submission1,
                                     std::vector<int> &submission2)
{

    // submission1 = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    // submission2 = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    // TODO: Write your code here
    int n = submission1.size();
    int m = submission2.size();


    for(int i = 0; i < n; i++)
    {
        cout<<submission1[i]<<" ";
    }
    cout<<endl;
    for(int i = 0; i < m; i++)
    {
        cout<<submission2[i]<<" ";
    }
    cout<<endl;
    std::array<int, 5> result = {0, 0, 0, 0, 0};
    int plagiarism_flag = 0;
    int total_matching_length = 0;
    int longest_approx_match = 0;
    int start_index1 = 0;
    int start_index2 = 0;
    // std::unordered_set<ll> hashes;
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
        hash2 = rolling_hash2;
        // hash2 = compute_hash(submission2, j, j + window_length);
        if (hashes.find(hash2) != hashes.end())
        {

            std::vector<ll> match_indices = hashes[hash2];
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
            for (auto match_index : match_indices)
            {
                int length_matching = 0;
                while (match_index + length_matching < n && j + length_matching < m && submission1[match_index + length_matching] == submission2[j + length_matching])
                {
                    length_matching++;
                }
                all_matches.push({match_index + length_matching - 1, j + length_matching - 1, length_matching});
                max_length_matching = std::max(max_length_matching, length_matching);
            }
            // std::cout << "Match found at " << j << " of length " << length_matching << std::endl;

            // hash_score[hash2] = std::max((ll)max_length_matching, hash_score[hash2]);
            hash_score[hash2].push_back(max_length_matching);
            // total_matching_length += length_matching;
            j += max_length_matching;
            if (j > m - window_length)
            {
                break;
            }
            hash2 = compute_hash(submission2, j, j + window_length);
            rolling_hash2 = hash2;
        }
        if (j + window_length < m)
        {
            rolling_hash2 = update_hash(hash2, submission2[j], submission2[j + window_length], window_length);
        }
        // else
        //     break;
    }
    for (auto it : hash_score)
    {
        total_matching_length += sum_of_k_greatest_elements(it.second, hashes[it.first].size());
    }


    while(!all_matches.empty())
    {
        std::vector<ll> match = all_matches.top();
        all_matches.pop();
        if(match[2] > longest_approx_match)
        {
            longest_approx_match = match[2];
            start_index1 = match[0] - match[2] + 1;
            start_index2 = match[1] - match[2] + 1;
        }
        
    }
    // for (int shift = 0; shift < n; shift++)
    // {
    //     for (int match_index = 0; match_index < m; match_index++)
    //     {
    //         int length_matching = 0;
    //         while (shift + length_matching < n && match_index + length_matching < m && submission1[shift + length_matching] == submission2[match_index + length_matching])
    //         {
    //             length_matching++;
    //         }
    //     }
    // }

    int number_of_hash_collisions = n - window_length + 1 - hashes.size();
    cout << "Number of hash collisions: " << number_of_hash_collisions << endl;
    if (total_matching_length > 0.3 * std::min(n, m))
    {
        plagiarism_flag = 1;
    }

    result[0] = plagiarism_flag;
    result[1] = total_matching_length;
    result[2] = longest_approx_match;
    result[3] = start_index1;
    result[4] = start_index2;

    return result; // dummy return
    // End TODO
}
