#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Elem {
    Elem* link;
    string info;
};

struct WordCount {
    WordCount* next;
    string word;
    int count;
};

void push(Elem*& top, const string& value) {
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->link = top;
    top = tmp;
}

string pop(Elem*& top) {
    if (top == nullptr) return "";
    Elem* tmp = top->link;
    string value = top->info;
    delete top;
    top = tmp;
    return value;
}

void readWordsFromFile(const string& filename, Elem*& top) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        return;
    }
    string word;
    while (file >> word) {
        push(top, word);
    }
    file.close();
}

void incrementWordCount(WordCount*& head, const string& word) {
    WordCount* current = head, * last = nullptr;
    while (current != nullptr) {
        if (current->word == word) {
            current->count++;
            return;
        }
        last = current;
        current = current->next;
    }
    WordCount* newNode = new WordCount{ nullptr, word, 1 };
    if (last) {
        last->next = newNode;
    }
    else {
        head = newNode;
    }
}

void printWordCount(WordCount* head) {
    cout << "Frequency of words:" << endl;
    while (head != nullptr) {
        cout << head->word << ": " << head->count << " times" << endl;
        head = head->next;
    }
}

void cleanUpWordCount(WordCount*& head) {
    while (head != nullptr) {
        WordCount* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void processWords(Elem* top) {
    WordCount* wordCountList = nullptr;
    while (top != nullptr) {
        string word = pop(top);
        cout << word << " ";
        incrementWordCount(wordCountList, word);
    }
    cout << endl;

    printWordCount(wordCountList);
    cleanUpWordCount(wordCountList);
}

void openInNotepad(const string& filename) {
    string command = "notepad.exe " + filename;
    system(command.c_str());
}

int main() {
    Elem* top = nullptr;

    string filename = "text.txt";
    readWordsFromFile(filename, top);
    processWords(top);
    openInNotepad(filename);

    return 0;
}