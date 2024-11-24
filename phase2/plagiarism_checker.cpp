#include "plagiarism_checker.hpp"
// You should NOT add ANY other includes to this file.
// Do NOT add "using namespace std;".

// TODO: Implement the methods of the plagiarism_checker_t class

#define ll long long
ll BASE = 37;
ll MODULUS = 1e9 + 7;
int window_length = 15;

ll compute_hash(std::vector<int> &submission, int start, int end)
{
    ll hash = 0;
    for (int i = start; i < end; i++)
    {
        if (i >= submission.size())
            return -1;
        hash = (hash * BASE + submission[i]) % MODULUS;
    }
    return hash;
}

plagiarism_checker_t::plagiarism_checker_t(std::vector<std::shared_ptr<submission_t>>
                                               __submissions)
{
    stop_thread = false;
    begin_time = std::chrono::system_clock::now();
    submissions = __submissions;
    for (auto submission : submissions)
    {
        plagged_submissions_flag[submission] = false;
        last_index_count[submission] = -2 * window_length;
        time_stamps[submission] = begin_time;
        auto code = submission->codefile;
        tokenizer_t tokenizer(code);
        auto tokens = tokenizer.get_tokens();
        for (int i = 0; i < tokens.size() - 14; i++)
        {
            ll hash = compute_hash(tokens, i, i + window_length);
            hashes[hash].push_back({submission, hash});
        }
    }
    continuous_worker_thread = std::thread(&plagiarism_checker_t::continuous_worker, this);
}
plagiarism_checker_t::~plagiarism_checker_t()
{
    // std::unique_lock<std::mutex> lock(mtx);
    stop_thread = true;
    cv.notify_all();
    continuous_worker_thread.join();
}

void plagiarism_checker_t::update_hashes(std::shared_ptr<submission_t> __submission, std::vector<int> tokens)
{
    for (auto x : last_index_count)
    {
        last_index_count[x.first] = -2 * window_length;
    }
    last_index_count[__submission] = -2 * window_length;

    for (int i = 0; i < tokens.size() - 14; i++)
    {
        ll hash = compute_hash(tokens, i, i + window_length);
        hashes[hash].push_back({__submission, hash});
    }
}

void plagiarism_checker_t::evaluate_plagiarism(std::shared_ptr<submission_t> __submission)
{

    auto code_string = __submission->codefile;
    tokenizer_t tokenizer(code_string);
    auto tokens = tokenizer.get_tokens();

    std::set<std::shared_ptr<submission_t>> plagged_submissions;

    long long total_pattern_matches = 0;
    bool once_increased = false;
    ll hash;
    for (int j = 0; j <= tokens.size() - window_length; j++)
    {
        hash = compute_hash(tokens, j, j + window_length);
        once_increased = false;

        if (hashes.find(hash) != hashes.end())
        {
            std::vector<std::pair<std::shared_ptr<submission_t>, long long>> match_indices = hashes[hash];
            if (match_indices.empty())
                continue;

            std::shared_ptr<submission_t> prev_file;
            for (auto match_address : match_indices)
            {
                if (j - last_index_count[match_address.first] >= window_length)
                {
                    num_pattern_clashes[match_address.first] += 1;
                    if (!once_increased)
                    {
                        total_pattern_matches += 1;
                        once_increased = true;
                    }
                    last_index_count[match_address.first] = j;
                }
                if (num_pattern_clashes[match_address.first] >= 10)
                {
                    plagged_submissions.insert(__submission);

                    if (std::chrono::duration_cast<std::chrono::seconds>(time_stamps[__submission] - time_stamps[match_address.first]).count() < 1)
                    {
                        plagged_submissions.insert(match_address.first);
                    }
                }
                if (total_pattern_matches >= 20)
                {
                    plagged_submissions.insert(__submission);
                }

                ll match_index = match_address.second;
                int length_matching = 0;
                prev_file = match_address.first;
                bool match75_found = true;

                for (int i = 1; i <= 4; i++)
                {
                    ll new_index = j + i * window_length;
                    if (new_index + window_length >= tokens.size())
                    {
                        match75_found = false;
                        prev_file = NULL;
                        break;
                    }
                    ll new_hash = compute_hash(tokens, new_index, new_index + window_length);
                    auto hashLookupResult = hashes[new_hash];
                    if (!hashLookupResult.empty())
                    {
                        for (auto matchedSubmission : hashLookupResult)
                        {
                            match75_found = false;
                            if (matchedSubmission.first == prev_file and matchedSubmission.second == match_index + i * window_length)
                            {
                                match75_found = true;
                                break;
                            }
                        }
                    }
                    else
                    {
                        match75_found = false;
                        prev_file = NULL;
                        break;
                    }
                }

                if (match75_found)
                {
                    if (prev_file != NULL)
                    {
                        // mark current file as plag
                        plagged_submissions.insert(__submission);

                        if (std::chrono::duration_cast<std::chrono::seconds>(time_stamps[__submission] - time_stamps[prev_file]).count() < 1)
                        {
                            // mark prev file as plag
                            plagged_submissions.insert(prev_file);
                        }
                    }
                }
            }
        }
    }
    std::set<std::shared_ptr<submission_t>> temp;
    {
        // std::unique_lock<std::mutex> lock(mtx);
        temp = plagged_submissions;
    }
    for (auto x : temp)
    {

        if (plagged_submissions_flag[x] == true)
            continue;
        if (x->student != NULL)
            x->student->flag_student(x);
        if (x->professor != NULL)
            x->professor->flag_professor(x);
        plagged_submissions_flag[x] = true;
    }
    update_hashes(__submission, tokens);
    num_pattern_clashes.clear();
}

void plagiarism_checker_t::continuous_worker()
{
    while (true)
    {
        std::function<void()> task;

        // Lock and wait for tasks
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]
                    { return !task_queue.empty() || stop_thread; });

            if (stop_thread && task_queue.empty())
                return;
            task = std::move(task_queue.front());
            task_queue.pop();
        }

        // Execute the task
        task();
    }
}

void plagiarism_checker_t::add_submission(std::shared_ptr<submission_t> __submission)
{
    // std::cerr << "Adding submission" << std::endl;
    // std::unique_lock<std::mutex> lock(mtx);
    time_stamps[__submission] = std::chrono::system_clock::now();
    plagged_submissions_flag[__submission] = false;
    submissions.push_back(__submission);
    task_queue.push([this, __submission]
                    { evaluate_plagiarism(__submission); });
}

// End TODO