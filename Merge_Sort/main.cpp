#include <iostream>
#include <vector>
#include <thread>

using namespace std;
vector <int> arr;

void readInput();
void printArray();
void merge(int l, int m, int r);
void mergeSort(int l, int r);

/* -------------------------------------------
        READING THE INPUT FROM USER
------------------------------------------- */

void readInput()
{
    FILE* input;
    input = freopen("input.txt","r",stdin);
    int arraySize,temp;

    cin >> arraySize;

    for(int i = 0; i < arraySize; i++){
        cin >> temp;
        arr.push_back(temp);
    }

    fclose(input);
}

/* --------------------------------------------------------
                    M   E   R   G   E
--------------------------------------------------------- */

void merge(int l, int m, int r)
{
    vector<int> temp;
    int i = l, j = m + 1;

    while(i <= m && j <= r)
        arr[i] < arr[j] ? temp.push_back(arr[i++]) : temp.push_back(arr[j++]);

    while(i <= m)
        temp.push_back(arr[i++]);

    while(j <= r)
        temp.push_back(arr[j++]);

    for(int i = 0; i < temp.size(); i++)
        arr[l + i] = temp[i];
}

/*  -----------------------------------------------------------------
                            M E R G E S O R T
        1. Sort the right part
        2. sort the left part
        3. merge!
        l is for left index and r is right index of the Sub-array
    -----------------------------------------------------------------*/

void mergeSort(int l, int r)
{
    if(l < r)
    {
        int m = l + ( r - l ) / 2;

        thread t1{[&](){mergeSort(l, m);}};
        thread t2{[&](){mergeSort(m + 1, r);}};

        t1.join();
        t2.join();

        merge(l, m, r);
    }
}


void printArray()
{
    for(int num : arr)
        cout << num << " ";
}

int main()
{

    readInput();
    auto start = chrono::steady_clock::now();
    mergeSort(0, arr.size()-1);
    auto end = chrono::steady_clock::now();
    printArray();
    cout << "\nTime Executed: " << chrono::duration <double, nano> (end - start).count() << " ns" << endl;
    return 0;
}
