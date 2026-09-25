
#include <iostream>
using namespace std;

//Player Class
class Player{
    public:
        int id;
        int energy;
        char history[100];
        int top;

    Player(){
        id = 0;
        energy = 100;
        top = -1;
    }

    //Check if history is empty
    bool isEmpty(){
        return top == -1;
    }

    //Push action into history
    void push(char action){
        top++;
        history[top] = action;
    }

    //Pop last action
    char pop(){
        if(isEmpty()){
            return 'X';
        }

        char action = history[top];
        top--;

        return action;
    }

    //Number of actions remaining
    int count(){
        return top + 1;
    }
};


//Main Function
int main(){

    Player p[100];

    int q[1000];
    int front = 0;
    int rear = -1;

    int n;
    cout << "Enter number of players: ";
    cin >> n;

    //Input players
    for(int i = 0; i < n; i++){
        cout << "Enter Player ID: ";
        cin >> p[i].id;

        p[i].energy = 100;
        //Add player to queue
        rear++;
        q[rear] = i;
    }

    int commands;
    cout << "Enter number of commands: ";
    cin >> commands;

    int eliminated[100];
    int eCount = 0;

    //Process all commands
    for(int i = 0; i < commands; i++){

        if(front > rear){
            break;
        }

        char cmd;
        cin >> cmd;

        //Get player from front
        int index = q[front];
        front++;

        //F: Move Forward
        if(cmd == 'F'){
            p[index].energy -= 10;
            p[index].push('F');
        } else if(cmd == 'B'){  //B: Move Backward
            p[index].push('B');
        } else if(cmd == 'T'){ //T: Collect Treasure
            p[index].energy += 20;
            p[index].push('T');
        } else if(cmd == 'U'){    //U: Undo

            if(!p[index].isEmpty()){
                char action = p[index].pop();
                if(action == 'F'){
                    p[index].energy += 10;
                } else if(action == 'B'){
                    //No energy change
                } else if(action == 'T'){
                    p[index].energy -= 20;
                }
            }
        }

        //Check if player is eliminated
        if(p[index].energy <= 0){
            eliminated[eCount] = p[index].id;
            eCount++;
        } else{
            //Active player goes to end of queue
            rear++;
            q[rear] = index;
        }
    }

    //Final Output
    cout << "\nFINAL RESULTS" << endl;
    cout << "\nElimination Order: ";
    if(eCount == 0){
        cout << "No players eliminated";
    } else{
        for(int i = 0; i < eCount; i++){
            cout << eliminated[i] << " ";
        }
    }

    cout << "\n\nActive Players:" << endl;
    //Display players still in queue
    for(int i = front; i <= rear; i++){
        int index = q[i];
        cout << "Player ID: " << p[index].id << endl;
        cout << "Energy: " << p[index].energy << endl;
        cout << "Actions Available to Undo: " << p[index].count() << endl;
    }

    return 0;
}