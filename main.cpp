#include <iostream>

#define ARRAY_SIZE 17  // size of array to be sorted
#define BUCKET_COUNT 6 // number of buckets to be used
#define INTERVAL 10    // interval of values in each bucket

using namespace std;

class Node // node for linked list (bucket)
{
public:
    int value;
    Node *next;
};

void print(int array[])
{
    for (int i = 0; i < ARRAY_SIZE; ++i) // for each item in array
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void print(Node *node) // print linked list (bucket)
{
    while (node != NULL)
    {
        cout << node->value << " "; // print value of current node
        node = node->next;          // move to next node
    }
    cout << endl;
}

void printAllBuckets(Node *buckets[])
{
    for (int i = 0; i < BUCKET_COUNT; ++i)
    {
        cout << "Bucket " << i << ": "; // bucket index
        print(buckets[i]);
    }
}

void setArrayFromBuckets(int array[], Node *buckets[]) // for adding sorted items from buckets to the array
{
    int index = 0;
    for (int i = 0; i < BUCKET_COUNT; ++i) // for each bucket
    {
        Node *current = buckets[i]; // set current node to first node in bucket
        while (current != NULL)     // while not end of bucket
        {
            array[index] = current->value; // set value of current node to array at index
            current = current->next;       // move to next node in bucket
            index++;                       // increment index
        }
    }
}

Node *insertionSort(Node *node) // insertion sort for linked list (bucket)
{
    Node *current = node; // set current node to first node in list
    Node *sorted = NULL;  // set sorted list to NULL

    while (current != NULL) // while not end of list
    {
        Node *next = current->next;                            // set next node to next node in list
        if (sorted == NULL || sorted->value >= current->value) // if sorted list is empty or value of current node is less than value of first node in sorted list
        {
            current->next = sorted; // set next node of current node to sorted list
            sorted = current;       // set current node as first node in sorted list
        }
        else // if value of current node is greater than value of first node in sorted list
        {
            Node *temp = sorted;                                             // set temp node to first node in sorted list
            while (temp->next != NULL && temp->next->value < current->value) // while not end of sorted list and value of next node in sorted list is less than value of current node
            {
                temp = temp->next; // move to next node in sorted list
            }
            current->next = temp->next; // set next node of current node to next node of temp node
            temp->next = current;       // set next node of temp node to current node
        }
        current = next; // move to next node in list
    }
    return sorted; // return sorted list
}

void BucketSort(int array[])
{
    Node *buckets[BUCKET_COUNT];
    for (int i = 0; i < BUCKET_COUNT; ++i) // initialize buckets
    {
        buckets[i] = NULL; // set each bucket to NULL
    }

    for (int i = 0; i < ARRAY_SIZE; ++i) // add items to buckets based on interval of their value
    {
        int bucketIndex = array[i] / INTERVAL; // get bucket index for current item from modulo of its value and interval
        Node *current = new Node();            // create new node for current item
        current->value = array[i];             // set value of current item to current node
        current->next = buckets[bucketIndex];  // add current item to the beginning of the bucket
        buckets[bucketIndex] = current;        // set current item as the first item in the bucket
    }

    cout << "Initial buckets: " << endl;
    printAllBuckets(buckets);

    for (int i = 0; i < BUCKET_COUNT; ++i) // sort each bucket
    {
        buckets[i] = insertionSort(buckets[i]);
    }

    cout << "-------------" << endl
         << "Sorted buckets: " << endl;
    printAllBuckets(buckets);

    setArrayFromBuckets(array, buckets);
    return;
}

int main(void)
{
    int array[ARRAY_SIZE] = {13, 17, 29, 24, 22, 5, 11, 42, 8, 52, 37, 32, 35, 47, 49, 51, 56}; // initialize array

    cout << "Initial array: " << endl;
    print(array);
    cout << "-------------" << endl;

    BucketSort(array);
    cout << "-------------" << endl;
    cout << "Sorted array: " << endl;
    print(array);
}