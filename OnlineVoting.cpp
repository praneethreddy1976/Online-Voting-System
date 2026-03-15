#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

/* ---------- SAFE INPUT ---------- */

template <typename T>
bool safeRead(T &val)
{
    if (cin >> val)
        return true;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Invalid input. Please try again.\n";
    return false;
}

string readLine(const string &prompt)
{
    string s;
    cout << prompt;
    getline(cin >> ws, s);
    return s;
}

/* ---------- VOTER ---------- */

class Voter
{
    int id_;
    string name_;
    bool hasVoted_;

public:
    Voter() : id_(0), name_(""), hasVoted_(false) {} // default constructor

    Voter(int id, const string &name)
        : id_(id), name_(name), hasVoted_(false) {}
    int getId() const { return id_; }
    const string &getName() const { return name_; }
    bool hasVoted() const { return hasVoted_; }
    void markVoted() { hasVoted_ = true; }
};

/* ---------- CANDIDATE ---------- */

class Candidate
{
    int id_;
    string name_;
    int votes_;

public:
    Candidate() : id_(0), name_(""), votes_(0) {} // default constructor
    Candidate(int id, const string &name) : id_(id), name_(name), votes_(0) {}
    int getId() const { return id_; }
    const string &getName() const { return name_; }
    int getVotes() const { return votes_; }
    void addVote() { votes_++; }
};

/* ---------- VOTE ---------- */

class Vote
{
    int voterID_;
    int candidateID_;

public:
    Vote(int voterID, int candidateID) : voterID_(voterID), candidateID_(candidateID) {}
    int getVoterID() const { return voterID_; }
    int getCandidateID() const { return candidateID_; }
};

/* ---------- VOTING SYSTEM ---------- */

class VotingSystem
{
    unordered_map<int, Voter> voters_;
    unordered_map<int, Candidate> candidates_;
    queue<Vote> voteQueue_;
    vector<Vote> auditLog_;
    bool votingClosed_;
    bool candidateExists(int id) const
    {
        return candidates_.find(id) != candidates_.end();
    }

    bool voterExists(int id) const
    {
        return voters_.find(id) != voters_.end();
    }

    void processVotesInternal()
    {
        while (!voteQueue_.empty())
        {
            Vote v = voteQueue_.front();
            voteQueue_.pop();

            auto it = candidates_.find(v.getCandidateID());
            if (it != candidates_.end())
                it->second.addVote();

            auditLog_.push_back(v);
        }
    }

public:
    VotingSystem() : votingClosed_(false)
    {

        voters_.insert({101, Voter(101, "Kohli")});
        voters_.insert({102, Voter(102, "Dhoni")});
        voters_.insert({103, Voter(103, "Rohit")});
        candidates_.insert({1, Candidate(1, "A")});
        candidates_.insert({2, Candidate(2, "B")});
        candidates_.insert({3, Candidate(3, "C")});
    }

    /* ----- voter management ----- */

    void registerVoter()
    {
        int id;
        cout << "Enter voter ID: ";
        if (!safeRead(id))
            return;

        if (voterExists(id))
        {
            cout << "Voter ID already exists\n";
            return;
        }

        string name = readLine("Enter voter name: ");
        if (name.empty())
        {
            cout << "Name cannot be empty\n";
            return;
        }

        voters_.insert({id, Voter(id, name)});
        cout << "Voter registered successfully\n";
    }

    void deleteVoter()
    {

        int id;
        cout << "Enter voter ID to delete: ";
        if (!safeRead(id))
            return;

        auto it = voters_.find(id);
        if (it == voters_.end())
        {
            cout << "Voter not found\n";
            return;
        }

        if (it->second.hasVoted())
        {
            cout << "Cannot delete voter with a pending or cast vote\n";
            return;
        }

        voters_.erase(it);
        cout << "Voter deleted successfully\n";
    }

    void showVoters() const
    {

        if (voters_.empty())
        {
            cout << "No voters registered\n";
            return;
        }

        cout << "\nRegistered Voters:\n";
        for (const auto &pair : voters_)
        {
            const Voter &v = pair.second;
            cout << "  " << v.getId() << " - " << v.getName();
            if (v.hasVoted())
                cout << " (Voted)";
            cout << "\n";
        }
    }

    /* ----- candidate management ----- */

    void addCandidate()
    {

        if (votingClosed_)
        {
            cout << "Cannot add candidates after voting has closed\n";
            return;
        }

        int id;
        cout << "Enter candidate ID: ";
        if (!safeRead(id))
            return;

        if (candidateExists(id))
        {
            cout << "Candidate ID already exists\n";
            return;
        }

        string name = readLine("Enter candidate name: ");
        if (name.empty())
        {
            cout << "Name cannot be empty\n";
            return;
        }

        candidates_.insert({id, Candidate(id, name)});
        cout << "Candidate added successfully\n";
    }

    void deleteCandidate()
    {

        if (votingClosed_)
        {
            cout << "Cannot delete candidates after voting has closed\n";
            return;
        }

        int id;
        cout << "Enter candidate ID to delete: ";
        if (!safeRead(id))
            return;

        if (!candidateExists(id))
        {
            cout << "Candidate not found\n";
            return;
        }

        queue<Vote> temp;
        bool pendingVoteFound = false;

        while (!voteQueue_.empty())
        {
            Vote v = voteQueue_.front();
            voteQueue_.pop();

            if (v.getCandidateID() == id)
            {
                pendingVoteFound = true;
            }

            temp.push(v);
        }

        voteQueue_ = temp;

        if (pendingVoteFound)
        {
            cout << "Cannot delete candidate with pending votes\n";
            return;
        }

        candidates_.erase(id);

        cout << "Candidate removed\n";
    }

    void showCandidates() const
    {

        if (candidates_.empty())
        {
            cout << "No candidates registered\n";
            return;
        }

        cout << "\nCandidates:\n";
        for (const auto &pair : candidates_)
        {
            const Candidate &c = pair.second;
            cout << "  " << c.getId() << " - " << c.getName()
                 << " (Votes: " << c.getVotes() << ")\n";
        }
    }

    void showCandidates1() const
    {

        if (candidates_.empty())
        {
            cout << "No candidates registered\n";
            return;
        }

        cout << "\nCandidates:\n";
        for (const auto &pair : candidates_)
        {
            const Candidate &c = pair.second;
            cout << "  " << c.getId() << " - " << c.getName()
                 << "\n";
        }
    }

    /* ----- voting ----- */

    void castVote()
    {

        if (votingClosed_)
        {
            cout << "Voting is closed\n";
            return;
        }

        if (candidates_.empty())
        {
            cout << "No candidates available to vote for\n";
            return;
        }

        int voterID;
        cout << "Enter voter ID: ";
        if (!safeRead(voterID))
            return;

        auto vIt = voters_.find(voterID);
        if (vIt == voters_.end())
        {
            cout << "Invalid voter ID\n";
            return;
        }

        if (vIt->second.hasVoted())
        {
            cout << "This voter has already voted\n";
            return;
        }

        showCandidates1();

        int candidateID;
        cout << "Enter candidate ID: ";
        if (!safeRead(candidateID))
            return;

        if (!candidateExists(candidateID))
        {
            cout << "Invalid candidate ID\n";
            return;
        }

        voteQueue_.push(Vote(voterID, candidateID));
        vIt->second.markVoted();

        cout << "Vote cast successfully\n";
    }

    void processVotes()
    {

        if (votingClosed_)
        {
            cout << "Votes have already been processed\n";
            return;
        }

        if (voteQueue_.empty())
        {
            cout << "No votes in queue\n";
            return;
        }

        votingClosed_ = true;
        processVotesInternal();

        cout << "All votes processed. Voting is now closed.\n";
    }

    /* ----- results ----- */

    void showResults()
    {

        if (candidates_.empty())
        {
            cout << "No candidates registered\n";
            return;
        }

        if (!voteQueue_.empty())
        {
            cout << "Processing pending votes first...\n";
            votingClosed_ = true;
            processVotesInternal();
        }

        int maxVotes = 0;
        for (const auto &pair : candidates_)
            maxVotes = max(maxVotes, pair.second.getVotes());

        cout << "\n--- Election Results ---\n";
        for (const auto &pair : candidates_)
        {
            const Candidate &c = pair.second;
            cout << "  " << c.getName() << " : " << c.getVotes() << " votes\n";
        }

        cout << "\nWinner(s):\n";
        for (const auto &pair : candidates_)
        {
            if (pair.second.getVotes() == maxVotes)
                cout << "  " << pair.second.getName()
                     << " with " << maxVotes << " votes\n";
        }
    }

    /* ----- audit log ----- */

    void showAuditLog() const
    {

        if (auditLog_.empty())
        {
            cout << "No votes have been processed yet\n";
            return;
        }

        cout << "\n--- Vote Audit Log ---\n";
        for (const auto &v : auditLog_)
        {
            cout << "  Voter " << v.getVoterID()
                 << "  ->  Candidate " << v.getCandidateID() << "\n";
        }
        cout << "Total processed: " << auditLog_.size() << " vote(s)\n";
    }
};

/* ---------- MAIN ---------- */

int main()
{

    VotingSystem system;

    int choice;

    while (true)
    {

        cout << "\n===== ONLINE VOTING SYSTEM =====\n";
        cout << " 1  Register Voter\n";
        cout << " 2  Delete Voter\n";
        cout << " 3  Show Voters\n";
        cout << " 4  Add Candidate\n";
        cout << " 5  Delete Candidate\n";
        cout << " 6  Show Candidates\n";
        cout << " 7  Cast Vote\n";
        cout << " 8  Process Votes\n";
        cout << " 9  Show Results\n";
        cout << "10  Audit Log\n";
        cout << "11  Exit\n";
        cout << "Choice: ";

        if (!safeRead(choice))
            continue;

        switch (choice)
        {

        case 1:
            system.registerVoter();
            break;
        case 2:
            system.deleteVoter();
            break;
        case 3:
            system.showVoters();
            break;
        case 4:
            system.addCandidate();
            break;
        case 5:
            system.deleteCandidate();
            break;
        case 6:
            system.showCandidates();
            break;
        case 7:
            system.castVote();
            break;
        case 8:
            system.processVotes();
            break;
        case 9:
            system.showResults();
            break;
        case 10:
            system.showAuditLog();
            break;
        case 11:
            cout << "Goodbye\n";
            return 0;
        default:
            cout << "Invalid option\n";
        }
    }
    return 0;
}