#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

int main() {
    int maxSlots;
    cout << "Enter total number of parking slots: ";
    cin >> maxSlots;

    stack<string> parkingStack;
    queue<string> waitingQueue;

    int slotStatus[100] = {0};   // 0 = empty, 1 = filled
    string slotCars[100];

    int choice, slotChoice;
    string carNumber;

    do {
        cout << "\n====== SMART PARKING LOT SYSTEM ======\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Display Parked Vehicles\n";
        cout << "4. Display Waiting List\n";
        cout << "5. Show Parking Status\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            // --------- Park Vehicle ---------
            case 1: {
                cout << "Enter Car Number: ";
                cin >> carNumber;

                int occupied = 0;
                for (int i = 0; i < maxSlots; i++) {
                    if (slotStatus[i] == 1) {
                        occupied++;
                    }
                }

                int available = maxSlots - occupied;

                if (available == 0) {
                    cout << "Available Slots: 0\n";
                    cout << "🚫 Parking is FULL!\n";
                    waitingQueue.push(carNumber);
                    cout << "✅ Vehicle added to waiting list.\n";
                } 
                else {
                    cout << "Available Slots: ";
                    for (int i = 0; i < maxSlots; i++) {
                        if (slotStatus[i] == 0) {
                            cout << (i + 1) << " ";
                        }
                    }
                    cout << endl;

                    cout << "Choose slot number: ";
                    cin >> slotChoice;

                    if (slotChoice < 1 || slotChoice > maxSlots) {
                        cout << "❌ Invalid slot number!\n";
                    }
                    else if (slotStatus[slotChoice - 1] == 1) {
                        cout << "❌ Slot already occupied!\n";
                    }
                    else {
                        slotStatus[slotChoice - 1] = 1;
                        slotCars[slotChoice - 1] = carNumber;
                        parkingStack.push(carNumber);
                        cout << "✅ Vehicle parked in slot " << slotChoice << endl;
                    }
                }
                break;
            }

            // --------- Remove Vehicle ---------
            case 2: {
                cout << "Enter Car Number to remove: ";
                cin >> carNumber;

                int found = -1;
                for (int i = 0; i < maxSlots; i++) {
                    if (slotStatus[i] == 1 && slotCars[i] == carNumber) {
                        found = i;
                        break;
                    }
                }

                if (found != -1) {
                    slotStatus[found] = 0;
                    slotCars[found] = "";
                    cout << "🚗 Vehicle removed from slot " << (found + 1) << endl;
                } else {
                    cout << "❌ Vehicle not found!\n";
                }
                break;
            }

            // --------- Display Parked Vehicles ---------
            case 3: {
                cout << "\n🚙 Parked Vehicles:\n";
                for (int i = 0; i < maxSlots; i++) {
                    if (slotStatus[i] == 1) {
                        cout << "Slot " << (i + 1) << ": " << slotCars[i] << endl;
                    }
                }
                break;
            }

            // --------- Display Waiting List ---------
            case 4: {
                if (waitingQueue.empty()) {
                    cout << "No vehicles in waiting list.\n";
                } else {
                    queue<string> temp = waitingQueue;
                    cout << "\n🕒 Waiting Vehicles:\n";
                    while (!temp.empty()) {
                        cout << temp.front() << endl;
                        temp.pop();
                    }
                }
                break;
            }

            // --------- Show Parking Status ---------
            case 5: {
                int occupied = 0;
                for (int i = 0; i < maxSlots; i++) {
                    if (slotStatus[i] == 1) {
                        occupied++;
                    }
                }

                int available = maxSlots - occupied;

                cout << "\n📊 Parking Status\n";
                cout << "Total Slots     : " << maxSlots << endl;
                cout << "Occupied Slots  : " << occupied << endl;
                cout << "Available Slots : " << available << endl;

                if (available == 0) {
                    cout << "🚫 Parking is FULL!\n";
                }
                break;
            }

            // --------- Exit ---------
            case 6:
                cout << "👋 Exiting program...\n";
                break;

            default:
                cout << "❌ Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}