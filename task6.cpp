#include <iostream>
#include <string>
using namespace std;

//Song Obj Class
class Song{
    public:
    string title;
    string genre;
    int duration;
    bool explicitContent;

    Song(){
        title = "";
        genre = "";
        duration = 0;
        explicitContent = false;
    }

    Song(string t, string g, int d, bool exp){
        title = t;
        genre = g;
        duration = d;
        explicitContent = exp;
    }
};

//Node Contain Song Obj
class Node{
    public:
    Song song;
    Node* next;

    Node(Song s){
        song = s;
        next = nullptr;
    }
};

//Playlist will manage linked list
class PlayList{
    private:
    Node* head;

    //check if song can be inserted at this position
    bool validPosition(Song s, int pos) const{

        Node* previous = nullptr;
        Node* nextNode = head;

        //find previous and next node
        if(pos>1){
            previous = head;
            for(int i = 1; i<pos-1; i++){
                if(previous == nullptr)
                    return false;

                previous = previous->next;
            }

            if(previous != nullptr)
                nextNode = previous->next;
        }

        //same genre with previous song
        if(previous != nullptr){
            if(previous->song.genre == s.genre)
                return false;
        }

        //same genre with next song
        if(nextNode != nullptr){
            if(nextNode->song.genre == s.genre)
                return false;
        }

        //check three songs around insertion point
        if(previous != nullptr && nextNode != nullptr){

            if(previous->song.duration + s.duration + nextNode->song.duration > 600)
                return false;
        }

        //check previous two + new song
        if(previous != nullptr){
            Node* prev2 = head;

            while(prev2 != nullptr && prev2->next != previous)
                prev2 = prev2->next;

            if(prev2 != nullptr){
                if(prev2->song.duration + previous->song.duration + s.duration > 600)
                    return false;
            }
        }

        //check new song + next two
        if(nextNode != nullptr && nextNode->next != nullptr){

            if(s.duration + nextNode->song.duration + nextNode->next->song.duration > 600)
                return false;
        }

        return true;
    }

    //check complete playlist constraints
    bool checkConstraints() const{
        Node* current = head;

        while(current != nullptr){
            //two adjacent songs cannot have same genre
            if(current->next != nullptr){
                if(current->song.genre == current->next->song.genre)
                    return false;
            }

            //three consecutive songs cannot exceed 600 seconds
            if(current->next != nullptr && current->next->next != nullptr){

                int total = current->song.duration + current->next->song.duration + current->next->next->song.duration;

                if(total>600)
                    return false;
            }

            current = current->next;
        }

        return true;
    }

    public:
    PlayList(){
        head = nullptr;
    }

    //destructor
    ~PlayList(){
        Node* current = head;

        while(current != nullptr){
            Node* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
    }

    //display function
    void display() const{
        if(head == NULL){
            cout << "NULL" << endl;
            return;
        }

        Node* current = head;
        int pos = 1;

        while(current){
            cout << "Song: " << pos << endl;
            cout << "Title: " << current->song.title << endl;
            cout << "Genre: " << current->song.genre << endl;
            cout << "Duration: " << current->song.duration << " Seconds" << endl;
            cout << "Explicit: " << (current->song.explicitContent ? "YES" : "NO") << endl;
            cout << endl;
            current = current->next;
            pos++;
        }
    }

    //search function by title
    void search(string title){
        if(head == NULL){
            cout << "No Songs Added\n";
            return;
        }

        Node* current = head;
        int pos = 1;

        while(current){
            if(current->song.title == title){
                cout << "Found" << endl;
                cout << "Position: " << pos << endl;
                cout << "Title: " << current->song.title << endl;
                cout << "Genre: " << current->song.genre << endl;
                cout << "Duration: " << current->song.duration << " seconds\n";
                cout << "Explicit: " << (current->song.explicitContent ? "Yes" : "No") << endl;
                return;
            }

            current = current->next;
            pos++;
        }

        cout << "SONG NOT FOUND" << endl;
    }

    //make explicit song non-explicit
    void makeNonExplicit(int pos){
        if(head == NULL){
            cout << "No Songs\n";
            return;
        }

        Node* current = head;

        for(int i = 1; i < pos; i++){
            if(current == nullptr){
                cout << "Invalid Position." << endl;
                return;
            }

            current = current->next;
        }

        if(current == nullptr){
            cout << "Invalid Position." << endl;
            return;
        }

        if(current->song.explicitContent == false){
            cout << "Song is already NON-Explicit\n";
            return;
        }

        current->song.explicitContent = false;

        cout << "Song is now NON-Explicit\n";
    }

    //delete at position
    void deleteAtPos(int pos){
        if(head == NULL){
            cout << "No Songs\n";
            return;
        }

        if(pos < 1){
            cout << "Invalid Position." << endl;
            return;
        }

        Node* target;

        if(pos == 1){
            target = head;
        }
        else{
            Node* current = head;

            for(int i = 1; i < pos-1; i++){
                if(current == nullptr){
                    cout << "Invalid Position." << endl;
                    return;
                }

                current = current->next;
            }

            if(current == NULL || current->next == NULL){
                cout << "Invalid Position." << endl;
                return;
            }

            target = current->next;
        }

        //explicit songs cannot be deleted directly
        if(target->song.explicitContent == true){
            cout << "Can Not Delete Explicit Song\n";
            cout << "Make Song NON-Explicit First\n";
            return;
        }

        //check if deletion creates genre conflict
        if(pos == 1){
            if(head->next != nullptr && head->next->next != nullptr){

                if(head->next->song.genre == head->next->next->song.genre){

                    cout << "Deletion creates same genre adjacency.\n";
                    cout << "Song can not be deleted at this position.\n";
                    return;
                }
            }
        }
        else{
            Node* current = head;

            for(int i = 1; i < pos-1; i++)
                current = current->next;

            Node* before = current;
            Node* after = target->next;

            if(before != nullptr && after != nullptr){
                if(before->song.genre == after->song.genre){
                    cout << "Deletion creates same genre adjacency.\n";
                    cout << "Song can not be deleted at this position.\n";
                    return;
                }
            }
        }

        //now delete
        if(pos == 1){
            head = head->next;
            delete target;
        }
        else{
            Node* current = head;

            for(int i = 1; i < pos-1; i++)
                current = current->next;

            Node* delNode = current->next;
            current->next = delNode->next;
            delete delNode;
        }

        cout << "Song Is Deleted\n";
    }

    //insert song at position
    void insertAtPos(Song s, int pos){
        if(pos < 1)
            pos = 1;

        //find next valid position
        int total = 0;
        Node* current = head;

        while(current != nullptr){
            total++;
            current = current->next;
        }

        if(pos > total + 1)
            pos = total + 1;

        int validPos = -1;

        //try desired position and then next positions
        for(int i = pos; i <= total + 1; i++){
            if(validPosition(s, i)){
                validPos = i;
                break;
            }
        }

        if(validPos == -1){
            cout << "No valid position found for this song.\n";
            return;
        }

        Node* newNode = new Node(s);

        //insert at beginning
        if(validPos == 1){
            newNode->next = head;
            head = newNode;
        }
        else{
            current = head;

            for(int i = 1; i < validPos-1; i++)
                current = current->next;

            newNode->next = current->next;
            current->next = newNode;
        }

        cout << "Song Inserted At Position: " << validPos << endl;

        if(validPos != pos)
            cout << "Desired position was invalid, so next valid position was used.\n";
    }

    //check playlist constraints
    void checkPlaylist(){
        if(checkConstraints())
            cout << "All Playlist Constraints Satisfied.\n";
        else
            cout << "Playlist Constraints Violated.\n";
    }
};

int main(){

    PlayList playlist;

    Song s1("Believer", "rock", 180, false);
    Song s2("Shape Of You", "pop", 200, false);
    Song s3("Faded", "electronic", 190, true);
    Song s4("Perfect", "classical", 150, false);
    Song s5("Jazz Song", "jazz", 160, false);

    playlist.insertAtPos(s1, 1);
    playlist.insertAtPos(s2, 2);
    playlist.insertAtPos(s3, 3);
    playlist.insertAtPos(s4, 4);

    cout << "\nPLAYLIST\n";
    playlist.display();

    cout << "\nSEARCH\n";
    playlist.search("Faded");

    cout << "\nTRY DELETE EXPLICIT SONG\n";
    playlist.deleteAtPos(3);

    cout << "\n MAKE NON-EXPLICIT\n";
    playlist.makeNonExplicit(3);

    cout << "\nDELETE SONG\n";
    playlist.deleteAtPos(3);

    cout << "\nINSERT JAZZ\n";
    playlist.insertAtPos(s5, 2);

    cout << "\nFINAL PLAYLIST\n";
    playlist.display();

    cout << "\nCHECK CONSTRAINTS\n";
    playlist.checkPlaylist();

    return 0;
}
