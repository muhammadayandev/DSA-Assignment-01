#include <iostream>
using namespace std;

class Rider{
public:
    string r_name;
    int id;
    int ass_orders;
    Rider* next;

    Rider(string n = "", int i = 0, int o =0 ){
        r_name = n;
        id = i;
        ass_orders = o;
        next = nullptr;
    }
};

class CircularLL{
    private:
    Rider* head;

    public:
    CircularLL(){
        head = NULL;
    }

    void insertAtFront(string name, int id, int order){
        Rider* newRider = new Rider(name,id,order);
        if(head==NULL){
            head = newRider;
            head->next = head;
            return;
        }

        Rider* temp = head;
        while(temp->next!=head){
            temp = temp->next;
        }
        newRider->next = head;;
        head = newRider;
        temp->next = head;
    }

    void insertAtEnd(string name, int id, int order){
        Rider* newRider = new Rider(name,id,order);
        if(head==NULL){
            head = newRider;
            head->next = head;
            return;
        }

        Rider* temp = head;
        while(temp->next!=head){
            temp = temp->next;
        }

        temp->next = newRider;
        newRider->next = head;
    }

    void insertAtPos(int pos,string name, int id, int order ){
        //if pos = 1 then 
        if(pos==1){
            insertAtFront(name,id,order);
            return;
        }

        if(pos<1){
            cout << "Invalid Position\n";
            return;
        }

        if(head==NULL){
            cout << "Invalid Position\n";
            return;
        }

        Rider* temp = head;
        for(int i = 1;i<pos-1;i++){
            temp = temp->next;
            if(temp==head){
                cout << "Invalid Position\n";
                return;
            }
        }

        Rider *newRider = new Rider(name,id,order);

        newRider->next = temp->next;
        temp->next = newRider;
        
    }

    void deleteAtFront(){
        if(head==NULL){
            cout << "List Is Empty\n";
            return;
        }
        //IF only one rider exist
        Rider* delNode= head;
        if(head->next == head){
            head= NULL;
            delete delNode;
            return;
        }


        Rider* temp = head;
        while(temp->next!=head){
            temp = temp->next;
        }

        head = head->next;
        temp->next = head;
        delete delNode;
    }

    void deleteAtEnd(){
        if(head==NULL){
            cout << "LIst Is Empty\n";
            return;
        }
        Rider* delNode = head;
        if(head->next== head){
            head = NULL;
            delete delNode;
            return;
        }

        Rider* temp = head;
        while(temp->next->next!=head){
            temp = temp->next;
        }

        delNode = temp->next;
        temp->next = head;
        delete delNode;
    }

    void deleteAtPos(int pos){
        if(head==NULL){
            cout << "Invalid Position\n";
            return;
        }
        //if pos = 1 then 
        if(pos==1){
            deleteAtFront();
            return;
        }

        if(pos<1){
            cout << "Invalid Position\n";
            return;
        }

        Rider* temp = head;
        for(int i =1 ;i<pos-1;i++){
            temp = temp->next;
            if(temp==head){
                cout << "Invalid Position\n";
                return;
            }
        }

        Rider* delNode = temp->next;
        if(delNode == head){
            cout << "Invalid Position!" << endl;
            return;
        }
        temp->next = temp->next->next;
        delete delNode;
    }

    void searchRider(int id){
        if(head == NULL){
            cout << "List is Empty!" << endl;
            return;
        }

        Rider* temp = head;
        while(true){
            if(temp->id == id){
                cout << "Rider Found!" << endl;
                cout << "Name: " << temp->r_name << endl;
                cout << "ID: " << temp->id << endl;
                cout << "Orders: " << temp->ass_orders << endl;
                return;
            }
            temp = temp->next;
            if(temp == head){
                break;
            }
        }

        cout << "Rider Not Found\n";
    }

      void updateRider(string name, int id, int order){
        if(head == NULL){
            cout << "List is Empty!\n";
            return;
        }

        Rider* temp = head;
        while(true){

            if(temp->id == id){
                temp->r_name = name;
                temp->ass_orders = order;
                cout << "Rider Updated!" << endl;
                return;
            }

            temp = temp->next;
            if(temp==head){
                break;
            }
        }

        cout << "Rider Not Found!" << endl;
    }

    void display(){
        if (head==NULL){
            cout << "List is Empty!\n";
            return;
        }

        Rider* temp = head;

        while(true){
            cout << "Name: " << temp->r_name << " | ID: " << temp->id << " | Orders: " << temp->ass_orders << endl;
            temp = temp->next;
            if(temp==head){
                break;
            }
        }
    }

    int countRiders(){
        if(head==NULL){
            return 0;
        }

        int count = 0;
        Rider* temp = head;
        while(true){
            count++;
            temp = temp->next;
            if(temp==head){
                break;
            }
        }
        return count;
    }

    void traverseFrom(int id){
        if(head==NULL){
            cout << "List is Empty!\n";
            return;
        }

        Rider* start = head;
        bool found = false;

        while(true){
            if(start->id == id){
                found = true;
                break;
            }
            start = start->next;
            if(start==head){
                break;
            }
        }

        if(!found){
            cout << "Rider Not Found!" << endl;
            return;
        }

        Rider* temp = start;
        while(true){
            cout << temp->id << " -> ";
            temp = temp->next;
            if(temp==start){
                break;
            }
        }
        cout << "(Back to " << start->id << ")" << endl;
    }

    ~CircularLL(){
        if(head==NULL){
            return;
        }
        Rider* temp = head->next;
        while(temp!=head){
            Rider* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }

        delete head;
        head = NULL;
    }
};

int main(){

    CircularLL riders;

    //INSERT AT END
    cout << "After Insert At End\n";
    riders.insertAtEnd("Ali", 101, 5);
    riders.insertAtEnd("Ahmed", 102, 3);
    riders.insertAtEnd("Sara", 103, 7);
    riders.display();

    //INSERT AT FRONT
    cout << "After Insert At Front\n";
    riders.insertAtFront("Hamza", 100, 2);
    riders.display();

    //INSERT AT POS
    cout << "After Insert At Pos\n";
    riders.insertAtPos(4,"Usman", 104, 4);
    riders.display();

    //DELETE FROM FRONT
    cout << "After Delete From Front\n";
    riders.deleteAtFront();
    riders.display();


    //DELETE FROM END
    cout << "After Delete From End\n";
    riders.deleteAtEnd();
    riders.display();

    //DELETE AT POS
    cout << "After Delete At Pos\n";
    riders.deleteAtPos(2);
    riders.display();

    //SEARCH
    cout << "Search Rider\n";
    riders.searchRider(102);

    //UPDATE
    cout << "Update Rider\n";
    riders.updateRider("Ahmed Khan", 102, 10);
    riders.display();

    cout << "Total Riders: " << riders.countRiders() << endl;
    riders.traverseFrom(102);
    return 0;
}