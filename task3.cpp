#include <iostream>
using namespace std;

void CombSort(int *arr, int n){
    int gap = n;
    bool swapped = true;

    while(gap>1 || swapped==true){
        gap = gap/1.3; //shrink factor 1.3
        if(gap<1){
            gap = 1;
        }

        swapped = false;
        for(int i = 0;i+gap<n;i++){
            if(arr[i] > arr[i+gap]){
                swap(arr[i], arr[i+gap]);
                swapped = true;
            }
        }

        cout << "\nGap: "  << gap << endl;
        for(int i = 0;i<n;i++){
            cout << *(arr+i) << " ";
        } 
    }
}


int main(){
    int n;
    cout << "How Many Weights Do You Want To Enter: ";
    cin >> n;

    int *arr = new int[n];
    for(int i = 0;i<n;i++){
        cout << "Enter Weight " << i+1 << ": ";
        cin >> *(arr+i);
    } 

    cout << "\nUnsorted Array: ";
    for(int i = 0;i<n;i++){
        cout << *(arr+i) << " ";
    } 

    CombSort(arr,n);

    cout << "\nSorted Array: ";
    for(int i = 0;i<n;i++){
        cout << *(arr+i) << " ";
    } 

    delete[] arr;

    return 0;
}