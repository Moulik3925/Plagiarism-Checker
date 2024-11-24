#include "plagiarism_checker.hpp"
// You should NOT add ANY other includes to this file.
// Do NOT add "using namespace std;".

// TODO: Implement the methods of the plagiarism_checker_t class

#define ll long long
using namespace std;
ll BASE = 37;
ll MODULUS = 1e9 + 7;
int window_length = 15;

ll compute_hash(std::vector<int> &submission, int start, int end)
{
    ll hash = 0;
    for (int i = start; i < end; i++)
    {
        if(i >= submission.size())
            return -1;
        hash = (hash * BASE + submission[i]) % MODULUS;
    }
    return hash;
}

plagiarism_checker_t::plagiarism_checker_t(std::vector<std::shared_ptr<submission_t>>
                                               __submissions)
{
    begin_time = std::chrono::system_clock::now();
    submissions = __submissions;
    for (auto submission : submissions)
    {
        last_index_count[submission] = -2* window_length;
        time_stamps[submission] = begin_time;
        auto code = submission->codefile;
        tokenizer_t tokenizer(code);
        auto tokens = tokenizer.get_tokens();
        for(int i = 0; i < tokens.size() - 14; i++){
            ll hash = compute_hash(tokens, i, i + window_length);
            hashes[hash].push_back({submission, hash});
        }
    }
}
plagiarism_checker_t::~plagiarism_checker_t()
{

}

void plagiarism_checker_t::update_hashes(std::shared_ptr<submission_t> __submission, std::vector<int> tokens)
{
    for(auto x : last_index_count)
    {
        last_index_count[x.first] = -2*window_length;
    }
    last_index_count[__submission] = -2*window_length;

    for(int i = 0; i < tokens.size() - 14; i++){
        ll hash = compute_hash(tokens, i, i + window_length);
        hashes[hash].push_back({__submission, hash});
    }
}


void plagiarism_checker_t::add_submission(std::shared_ptr<submission_t> __submission)
{
    time_stamps[__submission] = std::chrono::system_clock::now();
    submissions.push_back(__submission);

    auto code = __submission->codefile;
    tokenizer_t tokenizer(code);
    auto tokens = tokenizer.get_tokens();

    std::set<std::shared_ptr<submission_t>> plagged_submissions;



    ll hash2;
    for (int j = 0; j <= tokens.size() - window_length; j++)
    {
        hash2 = compute_hash(tokens, j, j + window_length);

       
        if (hashes.find(hash2) != hashes.end())
        {

            std::vector<std::pair<std::shared_ptr<submission_t>, long long>> match_indices = hashes[hash2];
            if (match_indices.empty())
                continue;
           

            

            std::shared_ptr<submission_t> prev_file;
            for (auto match_indice : match_indices)
            {
                
                if(j - last_index_count[match_indice.first] >= window_length)
                {
                    num_pattern_clashes[match_indice.first] += 1;
                    last_index_count[match_indice.first] = j;
                }
                if(num_pattern_clashes[match_indice.first] >= 10)
                {
                    plagged_submissions.insert(__submission);
                   
                    if (std::chrono::duration_cast<std::chrono::seconds>(time_stamps[__submission] - time_stamps[match_indice.first]).count() < 1)
                    {
                        plagged_submissions.insert(match_indice.first);
                    }
                }


                ll match_index = match_indice.second;
                int length_matching = 0;
                prev_file = match_indice.first;
                bool match75_found = true;
                
                for(int qq = 1; qq <= 4; qq++)
                {
                    ll new_index = j + qq*window_length;
                    if(new_index + window_length >= tokens.size())
                    {
                        match75_found = false;
                        prev_file = NULL;
                        break;
                    }
                    ll new_hash = compute_hash(tokens, new_index, new_index + window_length);
                    auto zz = hashes[new_hash];
                    if(!zz.empty())
                    {
                        for(auto x : zz)
                        {
                            match75_found = false;
                            if(x.first == prev_file and x.second == match_index + qq*window_length)
                            {
                                match75_found = true;
                                break;
                            }
                        }
                        // if(zz.find({match_indice.first, match_index + qq*window_length}) == zz.end())
                        // {
                        //     match75_found = false;
                        //     prev_file = NULL;
                        //     break;
                        // }
                    }
                    else
                    {
                        match75_found = false;
                        prev_file = NULL;
                        break;
                    }
                }

                if(match75_found)
                {
                   if(prev_file != NULL) 
                   {
                    // mark current file as plag
                    plagged_submissions.insert(__submission);
                    // if(__submission->student != NULL) __submission->student->flag_student(__submission);
                    // if(__submission->professor != NULL) __submission->professor->flag_professor(__submission);

                    if (std::chrono::duration_cast<std::chrono::seconds>(time_stamps[__submission] - time_stamps[prev_file]).count() < 1)
                    {
                        // mark prev file as plag
                        plagged_submissions.insert(prev_file);
                        // if(prev_file->student != NULL) prev_file->student->flag_student(prev_file);
                        // if(prev_file->professor != NULL) prev_file->professor->flag_professor(prev_file);
                    }
                    }
                    // j += window_length - 1;
                }
            }
        }
        

    }

    for(auto x : plagged_submissions)
    {
        if(x->student != NULL) x->student->flag_student(x);
        if(x->professor != NULL) x->professor->flag_professor(x);
    }
    update_hashes(__submission, tokens);
    num_pattern_clashes.clear();

}

// End TODO