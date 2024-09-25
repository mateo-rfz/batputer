#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string returnCharge() {
    ifstream charge("/sys/class/power_supply/BAT0/capacity");
    string capacity;

    if (charge.is_open()) {
        getline(charge, capacity);
        charge.close();
    } else {
        capacity = "Error: Unable to open file";
    }

    return capacity;
}

int main() {
    cout << returnCharge() << endl;
    return 0;
}
