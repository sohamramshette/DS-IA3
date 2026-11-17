# Debugging & Testing Log

## Project Information
- **Student Name:** Soham Balaji Ramshette
- **PRN:** 202501100069
- **Subject:** Data Structures (Course Code: 2310212 T)
- **Project Title:** Hash Table Using Mid-Square Hashing and Separate Chaining
- **Domain Scenario:** Mango Varieties Inventory
- **Personalized Seed:** 69
- **Table Size ($M$):** 11

---

## Log Entries

| Entry ID | Phase | Test Case / Scenario | Observed Behavior | Root Cause / Analysis | Resolution / Verification | Status |
| :---: | :---: | :--- | :--- | :--- | :--- | :---: |
| 01 | Phase 1 | Project Environment Setup | Directory structure and skeleton created | Initial repository configuration | Files created and verified in workspace | **PASS** |
| 02 | Phase 2 | Compiler Compatibility | MinGW GCC compiled standard C++11 source | Strict flag compliance required | Compiled cleanly with `-std=c++11 -Wall -Wextra` | **PASS** |
| 03 | Phase 3 | Test 1: Personalized Dataset Insertion | Exactly 20 keys inserted with 11 collisions | Total 20 records processed through loop | Verified key count = 20/20, Load Factor = 1.82 | **PASS** |
| 04 | Phase 3 | Test 2: Mid-Square Padding for Small Squares | Squares $< 1000$ (e.g. $8^2=64$, $3^2=9$) need leading zeros | Without zero-padding, substring index 1..2 would fail or give wrong digits | Used `std::setfill('0') << std::setw(4)` to format exact 4 digits (`0064`, `0009`) | **PASS** |
| 05 | Phase 3 | Test 3: Separate Chaining & Collision Order | Keys appended to tail of existing linked list | Chaining must preserve FIFO insertion sequence | Chains match expected order (e.g., Index 6: `82 -> 8 -> 86`) | **PASS** |
| 06 | Phase 3 | Test 4: Empty Buckets Display | Indices 1 and 8 have no keys assigned | Head pointers remain `nullptr` | Guard condition checked `table[i] == nullptr`, outputting `NULL` safely | **PASS** |
| 07 | Phase 3 | Test 5: Duplicate Key Rejection | Insertion of pre-existing keys (69, 8, 86) rejected | Duplicate keys must not be added to existing chains | `insertKey` traversed chain, detected existing key, freed temporary node, returned `false` | **PASS** |
| 08 | Phase 3 | Test 6: Dynamic Memory Deallocation | Heap nodes allocated via `new Node` must be freed | Risk of memory leak if head pointers discarded without traversing chains | `freeHashTable()` iterates each chain, deletes all nodes, sets heads to `nullptr` (0 leaks) | **PASS** |
| 09 | Phase 3 | Test 7: Strict Compiler Flags | Compiled using `-std=c++11 -Wall -Wextra -pedantic` | Checking for non-standard extensions or implicit type conversions | Zero errors, zero warnings generated | **PASS** |
