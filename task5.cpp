#include <iostream>
#include <string>
using namespace std;

class Node{
    public:
        int product_id;
        string product_name;
        string category;
        int price;
        Node* next;
    
    Node(int id, string p_name, string cat, int p){
        product_id = id;
        product_name = p_name;
        category = cat;
        price = p;
        next = nullptr;
    }
};


class Branch{
    private:
    Node* head;

    public:
    Branch(){
        head = nullptr;
    }

    void insertSorted(int id, string p_name, string cat, int p){
        Node* newNode = new Node(id, p_name, cat, p);
        //case 1 if head is NULL or if id is less than productid of head
        if(head==NULL || id<head->product_id){    
            newNode->next = head;
            head = newNode;
            return;
        }

        //case 2 if it is not head it is between and somewhere else then we will find first pos -1 
        Node* temp = head;
        while(temp->next && temp->next->product_id<id){
            temp = temp->next;
        }
 
        newNode->next = temp->next;
        temp->next = newNode;
    }

    //display const function
    void display()const{
        Node *temp = head;
        while(temp){
            cout << "Product ID: " << temp->product_id << endl;
            cout << "Product Name: " << temp->product_name << endl;
            cout << "Category: " << temp->category << endl;
            cout << "Price: " << temp->price << endl;
            cout << "------------------------" << endl;
            temp = temp->next;
        }
    }

    //merge two linked list
    Node* mergeLL(Node* head1, Node* head2){
        //if one ll is empty 
        if(head1==NULL){
            return head2;
        }
        //if 2nd is ll is empty
        if(head2==NULL){
            return head1;
        }

        //now we will comapre and merge them in ascending order if same node appears in both ten we will take lower price one
        Node *head = NULL;
        Node *tail = NULL;

        while(head1 && head2){
            Node* selected;
            if(head1->product_id < head2->product_id){ //head1 id is less 
                selected = head1;
                head1  = head1->next;
            }else if(head1->product_id > head2->product_id){ //head2 id is less 
                selected = head2;
                head2 = head2->next;
            }else{
                Node* duplicate;
                if(head1->price <= head2->price){
                    selected = head1;
                    duplicate = head2;
                }
                else{
                    selected = head2;
                    duplicate = head1;
                }

                head1 = head1->next;
                head2 = head2->next;

                delete duplicate;
            }
            //insert
            selected->next = nullptr;
            if(head==NULL){
                head = tail = selected;
            }else{
                tail->next = selected;
                tail = selected;
            }
        }
        //if ll1 has remaining elements
        if(head1){
            tail->next = head1;
        }
        //if ll2 has remaining elements
        if(head2){
            tail->next = head2;
        }

        return head;
    }

    //total products and total inventory value calculate function
    void totalCal(){
        int count = 0;
        int total = 0;

        Node *temp = head;
        while(temp){
            count++;
            total+= temp->price;
            temp = temp->next;
        }

        cout << "Total Items: " << count << endl;
        cout << "Total Inventory Value: " << total << endl;
    }
    //helper function
    Node* getHead(){
        return head;
    }

    //helper function
    void clearHead(){
        head = nullptr;
    }


    //destructor
    ~Branch(){
        Node* temp;

        while(head){
            temp = head;
            head = head->next;
            delete temp;
        }
    }

};

int main(){
    Branch glowCare;
    Branch beautyHub;

    int n;
    cout << "Enter number of products for GlowCare: ";
    cin >> n;
    for(int i = 0; i<n; i++){
        int id, price;
        string name, category;

        cout << "\nProduct " << i + 1 << endl;
        cout << "Product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Product Name: ";
        getline(cin, name);
        cout << "Category: ";
        getline(cin, category);
        cout << "Price: ";
        cin >> price;

        glowCare.insertSorted(id, name, category, price);
    }


    cout << "\nEnter number of products for BeautyHub: ";
    cin >> n;

    for(int i = 0; i<n;i++){
        int id, price;
        string name, category;

        cout << "\nProduct " << i + 1 << endl;
        cout << "Product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Product Name: ";
        getline(cin, name);
        cout << "Category: ";
        getline(cin, category);
        cout << "Price: ";
        cin >> price;

        beautyHub.insertSorted(id, name, category, price);
    }

    cout << "\nGlowCare\n";
    glowCare.display();
    glowCare.totalCal();

    cout << "\nBeautyHub\n";
    beautyHub.display();
    beautyHub.totalCal();

    //Merge
    Node* masterLL = glowCare.mergeLL(glowCare.getHead(),beautyHub.getHead());
    glowCare.clearHead();
    beautyHub.clearHead();
    cout << "\nMaster List\n";
    Node* temp = masterLL;
    while(temp){
        cout << "Product ID: " << temp->product_id << endl;
        cout << "Product Name: " << temp->product_name << endl;
        cout << "Category: " << temp->category << endl;
        cout << "Price: " << temp->price << endl;
        cout << "------------------------" << endl;

        temp = temp->next;
    }

    //Calculate totals of a masterLL is a Node*, not a Branch object. Therefore we will not able to call calc function
    int count = 0;
    int total = 0;
    temp = masterLL;
    while(temp){
        count++;
        total += temp->price;
        temp = temp->next;
    }

    cout << "\nTotal Items: " << count << endl;
    cout << "Total Inventory Value: " << total << endl;

    temp = masterLL;

    while(temp!=nullptr){
        Node* next = temp->next;
        delete temp;
        temp = next;
    }

    return 0;
}
