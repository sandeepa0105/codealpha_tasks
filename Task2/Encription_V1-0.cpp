#include <iostream>
#include <fstream>
#include <string>

using namespace std;

char encryptChar(char ch, int key) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return (ch - base + key) % 26 + base;
    }
    return ch;
}

char decryptChar(char ch, int key) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return (ch - base - key + 26) % 26 + base;
    }
    return ch;
}

void encryptFile(const string& inputFile, const string& outputFile, int key) {
    ifstream in(inputFile);
    ofstream out(outputFile);

    if (!in || !out) {
        cout << "File error!\n";
        return;
    }

    char ch;
    while (in.get(ch)) {
        out << encryptChar(ch, key);
    }

    cout << "File encrypted and saved as: " << outputFile << endl;
}

void decryptFile(const string& inputFile, const string& outputFile, int key) {
    ifstream in(inputFile);
    ofstream out(outputFile);

    if (!in || !out) {
        cout << "File error!\n";
        return;
    }

    char ch;
    while (in.get(ch)) {
        out << decryptChar(ch, key);
    }

    cout << "File decrypted and saved as: " << outputFile << endl;
}

int main() {
    int choice, key;
    string inputFile, outputFile;

    cout << "==== Caesar Cipher File Encryptor ====\n";
    cout << "1. Encrypt File\n";
    cout << "2. Decrypt File\n";
    cout << "Choose an option: ";
    cin >> choice;

    cout << "Enter key (1-25): ";
    cin >> key;

    cin.ignore(); // Clear newline
    cout << "Enter input file path: ";
    getline(cin, inputFile);
    cout << "Enter output file path: ";
    getline(cin, outputFile);

    if (choice == 1)
        encryptFile(inputFile, outputFile, key);
    else if (choice == 2)
        decryptFile(inputFile, outputFile, key);
    else
        cout << "Invalid choice.\n";

    return 0;
}
