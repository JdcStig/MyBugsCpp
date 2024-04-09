#include <iostream>
#include <vector>
#include "Bug.h"

using namespace std;


//Basic Menu
void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Initialize Bug Board\n";
    cout << "2. Display Bugs Coordinates\n";
    cout << "3. Find Bug by ID\n";
    cout << "4. Tap the Bug Board\n";
    cout << "5. Display Life History of all Bugs\n";
    cout << "6. Display all Cells listing their Bugs\n";
    cout << "7. Run simulation\n";
    cout << "8. Exit\n";
    cout << "Enter your choice: ";
}


int main() {
    std::vector<Bug*> bugs; // Vector to store Bug
//depending on choice relevant function is called

    int choice;
    //do while loop will continue displaying the menu until the user inputs 8 for exit
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                createBugs(bugs);
                cout<<"\n Bugs have been Created \n"<<endl;
                break;


            case 2: {
                displayAllBugs(bugs);
                break;
            }

            case 3:
               cout<<"not done"<<endl;
                break;

            case 4:
                cout<<"not done"<<endl;
                break;

            case 5:
                cout<<"not done"<<endl;
                break;

            case 6:
                cout<<"not done"<<endl;
                break;

            case 7:
                cout<<"not done"<<endl;
                break;

            case 8:
                cout<<"not done"<<endl;
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 8);

    // Deletes all bugs when done so i have more memory and less memory being wasted
    for (Bug* bug : bugs) {
        delete bug;
    }

    return 0;
}