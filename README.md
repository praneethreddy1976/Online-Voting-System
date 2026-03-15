# Online Voting System (C++)

## Overview

The **Online Voting System** is a console-based application written in **C++** that simulates a digital election process.
The system allows administrators to manage voters and candidates, cast votes, process votes, and display election results.

This project demonstrates the use of **Data Structures and Object-Oriented Programming (OOP)** concepts using C++ STL containers such as **unordered_map, queue, and vector**.

The system ensures that:

* Each voter can vote **only once**
* Votes are processed **sequentially using a queue**
* All processed votes are recorded in an **audit log for transparency**

---

## Features

* Register new voters
* Delete existing voters
* View all registered voters
* Add new candidates
* Delete candidates with safety checks
* View candidate list
* Cast vote (one vote per voter)
* Queue-based vote processing
* Display election results
* Audit log for processed votes

---

## Data Structures Used

| Data Structure | Purpose                                             |
| -------------- | --------------------------------------------------- |
| unordered_map  | Store voters and candidates with fast lookup (O(1)) |
| queue          | Manage vote processing sequentially                 |
| vector         | Maintain an audit log of processed votes            |

---

## Object-Oriented Design

The program uses the following classes:

### Voter

Stores voter information:

* Voter ID
* Name
* Voting status

### Candidate

Stores candidate information:

* Candidate ID
* Candidate name
* Vote count

### Vote

Represents a vote transaction containing:

* Voter ID
* Candidate ID

### VotingSystem

Core system responsible for:

* Managing voters
* Managing candidates
* Handling vote casting
* Processing vote queue
* Generating election results
* Maintaining audit logs

---

## Default Data

### Default Voters

101 - Kohli
102 - Dhoni
103 - Rohit

### Default Candidates

1 - A
2 - B
3 - C

---

## Menu Options

1  Register Voter
2  Delete Voter
3  Show Voters
4  Add Candidate
5  Delete Candidate
6  Show Candidates
7  Cast Vote
8  Process Votes
9  Show Results
10 Audit Log
11 Exit

---

## Voting Process

1. Voters are registered in the system
2. Candidates are added to the election
3. A voter casts a vote
4. Votes are stored in a queue
5. Votes are processed sequentially
6. Candidate vote counts are updated
7. Election results are displayed

---

## Time Complexity

| Operation      | Complexity |
| -------------- | ---------- |
| Register voter | O(1)       |
| Delete voter   | O(1)       |
| Add candidate  | O(1)       |
| Cast vote      | O(1)       |
| Process votes  | O(n)       |
| Show results   | O(n)       |

---
## Example Output

```
===== ONLINE VOTING SYSTEM =====

1 Register Voter
2 Delete Voter
3 Show Voters
4 Add Candidate
5 Delete Candidate
6 Show Candidates
7 Cast Vote
8 Process Votes
9 Show Results
10 Audit Log
11 Exit
```

---

## Future Improvements

Possible enhancements include:

* File storage for persistent data
* Admin authentication system
* Real-time leader tracking
* Encryption for vote integrity
* Web-based interface

---

## Technologies Used

* C++
* STL (Standard Template Library)
* Object-Oriented Programming

---

## Author

Developed as a **Data Structures and Algorithms project in C++**.
