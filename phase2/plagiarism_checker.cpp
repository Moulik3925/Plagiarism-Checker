#include "plagiarism_checker.hpp"
// You should NOT add ANY other includes to this file.
// Do NOT add "using namespace std;".

// TODO: Implement the methods of the plagiarism_checker_t class

#define ll long long
using namespace std;
ll BASE = 37;
ll MODULUS = 1e9 + 9;

ll compute_hash(std::vector<int> &submission, int start, int end)
{
    ll hash = 0;
    for (int i = start; i < end; i++)
    {
        hash = (hash * BASE + submission[i]) % MODULUS;
    }
    return hash;
}

plagiarism_checker_t::plagiarism_checker_t(std::vector<std::shared_ptr<submission_t>>
                                               __submissions)
{
    submissions = __submissions;
    // for(int i = 0; )



}
plagiarism_checker_t::~plagiarism_checker_t()
{

}

void plagiarism_checker_t::add_submission(std::shared_ptr<submission_t> __submission)
{
    
}

// End TODO