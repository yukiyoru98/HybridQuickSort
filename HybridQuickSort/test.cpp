// _QUICK_SORT_AND_INSERTION_SORT_
# include <iostream>
# include <fstream>
# include <ctime>
# include <iomanip>

using namespace std;

void InsertionSort(int[], int, int);
void ModifiedQuickSort(int[], int ,int, int);
int Partition(int[], int, int);

int main() {
    // check speed
    double START,END;
        

    // read file
    fstream data;
    data.open("10000input.txt", ios::in);
    if (!data) {
        cout << "Fail to open file!!!" << endl;
    }
    int size = 0;                //input size
    data >> size;                //first element is # of keys
    int *a = new int[size];        //dynamic array

    // puts keys from file to array
    for (int i = 0; i < size; i++) {
        data >> a[i];
    }
    data.close();
    
    // build a tmp array to keep origin array's value
    int TmpArray[size];
    for(int i = 0; i < size; i++)
        TmpArray[i] = a[i];
    
    
    // do quick sort until each subarray is of length k
    // then use insertion sort instead
    int k; // do quick sort until subarray's length <= k
    double t; // run time
    double timeTmp = 99999.0;
    int kTmp = 0;
    for (k=1; k<10000; k++){
        START = clock();
        /*---要計算的程式效率區域---*/
            
        ModifiedQuickSort(a, 1, size, k);
        END = clock();
        t = (END - START) / CLOCKS_PER_SEC;
        // print how long it takes to calculate
        
        if(t < timeTmp){
            timeTmp = t;
            kTmp = k;
        }
        cout <<  t << endl;
        if(k!=699){
            for(int i = 0; i < size; i++)
                a[i] = TmpArray[i];
        }
    }
    cout << "Shortest time is " << timeTmp << " with k = " << kTmp << endl;
    /*
    
    int k = 663;
    Start = clock();
    ModifiedQuickSort(a, 1, size, k);
    End = clock();
    cout << fixed << setprecision(4) << (End - Start) / CLOCKS_PER_SEC << endl;
    */
    int pp = 0;
    for (int i = 0 ; i < 10000 ; i++){
        if(a[i] != i+1)
            pp++;
    }
    cout << "pp = " << pp << endl;

    // output array
    data.open("output.txt", ios::out);
    data << size << endl;
    for (int i = 0; i < size; i++) {
        data << a[i] << endl;
    }
    data.close();

    // system("pause");

    return 0;
}

void ModifiedQuickSort(int A[], int p, int r, int k) {
    if (p < r) {
        int q = Partition(A, p, r);    // pick the pivot
        if((q-p) <= k){    // if length of subarray <= k
            // do insertion sort
            InsertionSort(A, p, q-1);
        }
        else{
            // do qucik sort
            ModifiedQuickSort(A, p, q-1, k);
        }
        if((r-q) <= k){    // if length of subarray <= k
            // do insertion sort
            InsertionSort(A, q+1, r);
        }
        else{
            // do qucik sort
            ModifiedQuickSort(A, q+1, r, k);
        }
        
    }
}

int Partition(int A[], int p, int r) {
    // Suppose there are 2 group: elements <= pivot & elements > pivot
    // called them S & B
    int x = A[r - 1];    // pivot
    int i = p - 1;        // i indicates the last element of S
    int tmp = 0;        // for swapping
    
    for (int j = p; j < r; j++) {
        if (A[j - 1] <= x) {    // if element is smaller than pivot
            // swap it with the first element of B
            i = i + 1;
            tmp = A[j - 1];
            A[j - 1] = A[i - 1];
            A[i - 1] = tmp;
        }
    }
    /*
    Now that all elements of S is on the left side
    and elements of B is on the right side
    To put pivot between S & B, swap it and the first element of B
    */
    tmp = A[r - 1];
    A[r - 1] = A[i];
    A[i] = tmp;
    // return pivot
    return i+1;
}
void InsertionSort(int A[], int p, int r) {
    int key = 0;
    int i = 0;
    for (int j = p + 1; j <= r; j++) {
        key = A[j - 1];        // next element after sorted array
        i = j - 1;
        while (i > 0 && A[i - 1] > key) {    // if the former element is bigger
            A[i] = A[i - 1];        // then push that element backward by 1
            i = i - 1;
        }
        A[i] = key;                    // insert the key to proper place in sorted array
    }
}
