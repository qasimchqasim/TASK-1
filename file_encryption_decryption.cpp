#include <iostream>
#include <fstream>
using namespace std;

string encrypt(string text, int shift) {
    string result = "";

    for (char c : text) {
        if (isupper(c))
            result += char((c - 'A' + shift) % 26 + 'A');
        else if (islower(c))
            result += char((c - 'a' + shift) % 26 + 'a');
        else
            result += c; 
    }

    return result;
}

string decrypt(string text, int shift) {
    return encrypt(text, 26 - shift); 
}

int main() {
    int choice, shift;
    string inputFile, outputFile, line;

    cout << "1. Encrypt File\n2. Decrypt File\nEnter choice: ";
    cin >> choice;

    cout << "Enter shift value (key): ";
    cin >> shift;

    cout << "Enter input file name: ";
    cin >> inputFile;

    cout << "Enter output file name: ";
    cin >> outputFile;

    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    while (getline(inFile, line)) {
        if (choice == 1)
            outFile << encrypt(line, shift) << endl;
        else if (choice == 2)
            outFile << decrypt(line, shift) << endl;
        else {
            cout << "Invalid choice!" << endl;
            return 1;
        }
    }

    inFile.close();
    outFile.close();

    cout << "Operation completed successfully!" << endl;

    return 0;
}
