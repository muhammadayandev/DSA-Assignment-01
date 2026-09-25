#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//Combatant Class
class Combatant{
    public:
        string name;
        int health;
        int attackPower;

    Combatant(string n = "", int h = 0, int a = 0){
        name = n;
        health = h;
        attackPower = a;
    }
};

//Node Class
class Node{
    public:
        Combatant combatant;
        Node* next;
        Node* prev;

    Node(string n, int h, int a){
        combatant.name = n;
        combatant.health = h;
        combatant.attackPower = a;

        next = nullptr;
        prev = nullptr;
    }
};


//Doubly Linked List
class Team{
    private:
        Node* head;

    public:
    Team(){
        head = nullptr;
    }

    // Insert combatant at the end
    void insert(string name, int health, int attackPower){
        Node* newNode = new Node(name, health, attackPower);
        //If list is empty
        if(head == NULL){
            head = newNode;
            return;
        }
        Node* temp = head;

        while(temp->next){
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    void displayNames(){

        Node* temp = head;
        while(temp){
            cout << temp->combatant.name << " ";
            temp = temp->next;
        }

        cout << endl;
    }

    void displayDetails(){
        Node* temp = head;
        while(temp){
            cout << "Name: " << temp->combatant.name << endl;
            cout << "Health: " << temp->combatant.health << endl;
            cout << "Attack Power: " << temp->combatant.attackPower << endl;
            cout << endl;
            temp = temp->next;
        }
    }

    Node* find(string name){
        Node* temp = head;
        while(temp){
            if(temp->combatant.name == name){
                return temp;
            }
            temp = temp->next;
        }

        return nullptr;
    }

    bool isEmpty(){
        if(head == NULL){
            return true;
        }
        return false;
    }

    void remove(Node* target){
        if(target == NULL){
            return;
        }
        //If target is head
        if(target == head){
            head = target->next;
            if(head != NULL){
                head->prev = nullptr;
            }
            delete target;
            return;
        }

        //Connect previous node with next node
        if(target->prev != NULL){
            target->prev->next = target->next;
        }

        if(target->next != NULL){
            target->next->prev = target->prev;
        }

        delete target;
    }


    //Calculate total health
    int totalHealth(){
        int total = 0;
        Node* temp = head;
        while(temp){
            total += temp->combatant.health;
            temp = temp->next;
        }
        return total;
    }

    //Destructor
    ~Team(){
        Node* temp;
        while(head){
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};


int main(){
    srand(time(0));
    Team heroes;
    Team enemies;

    // Five heroes
    heroes.insert("Arthur", 60, 5);
    heroes.insert("Merlin", 50, 4);
    heroes.insert("Lancelot", 70, 3);
    heroes.insert("Robin", 45, 5);
    heroes.insert("Gwen", 55, 2);

    // Five enemies
    enemies.insert("Orc", 60, 4);
    enemies.insert("Goblin", 40, 3);
    enemies.insert("Dragon", 70, 5);
    enemies.insert("Skeleton", 35, 2);
    enemies.insert("Demon", 65, 4);

    cout << "TURN BASED BATTLE\n";
    int round = 1;

    //Maximum 10 rounds
    while(!heroes.isEmpty() && !enemies.isEmpty() && round <= 10){

        cout << "\nROUND " << round << "\n";
        if(!heroes.isEmpty() && !enemies.isEmpty()){
            cout << "\nHeroes: ";
            heroes.displayNames();
            cout << "Enemies: ";
            enemies.displayNames();

            string attackerName;
            string targetName;
            cout << "\nChoose Hero Attacker: ";
            cin >> attackerName;
            Node* attacker = heroes.find(attackerName);

            // Check attacker
            if(attacker == NULL){
                cout << "Hero not found!\n";
                continue;
            }

            cout << "Choose Enemy Target: ";
            cin >> targetName;

            Node* target = enemies.find(targetName);
            // Check target
            if(target == NULL){
                cout << "Enemy not found!\n";
                continue;
            }

            //Random value 1 to 3
            int randomValue = rand() % 3 + 1;

            int damage = attacker->combatant.attackPower * randomValue;
            target->combatant.health -= damage;
            cout << attacker->combatant.name << " attacked " << target->combatant.name << endl;
            cout << "Damage dealt: " << damage << endl;

            //Remove if health <= 0
            if(target->combatant.health <= 0){
                cout << target->combatant.name << " has been defeated!\n";
                enemies.remove(target);
            }

            //Display remaining names
            cout << "\nRemaining Heroes: ";
            heroes.displayNames();

            cout << "Remaining Enemies: ";
            enemies.displayNames();
        }

        //Check if enemies are eliminated
        if(enemies.isEmpty()){
            cout << "\nHeroes win!\n";
            break;
        }
        //ENEMY TURN
        if(!heroes.isEmpty() && !enemies.isEmpty()){
            cout << "\nEnemy Counter Attack\n";
            cout << "Enemies: ";
            enemies.displayNames();
            cout << "Heroes: ";
            heroes.displayNames();

            string attackerName;
            string targetName;
            cout << "\nChoose Enemy Attacker: ";
            cin >> attackerName;
            Node* attacker = enemies.find(attackerName);
            if(attacker == NULL){
                cout << "Enemy not found!\n";
                continue;
            }
            cout << "Choose Hero Target: ";
            cin >> targetName;

            Node* target = heroes.find(targetName);
            if(target == NULL){
                cout << "Hero not found!\n";
                continue;
            }
            //Random value 1 to 3
            int randomValue = rand() % 3 + 1;
            int damage = attacker->combatant.attackPower * randomValue;
            target->combatant.health -= damage;
            cout << attacker->combatant.name<< " attacked " << target->combatant.name << endl;
            cout << "Damage dealt: " << damage << endl;
            //Remove defeated hero
            if(target->combatant.health <= 0){
                cout << target->combatant.name << " has been defeated!\n";
                heroes.remove(target);
            }
            //Display remaining names
            cout << "\nRemaining Heroes: ";
            heroes.displayNames();
            cout << "Remaining Enemies: ";
            enemies.displayNames();
        }

        //Check if heroes are eliminated
        if(heroes.isEmpty()){
            cout << "\nEnemies win!\n";
            break;
        }
        round++;
    }
    
    //FINAL RESULT
    if(heroes.isEmpty()){
        cout << "\nWINNER: ENEMIES\n";
        cout << "\nSurviving Enemies:\n";
        enemies.displayDetails();
    } else if(enemies.isEmpty()){
        cout << "\nWINNER: HEROEs\n";
        cout << "\nSurviving Heroes:\n";
        heroes.displayDetails();
    } else{
        cout << "\n10 ROUNDS COMPLETED\n";
        int heroHealth = heroes.totalHealth();
        int enemyHealth = enemies.totalHealth();
        cout << "\nTotal Hero Health: " << heroHealth << endl;
        cout << "Total Enemy Health: " << enemyHealth << endl;
        if(heroHealth > enemyHealth){
            cout << "\nHEROES WIN\n";
            cout << "\nSurviving Heroes:\n";
            heroes.displayDetails();
        } else if(enemyHealth > heroHealth){
            cout << "\nENEMIES WIN\n";
            cout << "\nSurviving Enemies:\n";
            enemies.displayDetails();
        } else{
            cout << "\nDRAW\n";
            cout << "\nRemaining Heroes:\n";
            heroes.displayDetails();
            cout << "\nRemaining Enemies:\n";
            enemies.displayDetails();
        }
    }


    return 0;
}