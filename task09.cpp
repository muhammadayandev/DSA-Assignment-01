#include <iostream>
#include <string>
using namespace std;

class Queue{
    private:
        int arr[100];
        int front;
        int rear;

    public:
    Queue(){
        front = 0;
        rear = -1;
    }

    //Check if queue is empty
    bool isEmpty(){
        return front > rear;
    }

    //Add patient
    void enqueue(int id){
        rear++;
        arr[rear] = id;
    }

    //Remove patient
    int dequeue(){
        if(isEmpty()){
            return -1;
        }

        int id = arr[front];
        front++;

        return id;
    }

    //Count patients
    int count(){
        if(isEmpty()){
            return 0;
        }

        return rear - front + 1;
    }
};


int main(){

    Queue critical;
    Queue serious;
    Queue normal;

    int n;
    cout << "Enter number of operations: ";
    cin >> n;

    int treated = 0;
    cout << "\nTreatment Order: ";

    for(int i = 0; i < n; i++){
        string op;
        cin >> op;
        //ARRIVE operation
        if(op == "ARRIVE"){
            int id;
            int sev;
            cin >> id >> sev;
            if(sev == 1){
                critical.enqueue(id);
            } else if(sev == 2){
                serious.enqueue(id);
            } else if(sev == 3){
                normal.enqueue(id);
            }
        } else if(op == "TREAT"){         //TREAT operation
            
            int id = -1;
            //Critical has highest priority
            if(!critical.isEmpty()){
                id = critical.dequeue();
            } else if(!serious.isEmpty()){ //Serious has second priority
                id = serious.dequeue();
            } else if(!normal.isEmpty()){    //Normal has lowest priority
                id = normal.dequeue();
            }

            //If patient was found
            if(id != -1){
                cout << id << " ";
                treated++;
            }
        }
    }

    int remaining = critical.count() + serious.count() + normal.count();

    cout << "\n\nFINAL RESULTS" << endl;
    cout << "Total Patients Treated: " << treated << endl;
    cout << "Total Patients Remaining: " << remaining << endl;
    cout << "Critical Patients Remaining: " << critical.count() << endl;
    cout << "Serious Patients Remaining: " << serious.count() << endl;
    cout << "Normal Patients Remaining: " << normal.count() << endl;

    return 0;
}