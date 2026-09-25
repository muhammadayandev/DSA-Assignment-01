#include <iostream>
using namespace std;

void insertionSort(int *arr,int n){
    for(int i=1;i<n;i++){
        int key = arr[i];
        int j = i-1;

        while(j>=0 && arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;

        cout << "\nPass " << i << ": ";
        for(int k = 0;k<n;k++){
            cout << *(arr+k) << " ";
        }
    }
}



int main(){
    int n;
    cout << "How Many Cables Are Required: ";
    cin >> n;

    int *arr = new int[n];

    for(int i = 0;i<n; i++){
        cout << "Enter Size Of Cable " << i+1 << ": ";
        cin >> *(arr+i);
    }

    cout << "\nUnsorted List: ";
    for(int i = 0;i<n; i++){
        cout << *(arr+i) << " ";
    }

    insertionSort(arr,n);
    cout << "\nSorted List: ";
    for(int i = 0;i<n; i++){
        cout << *(arr+i) << " ";
    }
    delete[] arr;
    return 0;
}