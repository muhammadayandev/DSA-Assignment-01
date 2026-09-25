#include <iostream>
using namespace std;

class Library{
    private:
    int n;
    int *arr;

    public:
    //default constructor
    Library(){
        n = 0;
        arr = nullptr;
    }

    //para constructor
    Library(int *array, int s){
        n = s;
        arr = new int[n];
        for(int i = 0;i<n;i++){
            *(arr+i) = *(array+i);
        }
    }

    //copy contructor
    Library(const Library &other){
        n = other.n;
        arr = new int[n];
        for(int i = 0;i<n;i++){
            *(arr+i) = other.arr[i];
        }   
    }

    void addNewShelf(int value, int pos){
        int *temp = new int[n+1];
        //copy old data till pos-1
        for(int i = 0;i< pos;i++){
            *(temp+i) = *(arr+i);
        }
        //add new value at desired pos
        temp[pos] = value;
        for(int i = pos;i<n;i++){ //copy next elements
            *(temp+i+1) = *(arr+i);
        } 
        //delete old array
        delete[] arr;
        //point old array to temporary array
        arr = temp;
        n++;
    }

    //sorting member function
    void insertionSort(){
        for(int i = 1;i<n;i++){
            int key =arr[i];
            int j = i-1;
            while(j>=0 && arr[j]>key){
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        }
    }

    //display
    void display()const{
        for(int i = 0;i<n;i++){
            cout << *(arr+i) << " ";
        }
        cout << endl;
    }

    //destructor
    ~Library(){
        delete[] arr;
    }
};

int main(){
    int n;
    cout << "Enter Number Of Shelfs: ";
    cin >> n;

    int *arr = new int[n];
    for(int i = 0;i<n;i++){
        cout << "Enter Book Capacity of " << i+1 << ": ";
        cin >> *(arr+i);
    } 
    Library shelf(arr,n);
    shelf.display();

    shelf.addNewShelf(70,2);
    cout << "After Adding New Shelf\n";
    shelf.display();

    shelf.insertionSort();
    cout << "After Sorting\n";
    shelf.display();

    delete[] arr;
    return 0;
}