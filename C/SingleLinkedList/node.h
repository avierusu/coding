/**
 * This header file defines the generic functionality
 * of a single linked list, defining a node and important
 * functions for managing the list
 */

// Define a generic node that will be a part of a single linked list
typedef struct node{
    // NOTE: the type "element" will not be recognized by the compiler
    // in this file, and it will be flagged as an error. We will define
    // "element" in the header file that defines a student record struct
    element data;
    // next points to the next node in the linked list
    // If it is null, you've reached the end of the list
    struct node *nextNode;
} Node;

/**
 * Every linked list should support these following 8 functions:
 * Adding a new node:
 * 1. At the head
 * 2. In the middle
 * 3. At the end
 * 
 * 4. Traverse the linked list
 * 
 * Deleting a node:
 * 5. From the head
 * 6. From the middle
 * 7. From the end
 * 
 * 8. Destroy the entire linked list
 */

// This function allocates space in memory to store a new node and returns the pointer
Node* createNode(){
    Node *nodePtr;

    // calloc() allocates memory for a new node and initializes all values to 0
    nodePtr = (Node*) calloc(1, sizeof(Node));

    // Check if space was allocated successfully
    if (nodePtr == NULL){
        printf("\nUnable to allocate memory space for the node");
        exit(1);
    }

    return nodePtr;
}

// This covers functionality 1 (add node at head)
// This function allocates memory for a new node and adds it to the beginning of the linked list
void addNodeAtHead(Node **headNode, element dataToAdd){
    // Create and allocate memory for a new node
    Node *newNode = createNode();

    // Copy the data into the new node
    newNode->data = dataToAdd;

    // Point the new node's pointer to the old head node
    newNode->nextNode = *headNode;

    // Store the new node's address into headNode
    *headNode = newNode;
}

// This covers functionalities 2 & 3 (add node at middle and end)
// This function allocates memory for a new node and adds it after the provided previous node
void addNode(Node *prevNode, element dataToAdd){
    // Create and allocate memory for a new node
    Node *newNode = createNode();

    // Copy the data into the new node
    newNode->data = dataToAdd;

    // Store the previous node's pointer in the new node's pointer
    newNode->nextNode = prevNode->nextNode;

    // Store the new node's address into the previous node's pointer
    prevNode->nextNode = newNode;
}

// This covers functionality 5 (delete from head)
// This function reclaims the memory allocated from the first node in the linked list
void deleteNodeAtHead(Node **headNode){
    // Create a temporary pointer to hold the address of the first node to delete
    Node *firstNode;

    // Store the address of the head node in the temporary pointer
    firstNode = *headNode;

    // Store the next node's address into headNode
    *headNode = (*headNode)->nextNode;

    // Free the memory space allocated to the first node
    free(firstNode);
}

// This covers functionalities 6 & 7 (delete from the middle and the end)
// This function reclaims the memory allocated from the node we wish to delete
void deleteNode(Node *prevNode){
    // Create a temporary pointer to hold the address of the current node to delete
    Node *currentNode;

    // Store the address of the current node in the temporary pointer
    currentNode = prevNode->nextNode;

    // Point the previous node's pointer to the address of the next node
    prevNode->nextNode = currentNode->nextNode;

    // Free the memory space allocated to the current node
    free(currentNode);
}

// This covers funcionality 8 (destroy the entire linked list)
// This function internally traverses through each node (functionality 4) and deletes the node
// until the next node is null
void destroyList(Node **headNode){
    // Create a temporary pointer to hold the address of the head node
    Node *currentNode;
    
    // Traverse through each node until the end of the linked list
    while ((*headNode) != NULL){
        // Store the address of the head node in the current node pointer
        currentNode = (*headNode);

        // Store the address of the next node in the head node's pointer
        // If the current node points to null, head node will become null
        (*headNode) = (*headNode)->nextNode;

        // Free the memory space allocated to the current node
        free(currentNode);

        // Prevent accidental use-after-free bugs
        currentNode = NULL;
    }
}