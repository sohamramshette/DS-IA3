# Debugging & Testing Log

## Project Information
- **Student Name:** Soham Balaji Ramshette
- **PRN:** 202501100069
- **Subject:** Data Structures (Course Code: 2310212 T)
- **College:** MIT Academy of Engineering, Alandi
- **Project Title:** Hash Table Using Mid-Square Hashing and Separate Chaining
- **Domain Scenario:** Mango Varieties Inventory
- **Personalized Seed:** 69
- **Table Size ($M$):** 11 (Configurable constant)
- **Dataset Size ($N$):** 20 keys

---

## 1. Commit-by-Commit Development & Testing Log

| Entry ID | Commit Hash | Milestone / Topic | Primary Activity | Key Observation or Challenge | Resolution / Verification |
| :---: | :---: | :--- | :--- | :--- | :--- |
| **01** | `00d2f51` | Environment & Project Setup | Repository structure, `.gitignore`, initial documentation | OneDrive cloud filter driver blocked direct binary launch (`ERROR_NOT_SUPPORTED`) | Verified GCC compilation; redirected test binary execution via `$env:TEMP` |
| **02** | `8f32674` | Mid-Square Hash Function | Implementation of square, padding, and middle-digit slicing | Squares $< 1000$ (e.g., $8^2=64, 3^2=9$) caused potential substring bounds errors | Left-padded with `std::setfill('0') << std::setw(4)` to guarantee exact 4 digits |
| **03** | `9bde943` | Separate Chaining Resolution | Linked-list node structure, insertion, and memory cleanup | Maintaining FIFO chain order upon collision and rejecting duplicate entries | Traversed to chain tail for append; verified duplicate detection before allocation |
| **04** | `122b955` | Formatted Console Reporting | Viva-ready output, step-by-step trace, final table | Clear visual distinction needed between `[NEW CHAIN]` and `[COLLISION]` | Formatted table with aligned columns; empty buckets explicitly display `NULL` |
| **05** | `3a08a20` | Automated Unit Test Suite | Comprehensive unit test suite in `tests/test_hash_table.cpp` | Verifying heap memory cleanup without third-party leak analyzers | Built instrumented node counter (`g_allocCount` vs `g_deallocCount`); 0 leaks confirmed |
| **06** | `3c29f84` | Mathematical Trace & Audit | Full 20-row trace calculation and documentation audit | Ensuring 100% concordance between hand-calculations and terminal output | Verified exact match for all 20 keys, 11 collisions, and buckets 0 to 10 |

---

## 2. Detailed Technical Observations per Commit

### Commit 1 (`00d2f51`): Initial Project Setup & Workspace Execution Failure
- **Development Activity:** Created the project directory structure (`src/`, `docs/`, `screenshots/`, `tests/`), configured `.gitignore` for standard C++ build artifacts, authored initial README documentation with student parameters (PRN 202501100069, Seed 69, Table Size 11), and created the skeleton `src/main.cpp`.
- **Issue & Genuine Failure Encountered:** During initial compilation testing using MinGW GCC, the executable `test_setup.exe` compiled successfully with return code 0, but executing `.\test_setup.exe` directly inside PowerShell produced a system failure: `Program 'test_setup.exe' failed to run: The request is not supported` (`ApplicationFailedException`, Native error `ERROR_NOT_SUPPORTED` / `0x80070032`). Analysis revealed that the project resided in a live OneDrive-synced directory where the Windows cloud file system filter driver (`cldflt.sys`) locks newly created, unhydrated binary reparse points from immediate in-place process execution.
- **Resolution & Outcome:** Verified that the compiler toolchain (`g++ 6.3.0`) was completely intact and functional. For direct execution and automated test runs, binaries are executed via `$env:TEMP` or after hydration, resolving the OS-level filter driver lock cleanly without altering any project files.

### Commit 2 (`8f32674`): Mid-Square Hash Function & Padding Verification
- **Development Activity:** Implemented the core `midSquareHash()` function in `src/main.cpp` and created the formatted calculation display table `displayHashCalculations()`.
- **Issue & Observation Encountered:** Small keys in the personalized dataset such as Key `8` ($8^2 = 64$) and Key `3` ($3^2 = 9$) yield 2-digit and 1-digit squares. If middle digits are extracted naively using string indexing or integer arithmetic assuming a 4-digit square, attempting `s.substr(1, 2)` on an unpadded string like `"64"` or `"9"` causes a `std::out_of_range` exception or extracts erroneous digits.
- **Resolution & Outcome:** Handled this edge case by formatting the squared integer through `std::ostringstream` with `std::setfill('0') << std::setw(4) << square`. This guarantees an exact 4-character string representation (`"0064"`, `"0009"`), ensuring that `s.substr(1, 2)` consistently extracts index 1 and 2: `"06"` ($6 \pmod{11} = 6$) and `"00"` ($0 \pmod{11} = 0$), matching theoretical specifications.

### Commit 3 (`9bde943`): Separate Chaining & Collision Order Handling
- **Development Activity:** Defined `struct Node` for singly linked lists, initialized the table head pointer array `Node* hashTable[TABLE_SIZE] = { nullptr }`, and implemented `insertKey()` and `freeHashTable()`.
- **Issue & Observation Encountered:** Standard separate chaining can insert new nodes either at the head or at the tail. However, academic specifications require preserving the chronological FIFO insertion order within each chain during collisions (e.g., Index 6 must contain `82 -> 8 -> 86` in exact insertion order, not reversed `86 -> 8 -> 82`). Additionally, duplicate key insertions needed guard checks to prevent memory leaks from unused node allocations.
- **Resolution & Outcome:** Implemented tail-traversal insertion: if the bucket is occupied, `insertKey()` traverses to the last node, verifying during traversal that the key does not already exist. If a duplicate is detected, the newly allocated node is deleted immediately and insertion aborts returning `false`. New colliding keys are linked to `current->next`, preserving insertion order.

### Commit 4 (`122b955`): Formatted Console Reporting & Trace Presentation
- **Development Activity:** Added `performInsertions()` to trace each key insertion step-by-step, implemented `displayHashTable()` to output the complete bucket layout, and added summary statistics reporting.
- **Issue & Observation Encountered:** In visual output, it was necessary to clearly communicate when a key established a new chain versus when a collision occurred, as well as ensure that empty buckets (Index 1 and Index 8) explicitly display `NULL` rather than being omitted or leaving blank lines, which can confuse evaluators during a viva.
- **Resolution & Outcome:** Standardized the trace output: Step $i$ explicitly logs whether the key triggered `[NEW CHAIN]` (head placement) or `[COLLISION]` (tail append). The final table traversal checks `table[i] == nullptr` to output `NULL` safely, and displays formatted summary statistics: 20/20 keys inserted, 11 total collisions, and load factor $\alpha = 1.82$.

### Commit 5 (`3a08a20`): Automated Unit Testing & Memory Leak Verification
- **Development Activity:** Authored `tests/test_hash_table.cpp`, a standalone test suite with assertions validating all 6 core project invariants: dataset insertion, hash calculation values, collision chaining sequences, empty buckets, duplicate rejection, and dynamic heap cleanup.
- **Testing Method & Observation:** To rigorously verify memory safety without external tools like Valgrind on Windows, an instrumented `TestNode` was implemented with static allocation and deallocation counters (`g_allocCount` and `g_deallocCount`). Tests verified that duplicate rejection attempts (keys 69, 8, 86) immediately deallocated their temporary nodes, and calling `freeHashTable()` deallocated all remaining 20 chain nodes.
- **Resolution & Outcome:** The test suite verified `g_allocCount == 23` and `g_deallocCount == 23` (net 0 active heap allocations remaining), and confirmed all table head pointers were reset to `nullptr`. The test suite compiles with `-std=c++11 -Wall -Wextra -pedantic` with 0 warnings and passes 100% of assertions.

### Commit 6 (`3c29f84`): Mathematical Trace-Match Verification & Documentation
- **Development Activity:** Completed [docs/trace_match_report.md](file:///c:/Users/lenovo/OneDrive/Desktop/Projects/DS%20IA/DS_IA3_HashTable/docs/trace_match_report.md) with complete mathematical derivations for all 20 keys, updated README build guides, and cross-referenced program output with manual calculations.
- **Observation & Concordance:** Hand calculations for each key's square, 4-digit zero-padded string, middle-two digits, and index modulo 11 were compared against the program's runtime output. Every single bucket chain (`Index 0: 21 -> 38 -> 3`, `Index 1: NULL`, `Index 2: 95`, `Index 3: 99 -> 12 -> 16`, `Index 4: 34 -> 77`, `Index 5: 60 -> 51`, `Index 6: 82 -> 8 -> 86`, `Index 7: 25`, `Index 8: NULL`, `Index 9: 47 -> 64`, `Index 10: 69 -> 73 -> 90`) achieved an **EXACT MATCH** with zero discrepancy.
- **Outcome:** Documentation provides complete theoretical and empirical evidence supporting the assignment, ready for viva demonstration.
