/**
 * ============================================================================
 * Project: Hash Table Using Mid-Square Hashing and Separate Chaining
 * Test Suite: Automated Unit and Invariant Verification
 * ============================================================================
 * Student: Soham Balaji Ramshette | PRN: 202501100069
 * Subject: Data Structures (Course Code: 2310212 T)
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

const int TABLE_SIZE = 11;

// Allocation tracking for memory leak verification
static int g_allocCount = 0;
static int g_deallocCount = 0;

struct TestNode {
    int key;
    TestNode* next;

    TestNode(int k) : key(k), next(nullptr) {
        g_allocCount++;
    }

    ~TestNode() {
        g_deallocCount++;
    }
};

int midSquareHash(int key, int tableSize, int &square, std::string &fourDigitStr, std::string &midStr, int &midDigits) {
    square = key * key;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << square;
    fourDigitStr = oss.str();
    midStr = fourDigitStr.substr(1, 2);
    midDigits = std::stoi(midStr);
    return midDigits % tableSize;
}

int midSquareHash(int key, int tableSize) {
    int square = 0;
    std::string fourDigitStr = "";
    std::string midStr = "";
    int midDigits = 0;
    return midSquareHash(key, tableSize, square, fourDigitStr, midStr, midDigits);
}

bool insertKey(TestNode* table[], int key, int tableSize, int &index, bool &isCollision) {
    index = midSquareHash(key, tableSize);
    TestNode* newNode = new TestNode(key);
    
    if (table[index] == nullptr) {
        table[index] = newNode;
        isCollision = false;
        return true;
    }
    
    isCollision = true;
    TestNode* current = table[index];
    
    if (current->key == key) {
        delete newNode;
        return false;
    }
    
    while (current->next != nullptr) {
        if (current->key == key) {
            delete newNode;
            return false;
        }
        current = current->next;
    }
    
    if (current->key == key) {
        delete newNode;
        return false;
    }
    
    current->next = newNode;
    return true;
}

void freeHashTable(TestNode* table[], int tableSize) {
    for (int i = 0; i < tableSize; ++i) {
        TestNode* current = table[i];
        while (current != nullptr) {
            TestNode* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}

int main() {
    std::cout << "========================================================================\n";
    std::cout << " RUNNING AUTOMATED UNIT TESTS FOR HASH TABLE IMPLEMENTATION\n";
    std::cout << " Student: Soham Balaji Ramshette | PRN: 202501100069\n";
    std::cout << "========================================================================\n\n";

    // --- TEST 1: Personalized Dataset Insertion ---
    const std::vector<int> dataset = {
        69, 82, 95, 8, 21, 34, 47, 60, 73, 86, 99, 12, 25, 38, 51, 64, 77, 90, 3, 16
    };
    TestNode* table[TABLE_SIZE] = { nullptr };
    int totalInserted = 0;
    int totalCollisions = 0;

    for (int key : dataset) {
        int idx = -1;
        bool isCol = false;
        if (insertKey(table, key, TABLE_SIZE, idx, isCol)) {
            totalInserted++;
            if (isCol) totalCollisions++;
        }
    }
    std::cout << "[PASS] Test 1: Dataset Insertion. Total Inserted: " << totalInserted 
              << "/20, Total Collisions: " << totalCollisions << "\n";
    assert(totalInserted == 20);
    assert(totalCollisions == 11);

    // --- TEST 2: Mid-Square Hash Calculation Examples ---
    int sq = 0, midDig = 0;
    std::string fStr, mStr;

    int idx69 = midSquareHash(69, TABLE_SIZE, sq, fStr, mStr, midDig);
    assert(sq == 4761 && fStr == "4761" && mStr == "76" && idx69 == 10);

    int idx82 = midSquareHash(82, TABLE_SIZE, sq, fStr, mStr, midDig);
    assert(sq == 6724 && fStr == "6724" && mStr == "72" && idx82 == 6);

    int idx8 = midSquareHash(8, TABLE_SIZE, sq, fStr, mStr, midDig);
    assert(sq == 64 && fStr == "0064" && mStr == "06" && idx8 == 6);

    int idx3 = midSquareHash(3, TABLE_SIZE, sq, fStr, mStr, midDig);
    assert(sq == 9 && fStr == "0009" && mStr == "00" && idx3 == 0);
    std::cout << "[PASS] Test 2: Mid-Square Hash Calculations (69->10, 82->6, 8->6, 3->0)\n";

    // --- TEST 3: Collision Handling in Chains ---
    assert(table[6]->key == 82 && table[6]->next->key == 8 && table[6]->next->next->key == 86);
    assert(table[10]->key == 69 && table[10]->next->key == 73 && table[10]->next->next->key == 90);
    assert(table[0]->key == 21 && table[0]->next->key == 38 && table[0]->next->next->key == 3);
    std::cout << "[PASS] Test 3: Collision Resolution Order (Index 6, 10, 0)\n";

    // --- TEST 4: Empty Buckets Verification ---
    assert(table[1] == nullptr);
    assert(table[8] == nullptr);
    std::cout << "[PASS] Test 4: Empty Buckets (Index 1 and Index 8 are NULL)\n";

    // --- TEST 5: Duplicate Key Rejection ---
    int dummyIdx = -1;
    bool dummyCol = false;
    int allocsBeforeDup = g_allocCount;
    int deallocsBeforeDup = g_deallocCount;

    bool dupHead = insertKey(table, 69, TABLE_SIZE, dummyIdx, dummyCol);
    bool dupMid = insertKey(table, 8, TABLE_SIZE, dummyIdx, dummyCol);
    bool dupTail = insertKey(table, 86, TABLE_SIZE, dummyIdx, dummyCol);

    assert(!dupHead && !dupMid && !dupTail);
    assert((g_allocCount - allocsBeforeDup) == (g_deallocCount - deallocsBeforeDup));
    std::cout << "[PASS] Test 5: Duplicate Rejection (Keys 69, 8, 86 rejected with zero leak)\n";

    // --- TEST 6: Memory Management Parity ---
    freeHashTable(table, TABLE_SIZE);
    assert(g_allocCount == g_deallocCount);
    for (int i = 0; i < TABLE_SIZE; ++i) {
        assert(table[i] == nullptr);
    }
    std::cout << "[PASS] Test 6: Memory Management (Allocations: " << g_allocCount 
              << ", Deallocations: " << g_deallocCount << ", Leaks: 0)\n";

    std::cout << "\n========================================================================\n";
    std::cout << " ALL 6 AUTOMATED UNIT TESTS COMPLETED SUCCESSFULLY!\n";
    std::cout << "========================================================================\n";
    return 0;
}
