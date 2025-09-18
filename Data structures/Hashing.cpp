#include <bits/stdc++.h>
using namespace std;


// Hash Table class using Chaining
class HashTable
{
private:
    vector<list<int>> table; // Each slot contains a linked list
    int tableSize;

    int hashFunction(int key)
    {
        return key % tableSize;
    }

public:
    HashTable(int size) : tableSize(size)
    {
        table.resize(tableSize);
    }

    // Function to insert a key into the hash table
    void insert(int key)
    {
        int index = hashFunction(key);
        table[index].push_back(key); // Insert key at the appropriate chain
    }

    // Function to search for a key in the hash table
    bool search(int key)
    {
        int index = hashFunction(key);
        for (int element : table[index])
        {
            if (element == key)
            {
                return true;
            }
        }
        return false;
    }

    // Function to delete a key from the hash table
    void remove(int key)
    {
        int index = hashFunction(key);
        table[index].remove(key);
    }

    // Function to display the hash table
    void display()
    {
        for (int i = 0; i < tableSize; ++i)
        {
            cout << "Slot " << i << ": ";
            for (int element : table[i])
            {
                cout << element << " -> ";
            }
            cout << "NULL\n";
        }
    }
};
class OpenAddressingHashTable{
private:
    vector<int> table;
    vector<string> status; // Tracks if a slot is EMPTY, OCCUPIED, or REMOVED
    int tableSize;
    const string EMPTY = "EMPTY"; // Marker for an empty slot
    const string OCCUPIED = "OCCUPIED";
    const string REMOVED = "REMOVED"; // Marker for a removed slot

    int elementCount = 0;

    enum ProbingMethod
    {
        LINEAR,
        QUADRATIC,
        DOUBLE_HASH
    };
    ProbingMethod probingMethod;

    // Primary hash function
    int h1(int key)
    {
        return key % tableSize;
    }

    // Secondary hash function (used for double hashing)
    int h2(int key)
    {
        return 7 - (key % 7);
    }

public:
    // Constructor
    OpenAddressingHashTable(int size, string method) : tableSize(size)
    {
        table.resize(tableSize, -1); // Initialize with -1 for keys
        status.resize(tableSize, EMPTY);

        if (method == "linear")
        {
            probingMethod = LINEAR;
        }
        else if (method == "quadratic")
        {
            probingMethod = QUADRATIC;
        }
        else if (method == "double")
        {
            probingMethod = DOUBLE_HASH;
        }
        else
        {
            throw invalid_argument("Invalid probing method. Choose 'linear', 'quadratic', or 'double'.");
        }
    }

    // Insert a key into the hash table
    void insert(int key)
    {
        if (elementCount == tableSize - 1)
        {
            rehash();
        }

        int index = h1(key);
        int step = (probingMethod == DOUBLE_HASH) ? h2(key) : 1;

        for (int i = 0; i < tableSize; ++i)
        {
            int newIndex;
            if (probingMethod == LINEAR)
            {
                newIndex = (index + i) % tableSize;
            }
            else if (probingMethod == QUADRATIC)
            {
                newIndex = (index + i * i) % tableSize;
            }
            else
            { // DOUBLE_HASH
                newIndex = (index + i * step) % tableSize;
            }

            if (status[newIndex] == EMPTY || status[newIndex] == REMOVED)
            {
                table[newIndex] = key;
                status[newIndex] = OCCUPIED;
                ++elementCount;
                cout << "Inserted " << key << " at index " << newIndex << endl;
                return;
            }
        }
        cout << "Hash table is full, cannot insert " << key << endl;
    }

    // Search for a key in the hash table
    bool search(int key)
    {
        int index = h1(key);
        int step = (probingMethod == DOUBLE_HASH) ? h2(key) : 1;

        for (int i = 0; i < tableSize; ++i)
        {
            int newIndex;
            if (probingMethod == LINEAR)
            {
                newIndex = (index + i) % tableSize;
            }
            else if (probingMethod == QUADRATIC)
            {
                newIndex = (index + i * i) % tableSize;
            }
            else
            { // DOUBLE_HASH
                newIndex = (index + i * step) % tableSize;
            }

            if (status[newIndex] == EMPTY)
            {
                return false; // Key not found
            }
            if (status[newIndex] == OCCUPIED && table[newIndex] == key)
            {
                return true; // Key found
            }
        }
        return false; // Key not found after probing all slots
    }

    // Remove a key from the hash table
    void remove(int key)
    {
        int index = h1(key);
        int step = (probingMethod == DOUBLE_HASH) ? h2(key) : 1;

        for (int i = 0; i < tableSize; ++i)
        {
            int newIndex;
            if (probingMethod == LINEAR)
            {
                newIndex = (index + i) % tableSize;
            }
            else if (probingMethod == QUADRATIC)
            {
                newIndex = (index + i * i) % tableSize;
            }
            else
            { // DOUBLE_HASH
                newIndex = (index + i * step) % tableSize;
            }

            if (status[newIndex] == EMPTY)
            {
                cout << "Key " << key << " not found in the hash table." << endl;
                return;
            }
            if (status[newIndex] == OCCUPIED && table[newIndex] == key)
            {
                status[newIndex] = REMOVED;
                --elementCount;
                cout << "Deleted " << key << " from index " << newIndex << endl;
                return;
            }
        }
        cout << "Key " << key << " not found in the hash table." << endl;
    }

    // Display the hash table
    void display()
    {
        for (int i = 0; i < tableSize; ++i)
        {
            cout << "Slot " << i << ": ";
            if (status[i] == EMPTY)
            {
                cout << "EMPTY";
            }
            else if (status[i] == REMOVED)
            {
                cout << "REMOVED";
            }
            else
            {
                cout << table[i];
            }
            cout << endl;
        }
    }

    // Rehash function
    void rehash()
    {
        cout << "Rehashing: ";
        int oldSize = tableSize;
        tableSize *= 2; // Double the table size
        cout << "new table size is " << tableSize << endl;

        vector<int> oldTable = table;
        vector<string> oldStatus = status;

        table.assign(tableSize, -1);
        status.assign(tableSize, EMPTY);
        elementCount = 0;

        for (int i = 0; i < oldSize; ++i)
        {
            if (oldStatus[i] == OCCUPIED)
            {
                insert(oldTable[i]);
            }
        }
    }
};

int divisionHash(int key, int tableSize);
int multiplicationHash(int key, int tableSize, float constant);
int midSquareHash(int key, int tableSize);
int foldingHash(int key, int tableSize, int partSize);

void mainForTestCases();
void mainForMenu();

int main()
{
    // mainForTestCases();
    mainForMenu();
    return 0;
}

void displayMenu(){
    cout << "\n=========== Hashing Menu ===========\n";
    cout << "1. Division Hashing\n";
    cout << "2. Multiplication Hashing\n";
    cout << "3. Mid-Square Hashing\n";
    cout << "4. Folding Hashing\n";
    cout << "5. Chaining Hash Table\n";
    cout << "6. Open Addressing (Linear Probing)\n";
    cout << "7. Open Addressing (Quadratic Probing)\n";
    cout << "8. Open Addressing (Double Hashing)\n";
    cout << "9. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}


int divisionHash(int key, int tableSize)
{
    if (tableSize <= 0)
    {
        cerr << "Error: Table size must be greater than 0." << endl;
        return -1;
    }
    return key % tableSize;
}

int multiplicationHash(int key, int tableSize, float constant)
{
    // constant=0.618033 the best number which DOCTOR mentioned
    float temp = key * constant;
    temp -= int(temp);
    return floor(temp * tableSize);
}

// Function to perform Mid-Square Hashing
int midSquareHash(int key, int tableSize)
{
    if (tableSize <= 0)
    {
        cerr << "Error: Table size must be greater than 0." << endl;
        return -1;
    }

    long long squaredKey = static_cast<long long>(key) * key;

    // Determine the number of middle digits (r) based on table size
    int r = static_cast<int>(log10(tableSize)) + 1; // r = log10(n) + 1 to get the number of digits
    // Convert the squared value to a string
    string squaredStr = to_string(squaredKey);
    int len = squaredStr.length();

    //  Calculate the start index to extract the middle r digits
    int start = (len - r) / 2; // Center the extraction around the middle of the string

    // Extract r digits from the middle
    string midDigits = squaredStr.substr(start, r);

    int middleValue = stoi(midDigits);

    return middleValue % tableSize;
}

int foldingHash(int key, int tableSize, int partSize)
{
    if (tableSize <= 0)
    {
        cerr << "Error: Table size must be greater than 0." << endl;
        return -1;
    }

    // Convert the key to a string for easy manipulation
    string keyStr = to_string(key);

    //  Divide the key into parts
    int sum = 0; // To store the sum of parts

    for (size_t i = 0; i < keyStr.length(); i += partSize)
    {
        // Extract a part of size `partSize` (or remaining digits)
        string part = keyStr.substr(i, partSize);

        // Convert the part back to an integer and add to the sum
        sum += stoi(part);
    }

    return sum % tableSize;
}

void mainForTestCases()
{
    // Test cases for Hash Functions
    cout << "Testing Hash Functions:\n";

    // Division Hash
    cout << "Division Hash:\n";
    cout << "Key: 120, Table Size: 10, Hash: " << divisionHash(120, 10) << endl; // Expected: 0
    cout << "Key: 1234, Table Size: 7, Hash: " << divisionHash(1234, 7) << endl; // Expected: 2

    // Multiplication Hash
    cout << "\nMultiplication Hash:\n";
    cout << "Key: 120, Table Size: 10, Constant: 0.618033, Hash: " << multiplicationHash(120, 10, 0.618033) << endl;   // Expected :1
    cout << "Key: 1234, Table Size: 13, Constant: 0.618033, Hash: " << multiplicationHash(1234, 13, 0.618033) << endl; // Expected :8

    // Mid-Square Hash
    cout << "\nMid-Square Hash:\n";
    cout << "Key: 120, Table Size: 10, Hash: " << midSquareHash(120, 10) << endl;       // Expected: 4
    cout << "Key: 5642, Table Size: 1000, Hash: " << midSquareHash(5642, 1000) << endl; // Expected: 321

    // Folding Hash
    cout << "\nFolding Hash:\n";
    cout << "Key: 12345678, Table Size: 100, Part Size: 2, Hash: " << foldingHash(12345678, 100, 2) << endl; // Expected: 80
    cout << "Key: 87654321, Table Size: 100, Part Size: 3, Hash: " << foldingHash(87654321, 100, 3) << endl; // Expected: 40

    // Test cases for Hash Tables
    cout << "\nTesting Hash Tables:\n";

    // Chaining
    cout << "Chaining:\n";
    HashTable chainingTable(7); // Table size: 7
    chainingTable.insert(10);
    chainingTable.insert(20);
    chainingTable.insert(15);
    chainingTable.insert(7);
    chainingTable.display();
    cout << "Searching 15: " << (chainingTable.search(15) ? "Found" : "Not Found") << endl;
    cout << "Searching 19: " << (chainingTable.search(19) ? "Found" : "Not Found") << endl;
    cout << "Removing 15.\n";
    chainingTable.remove(15);
    chainingTable.display();

    // Open Addressing with Linear Probing
    cout << "\nOpen Addressing (Linear Probing):\n";
    OpenAddressingHashTable linearTable(7, "linear");
    linearTable.insert(10);
    linearTable.insert(20);
    linearTable.insert(15);
    linearTable.insert(1); // linear probing
    linearTable.insert(7);
    linearTable.display();
    cout << "Searching 15: " << (linearTable.search(15) ? "Found" : "Not Found") << endl;
    cout << "Removing 15.\n";
    linearTable.remove(15);
    linearTable.display();

    // Open Addressing with Quadratic Probing
    cout << "\nOpen Addressing (Quadratic Probing):\n";
    OpenAddressingHashTable quadraticTable(7, "quadratic");
    quadraticTable.insert(10);
    quadraticTable.insert(20);
    quadraticTable.insert(15);
    quadraticTable.insert(1);
    quadraticTable.insert(22); // quadratic proping 3aozin n7otha fi 1
    quadraticTable.insert(7);
    quadraticTable.display();
    cout << "Searching 20: " << (quadraticTable.search(20) ? "Found" : "Not Found") << endl;
    cout << "Removing 22.\n";
    quadraticTable.remove(22);
    quadraticTable.display();

    // Open Addressing with Double Hashing
    cout << "\nOpen Addressing (Double Hashing):\n";
    OpenAddressingHashTable doubleTable(7, "double");
    doubleTable.insert(10);
    doubleTable.insert(20);
    doubleTable.insert(15);
    doubleTable.insert(7);
    doubleTable.display();
    cout << "Searching 10: " << (doubleTable.search(10) ? "Found" : "Not Found") << endl;
    cout << "Removing 10.\n";
    doubleTable.remove(10);
    doubleTable.display();

}

void mainForMenu()
{
    
    int choice;
    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Division Hashing\n";
            int key, tableSize;
            cout << "Enter key and table size: ";
            cin >> key >> tableSize;
            cout << "Hash: " << divisionHash(key, tableSize) << endl;
            break;
        }
        case 2:
        {
            cout << "Multiplication Hashing\n";
            int key, tableSize;
            float constant;
            cout << "Enter key, table size, and constant (e.g., 0.618033): ";
            cin >> key >> tableSize >> constant;
            cout << "Hash: " << multiplicationHash(key, tableSize, constant) << endl;
            break;
        }
        case 3:
        {
            cout << "Mid-Square Hashing\n";
            int key, tableSize;
            cout << "Enter key and table size: ";
            cin >> key >> tableSize;
            cout << "Hash: " << midSquareHash(key, tableSize) << endl;
            break;
        }
        case 4:
        {
            cout << "Folding Hashing\n";
            int key, tableSize, partSize;
            cout << "Enter key, table size, and part size: ";
            cin >> key >> tableSize >> partSize;
            cout << "Hash: " << foldingHash(key, tableSize, partSize) << endl;
            break;
        }
        case 5:
        {
            cout << "Chaining Hash Table\n";
            int tableSize;
            cout << "Enter table size: ";
            cin >> tableSize;
            HashTable hashTable(tableSize);

            while (true)
            {
                int subChoice;
                cout << "\n1. Insert\n2. Search\n3. Remove\n4. Display\n5. Back to Main Menu\nEnter your choice: ";
                cin >> subChoice;

                if (subChoice == 1)
                {
                    int key;
                    cout << "Enter key to insert: ";
                    cin >> key;
                    hashTable.insert(key);
                }
                else if (subChoice == 2)
                {
                    int key;
                    cout << "Enter key to search: ";
                    cin >> key;
                    cout << (hashTable.search(key) ? "Found" : "Not Found") << endl;
                }
                else if (subChoice == 3)
                {
                    int key;
                    cout << "Enter key to remove: ";
                    cin >> key;
                    hashTable.remove(key);
                }
                else if (subChoice == 4)
                {
                    hashTable.display();
                }
                else
                {
                    break;
                }
            }
            break;
        }
        case 6:
        {
            cout << "Open Addressing (Linear Probing)\n";
            int tableSize;
            cout << "Enter table size: ";
            cin >> tableSize;
            OpenAddressingHashTable hashTable(tableSize, "linear");

            while (true)
            {
                int subChoice;
                cout << "1. Insert\n2. Search\n3. Remove\n4. Display\n5. Back to Main Menu\nEnter your choice: ";
                cin >> subChoice;

                if (subChoice == 1)
                {
                    int key;
                    cout << "Enter key to insert: ";
                    cin >> key;
                    hashTable.insert(key);
                }
                else if (subChoice == 2)
                {
                    int key;
                    cout << "Enter key to search: ";
                    cin >> key;
                    cout << (hashTable.search(key) ? "Found" : "Not Found") << endl;
                }
                else if (subChoice == 3)
                {
                    int key;
                    cout << "Enter key to remove: ";
                    cin >> key;
                    hashTable.remove(key);
                }
                else if (subChoice == 4)
                {
                    hashTable.display();
                }
                else
                {
                    break;
                }
            }
            break;
        }
        case 7:
        {
            cout << "Open Addressing (Quadratic Probing)\n";
            int tableSize;
            cout << "Enter table size: ";
            cin >> tableSize;
            OpenAddressingHashTable hashTable(tableSize, "quadratic");

            while (true)
            {
                int subChoice;
                cout << "1. Insert\n2. Search\n3. Remove\n4. Display\n5. Back to Main Menu\nEnter your choice: ";
                cin >> subChoice;

                if (subChoice == 1)
                {
                    int key;
                    cout << "Enter key to insert: ";
                    cin >> key;
                    hashTable.insert(key);
                }
                else if (subChoice == 2)
                {
                    int key;
                    cout << "Enter key to search: ";
                    cin >> key;
                    cout << (hashTable.search(key) ? "Found" : "Not Found") << endl;
                }
                else if (subChoice == 3)
                {
                    int key;
                    cout << "Enter key to remove: ";
                    cin >> key;
                    hashTable.remove(key);
                }
                else if (subChoice == 4)
                {
                    hashTable.display();
                }
                else
                {
                    break;
                }
            }
            break;
        }
        case 8:
        {
            cout << "Open Addressing (Double Hashing)\n";
            int tableSize;
            cout << "Enter table size: ";
            cin >> tableSize;
            OpenAddressingHashTable hashTable(tableSize, "double");

            while (true)
            {
                int subChoice;
                cout << "1. Insert\n2. Search\n3. Remove\n4. Display\n5. Back to Main Menu\nEnter your choice: ";
                cin >> subChoice;

                if (subChoice == 1)
                {
                    int key;
                    cout << "Enter key to insert: ";
                    cin >> key;
                    hashTable.insert(key);
                }
                else if (subChoice == 2)
                {
                    int key;
                    cout << "Enter key to search: ";
                    cin >> key;
                    cout << (hashTable.search(key) ? "Found" : "Not Found") << endl;
                }
                else if (subChoice == 3)
                {
                    int key;
                    cout << "Enter key to remove: ";
                    cin >> key;
                    hashTable.remove(key);
                }
                else if (subChoice == 4)
                {
                    hashTable.display();
                }
                else
                {
                    break;
                }
            }
            break;
        }
        case 9:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

}
