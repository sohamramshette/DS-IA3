/**
 * ============================================================================
 * Project: Hash Table Using Mid-Square Hashing and Separate Chaining
 * Subject: Data Structures (Course Code: 2310212 T)
 * College: MIT Academy of Engineering, Alandi
 * ============================================================================
 * Student Information:
 *   - Student Name : Soham Balaji Ramshette
 *   - PRN          : 202501100069
 * 
 * Personalization Parameters:
 *   - Seed                 : 69
 *   - Domain Scenario      : Mango Varieties
 *   - Dataset Size         : 20
 *   - Hashing Method       : Mid-Square Method
 *   - Collision Resolution : Separate Chaining (Singly Linked List)
 *   - Hash Table Size      : 11 (Configurable)
 *
 * Dataset Generation Formula:
 *   v[i] = (69 + 13 * i) % 100
 *
 * Dataset Keys (20 values):
 *   69, 82, 95, 8, 21, 34, 47, 60, 73, 86, 99, 12, 25, 38, 51, 64, 77, 90, 3, 16
 * ============================================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

// Configurable Hash Table Size
const int TABLE_SIZE = 11;

// Node structure for Separate Chaining (Singly Linked List)
struct Node {
    int key;
    Node* next;

    // Constructor to initialize a new node
    Node(int k) : key(k), next(nullptr) {}
};

/**
 * Mid-Square Hash Function
 * 1. Computes square of the key.
 * 2. Formats square as a 4-digit zero-padded string.
 * 3. Extracts middle two digits (indices 1 and 2).
 * 4. Returns (middleTwoDigits % TABLE_SIZE).
 */
int midSquareHash(int key, int tableSize, int &square, std::string &fourDigitStr, std::string &midStr, int &midDigits) {
    square = key * key;
    
    // Format into 4-digit representation with leading zeros
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << square;
    fourDigitStr = oss.str();
    
    // Extract middle two digits (characters at index 1 and index 2)
    midStr = fourDigitStr.substr(1, 2);
    midDigits = std::stoi(midStr);
    
    // Calculate hash index
    int hashIndex = midDigits % tableSize;
    return hashIndex;
}

// Convenience wrapper for hash calculation
int midSquareHash(int key, int tableSize) {
    int square = 0;
    std::string fourDigitStr = "";
    std::string midStr = "";
    int midDigits = 0;
    return midSquareHash(key, tableSize, square, fourDigitStr, midStr, midDigits);
}

/**
 * Inserts a key into the Hash Table using Separate Chaining.
 * Preserves insertion order by appending new nodes to the end of the chain.
 * Returns true if inserted, false if duplicate.
 */
bool insertKey(Node* table[], int key, int tableSize, int &index, bool &isCollision) {
    index = midSquareHash(key, tableSize);
    Node* newNode = new Node(key);
    
    // If the bucket is empty, start a new chain
    if (table[index] == nullptr) {
        table[index] = newNode;
        isCollision = false;
        return true;
    }
    
    // Collision occurred: bucket already contains one or more nodes
    isCollision = true;
    Node* current = table[index];
    
    // Check head for duplicate
    if (current->key == key) {
        delete newNode;
        return false;
    }
    
    // Traverse to the end of the chain
    while (current->next != nullptr) {
        if (current->key == key) {
            delete newNode;
            return false;
        }
        current = current->next;
    }
    
    // Check the last node for duplicate
    if (current->key == key) {
        delete newNode;
        return false;
    }
    
    // Append at the end of the existing chain
    current->next = newNode;
    return true;
}

/**
 * Displays Section A: Student and Project Details
 */
void displayStudentDetails() {
    std::cout << "========================================================================\n";
    std::cout << "                DATA STRUCTURES IA 3 - HASH TABLE PROJECT               \n";
    std::cout << "========================================================================\n";
    std::cout << " Student Name        : Soham Balaji Ramshette\n";
    std::cout << " PRN                 : 202501100069\n";
    std::cout << " Subject             : Data Structures (Course Code: 2310212 T)\n";
    std::cout << " College             : MIT Academy of Engineering, Alandi\n";
    std::cout << " Personalization Seed: 69\n";
    std::cout << " Domain Scenario     : Mango Varieties Inventory\n";
    std::cout << " Dataset Size        : 20 integers\n";
    std::cout << " Hash Table Size (M) : " << TABLE_SIZE << " (Configurable)\n";
    std::cout << " Hashing Method      : Mid-Square Method\n";
    std::cout << " Collision Handling  : Separate Chaining (Singly Linked List)\n";
    std::cout << "========================================================================\n\n";
}

/**
 * Displays Section B: Personalized Dataset
 */
void displayDataset(const std::vector<int>& dataset) {
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << " B. PERSONALIZED DATASET (20 Keys generated via (69 + 13 * i) % 100):\n";
    std::cout << "------------------------------------------------------------------------\n";
    for (size_t i = 0; i < dataset.size(); ++i) {
        std::cout << dataset[i];
        if (i + 1 < dataset.size()) {
            std::cout << ", ";
        }
        if ((i + 1) % 10 == 0) {
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

/**
 * Displays Section C: Detailed Mid-Square Hash Calculations Table
 */
void displayHashCalculations(const std::vector<int>& dataset, int tableSize) {
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << " C. MID-SQUARE HASH CALCULATION TABLE:\n";
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "+-----+--------+------------------------+---------------+------------+\n";
    std::cout << "| Key | Square | Four-digit (Padded)    | Middle digits | Hash index |\n";
    std::cout << "+-----+--------+------------------------+---------------+------------+\n";
    
    for (int key : dataset) {
        int square = 0;
        std::string fourDigits = "";
        std::string midStr = "";
        int midDigits = 0;
        int index = midSquareHash(key, tableSize, square, fourDigits, midStr, midDigits);
        
        std::cout << "| " << std::setw(3) << key << " "
                  << "| " << std::setw(6) << square << " "
                  << "| " << std::setw(22) << fourDigits << " "
                  << "| " << std::setw(13) << midStr << " "
                  << "| " << std::setw(10) << index << " |\n";
    }
    std::cout << "+-----+--------+------------------------+---------------+------------+\n\n";
}

/**
 * Inserts all dataset keys and displays Section D: Insertion Process
 */
void performInsertions(Node* table[], const std::vector<int>& dataset, int tableSize, int &totalInserted, int &totalCollisions) {
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << " D. STEP-BY-STEP INSERTION PROCESS:\n";
    std::cout << "------------------------------------------------------------------------\n";
    
    totalInserted = 0;
    totalCollisions = 0;
    
    for (size_t i = 0; i < dataset.size(); ++i) {
        int key = dataset[i];
        int index = -1;
        bool isCollision = false;
        
        bool success = insertKey(table, key, tableSize, index, isCollision);
        if (success) {
            totalInserted++;
            std::cout << "Step " << std::setw(2) << (i + 1) << ": Key " << std::setw(2) << key 
                      << " -> Hash Index " << std::setw(2) << index << " | ";
            if (isCollision) {
                totalCollisions++;
                std::cout << "[COLLISION] Appended to existing chain\n";
            } else {
                std::cout << "[NEW CHAIN]  Placed at head of bucket\n";
            }
        } else {
            std::cout << "Step " << std::setw(2) << (i + 1) << ": Key " << std::setw(2) << key 
                      << " -> [DUPLICATE] Ignored\n";
        }
    }
    std::cout << "\n";
}

/**
 * Displays Section E: Final Hash Table Structure
 */
void displayHashTable(Node* table[], int tableSize) {
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << " E. FINAL HASH TABLE (SEPARATE CHAINING):\n";
    std::cout << "------------------------------------------------------------------------\n";
    for (int i = 0; i < tableSize; ++i) {
        std::cout << "Index " << i << ": ";
        if (table[i] == nullptr) {
            std::cout << "NULL\n";
        } else {
            Node* current = table[i];
            while (current != nullptr) {
                std::cout << current->key;
                if (current->next != nullptr) {
                    std::cout << " -> ";
                }
                current = current->next;
            }
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

/**
 * Frees all dynamically allocated linked-list nodes to prevent memory leaks
 */
void freeHashTable(Node* table[], int tableSize) {
    for (int i = 0; i < tableSize; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}

int main() {
    // Personalized dataset of 20 integers generated using v[i] = (69 + 13 * i) % 100
    const std::vector<int> dataset = {
        69, 82, 95, 8, 21, 34, 47, 60, 73, 86, 99, 12, 25, 38, 51, 64, 77, 90, 3, 16
    };
    
    // Hash Table initialized to nullptr
    Node* hashTable[TABLE_SIZE] = { nullptr };
    
    // A. Display Student Details
    displayStudentDetails();
    
    // B. Display Personalized Dataset
    displayDataset(dataset);
    
    // C. Display Hash Calculations Table
    displayHashCalculations(dataset, TABLE_SIZE);
    
    // D. Perform Insertions & Trace Process
    int totalInserted = 0;
    int totalCollisions = 0;
    performInsertions(hashTable, dataset, TABLE_SIZE, totalInserted, totalCollisions);
    
    // E. Display Final Hash Table
    displayHashTable(hashTable, TABLE_SIZE);
    
    // F & G. Display Statistics
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << " SUMMARY STATISTICS:\n";
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << " F. Total Keys Inserted : " << totalInserted << " / " << dataset.size() << "\n";
    std::cout << " G. Total Collisions    : " << totalCollisions << "\n";
    std::cout << "    Load Factor (alpha) : " << std::fixed << std::setprecision(2) 
              << (static_cast<double>(totalInserted) / TABLE_SIZE) << "\n\n";
    
    // H. Conclusion Message
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << " H. CONCLUSION:\n";
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << " Mid-Square Hashing successfully scattered the 20 keys across the 11 buckets.\n";
    std::cout << " Collisions (" << totalCollisions << ") were resolved without data loss using Separate Chaining.\n";
    std::cout << " All 20 personalized mango variety keys are preserved in exact insertion order.\n";
    std::cout << " Memory dynamically allocated for all chains has been cleaned up safely.\n";
    std::cout << "========================================================================\n";
    
    // Cleanup dynamic memory
    freeHashTable(hashTable, TABLE_SIZE);
    
    return 0;
}
