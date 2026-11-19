#include <iostream>
#include <string>
#include <stdexcept>

class Event {
    int rows, seats, booked;
    char** map;
public:
    Event(int r, int s) : rows(r), seats(s), booked(0), map(nullptr) {
        if (r < 0 || s < 0) throw std::invalid_argument("negative dimensions");
        if (rows == 0 || seats == 0) return;
        map = new char*[rows];
        int made=0;
        try { for (; made<rows; ++made) { map[made]=new char[seats];
            for(int j=0;j<seats;++j) map[made][j]='O'; } }
        catch (...) { while(made>0) delete[] map[--made]; delete[] map; throw; }
        std::cout << "Created " << rows << "x" << seats << " event\n";
    }
    bool book(int r,int s) { if(r<0||r>=rows||s<0||s>=seats||map[r][s]=='X') return false; map[r][s]='X'; ++booked; return true; }
    bool cancel(int r,int s) { if(r<0||r>=rows||s<0||s>=seats||map[r][s]=='O') return false; map[r][s]='O'; --booked; return true; }
    ~Event() { if(map){ for(int i=0;i<rows;++i) delete[] map[i]; delete[] map; }
        std::cout << "Event closed; booked seats: " << booked << '\n'; }
};
int main() {
    Event local(2,3); local.book(0,1); local.book(1,2); local.cancel(0,1);
    { Event block(1,2); block.book(0,0); }
    Event* heap = new Event(1,1); heap->book(0,0); delete heap;
    Event zero(0,5);
}
