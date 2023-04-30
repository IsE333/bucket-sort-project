#include <iostream>
using namespace std;

void printArray(int arr[], int n)
{
    cout << "Array : " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int findMax(int arr[], int n)
{
    int i, max = arr[0], digits = 0;
    for (i = 1; i < n; i++) // finding max element from array
    {
        if (arr[i] > max)
            max = arr[i];
    }
    while (max > 0) // finding number of digits in max element
    {
        digits++;
        max = max / 10;
    }

    return digits;
}

void bucketSort(int arr[], int *bucket[], int numOfElements)
{
    static int sizeOfBucket[10], bucketIndex, l, divisor = 1;
    int digitCount;
    digitCount = findMax(arr, numOfElements); // Determine the number of digits in the maximum element of the array

    for (int m = 0; m < digitCount; m++) // Loop through the number of digits
    {
        for (int i = 0; i < 10; i++)
            sizeOfBucket[i] = 0;                // Initialize the size of each bucket to zero
        for (int i = 0; i < numOfElements; i++) // Loop through each element of the array
        {
            bucketIndex = (arr[i] / divisor) % 10;                   // Find the digit to use as an index in the bucket array
            bucket[bucketIndex][sizeOfBucket[bucketIndex]] = arr[i]; // Add the element to the corresponding bucket as last element
            sizeOfBucket[bucketIndex]++;                             // Increment the number of elements in that bucket
        }

        cout << endl
             << "Iteration " << m + 1 << " : ";

        // Copy the elements from the bucket array back to the original array
        l = 0;                       // Index counter for the original array
        for (int i = 0; i < 10; i++) // Loop through the bucket array
        {
            cout << endl
                 << "Bucket " << i << " : ";

            for (int k = 0; k < sizeOfBucket[i]; k++) // Loop through each element in the current bucket
            {
                cout << bucket[i][k] << " ";
                arr[l] = bucket[i][k]; // Copy the element back to the original array
                l++;
            }
        }
        divisor *= 10; // Move to the next digit
        cout << endl;

        printArray(arr, numOfElements);
    }
}

int main()
{
    int numOfElements, *arr, i;
    int *bucket[10];

    cout << "Enter no of element : ";
    cin >> numOfElements;
    arr = new int[numOfElements + 1];
    for (i = 0; i < 10; i++) // initializing bucket
        bucket[i] = new int[numOfElements];

    cout << "Enter array element : ";
    for (i = 0; i < numOfElements; i++)
        cin >> arr[i];

    bucketSort(arr, bucket, numOfElements);

    cin >> i; // to stop console from closing
    return 0;
}
