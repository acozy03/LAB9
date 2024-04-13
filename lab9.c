#include <stdio.h>
#include <stdlib.h> // for malloc, free

#define HASH_SIZE 10 // Adjust the size according to your requirements

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Node for separate chaining
struct Node
{
    struct RecordType data;
    struct Node *next;
};

// Hash table structure
struct HashType
{
    struct Node *head; // Array of pointers to nodes
};

// Initialize hash table
void initializeHashTable(struct HashType *hashTable, int size)
{
    hashTable->head = (struct Node *)malloc(size * sizeof(struct Node));
    if (hashTable->head == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; ++i)
    {
        hashTable->head[i].next = NULL;
    }
}

// Compute the hash function
int hash(int x)
{
    // Simple hash function example
    return x % HASH_SIZE;
}

// Function to insert a record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType record)
{
    int index = hash(record.id); // Compute hash value
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); // Create new node
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = record; // Assign data to the new node
    newNode->next = hashTable->head[index].next; // Insert at the beginning
    hashTable->head[index].next = newNode; // Update head pointer
}

// Function to display records in the hash structure
void displayRecordsInHash(struct HashType *hashTable, int hashSize)
{
    printf("Records in the hash table:\n");
    for (int i = 0; i < hashSize; ++i)
    {
        struct Node *current = hashTable->head[i].next;
        printf("Index %d -> ", i);
        while (current != NULL)
        {
            printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Function to free memory allocated for the hash table
void freeHashTable(struct HashType *hashTable, int hashSize)
{
    for (int i = 0; i < hashSize; ++i)
    {
        struct Node *current = hashTable->head[i].next;
        while (current != NULL)
        {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable->head);
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    int hashSize = HASH_SIZE;
    struct HashType hashTable;

    initializeHashTable(&hashTable, hashSize);

    recordSz = parseData("input.txt", &pRecords); // You need to implement parseData function

    // Insert records into the hash table
    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(&hashTable, pRecords[i]);
    }

    // Display records in the hash table
    displayRecordsInHash(&hashTable, hashSize);

    // Free memory allocated for hash table
    freeHashTable(&hashTable, hashSize);

    // Free memory allocated for pRecords
    free(pRecords);

    return 0;
}
