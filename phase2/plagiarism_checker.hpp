#include "structures.hpp"
#include<chrono>
#include<unordered_map>
#include<map>
#include<vector>
#include<utility>
#include<memory>
#include<set>
// -----------------------------------------------------------------------------

// You are free to add any STL includes above this comment, below the --line--.
// DO NOT add "using namespace std;" or include any other files/libraries.
// Also DO NOT add the include "bits/stdc++.h"

// OPTIONAL: Add your helper functions and classes here

class plagiarism_checker_t
{
    // You should NOT modify the public interface of this class.
public:
    plagiarism_checker_t(void);
    plagiarism_checker_t(std::vector<std::shared_ptr<submission_t>>
                             __submissions);
    ~plagiarism_checker_t(void);
    void add_submission(std::shared_ptr<submission_t> __submission);

protected:
    // TODO: Add members and function signatures here
    std::chrono::system_clock::time_point begin_time;
    std::unordered_map<long long, std::vector<std::pair<std::shared_ptr<submission_t>, long long>>> hashes;
    std::vector<std::shared_ptr<submission_t>> submissions;
    std::map<std::shared_ptr<submission_t>, std::chrono::system_clock::time_point> time_stamps;
    std::map<std::shared_ptr<submission_t>,int> num_pattern_clashes;

    void update_hashes(std::shared_ptr<submission_t> __submission, std::vector<int> tokens);

    std::map<std::shared_ptr<submission_t>,int> last_index_count;
    // End TODO
};