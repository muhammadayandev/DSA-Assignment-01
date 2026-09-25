
#include <iostream>
using namespace std;

class Node{
    public:
        char cmd;
        int move;
        Node* next;

    Node(char c, int m){
        cmd = c;
        move = m;
        next = nullptr;
    }
};


//Stack Class
class Stack{
    private:
        Node* top;

    public:
    Stack(){
        top = nullptr;
    }

    //Check if stack is empty
    bool isEmpty(){
        return top == nullptr;
    }

    //Push function
    void push(char c, int m){
        Node* newNode = new Node(c, m);

        newNode->next = top;
        top = newNode;
    }

    //Pop function
    int pop(){
        if(isEmpty()){
            return 0;
        }

        Node* temp = top;
        int m = temp->move;

        top = top->next;
        delete temp;

        return m;
    }

    //Display remaining stack
    void display(){
        Node* temp = top;

        if(temp == nullptr){
            cout << "Stack is empty" << endl;
            return;
        }

        cout << "Remaining Stack (Top to Bottom): ";

        while(temp){
            cout << temp->cmd << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    //Destructor
    ~Stack(){
        Node* temp;

        while(top){
            temp = top;
            top = top->next;
            delete temp;
        }
    }
};

int main(){

    Stack s;

    int n;
    cout << "Enter number of commands: ";
    cin >> n;

    int pos = 0;
    int moves = 0;
    int undo = 0;

    cout << "Enter commands: " << endl;

    for(int i = 0; i < n; i++){

        char cmd;
        cin >> cmd;

        //Case 1: Move Right
        if(cmd == 'R'){
            int newPos = pos + 1;
            if(newPos >= 0){
                pos = newPos;
                s.push('R', 1);
                moves++;
            }
        } else if(cmd == 'L'){ //Case 2: Move Left
            int newPos = pos - 1;
            if(newPos >= 0){
                pos = newPos;
                s.push('L', -1);
                moves++;
            }
        } else if(cmd == 'J'){ //Case 3: Jump Right by 2
            int newPos = pos + 2;
            if(newPos >= 0){
                pos = newPos;
                s.push('J', 2);
                moves++;
            }
        } else if(cmd == 'B'){  //Case 4: Undo
            if(!s.isEmpty()){
                int m = s.pop();
                pos = pos - m;
                undo++;
            }
        }
    }

    cout << "\nFINAL RESULTS" << endl;

    cout << "Final Position: " << pos << endl;
    cout << "Total Successful Movements: " << moves << endl;
    cout << "Total Successful Undo Operations: " << undo << endl;
    s.display();

    return 0;
}