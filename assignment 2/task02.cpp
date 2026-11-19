#include <iostream>
using namespace std;

int& highestMark(int marks[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i)
        if (marks[i] > marks[index]) index = i;
    return marks[index];
}

const int& highestMarkConst(const int marks[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i)
        if (marks[i] > marks[index]) index = i;
    return marks[index];
}

int highestMarkCopy(const int marks[], int size) {
    int highest = marks[0];
    for (int i = 1; i < size; ++i)
        if (marks[i] > highest) highest = marks[i];
    return highest;
}

int highestIndex(const int marks[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i)
        if (marks[i] > marks[index]) index = i;
    return index;
}

int* highestPointer(int marks[], int size) {
    int index = highestIndex(marks, size);
    return &marks[index];
}

// Intentionally unsafe example for compiler-warning demonstration only.
// Do NOT call this function or use its returned reference.
#if defined(SHOW_DANGLING_WARNING)
int& danglingReference() {
    int local = 50;
    return local; // returning a reference to a destroyed local variable is undefined behaviour
}
#endif

int main() {
    int marks[5] = {75, 88, 92, 67, 85};
    cout << "Original marks: ";
    for (int mark : marks) cout << mark << ' ';
    cout << "\nHighest mark: " << highestMark(marks, 5) << '\n';

    highestMark(marks, 5) += 2;
    cout << "After moderation: ";
    for (int mark : marks) cout << mark << ' ';
    cout << "\nConst reference: " << highestMarkConst(marks, 5);
    cout << "\nReturned copy: " << highestMarkCopy(marks, 5);
    int index = highestIndex(marks, 5);
    cout << "\nIndex result: " << index << ", value: " << marks[index];
    int* ptr = highestPointer(marks, 5);
    cout << "\nPointer result: " << *ptr << '\n';
}
