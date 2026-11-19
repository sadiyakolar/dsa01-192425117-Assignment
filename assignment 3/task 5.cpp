#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
class Time {
    int seconds;
public:
    explicit Time(int s=0):seconds(s){ if(s<0) throw std::invalid_argument("negative time"); }
    Time& operator++(){ ++seconds; return *this; }
    Time operator++(int){ Time old=*this; ++seconds; return old; }
    bool operator==(const Time& o)const{return seconds==o.seconds;}
    bool operator<(const Time& o)const{return seconds<o.seconds;}
    friend std::ostream& operator<<(std::ostream& os,const Time& t){int h=t.seconds/3600,m=(t.seconds/60)%60,s=t.seconds%60; return os<<h<<':'<<(m<10?"0":"")<<m<<':'<<(s<10?"0":"")<<s;}
};
class Playlist {
    std::vector<std::string> tracks;
public:
    Playlist(std::initializer_list<std::string> t):tracks(t){}
    std::string& operator[](int i){if(i<0||i>=static_cast<int>(tracks.size()))throw std::out_of_range("playlist index");return tracks[i];}
    const std::string& operator[](int i)const{if(i<0||i>=static_cast<int>(tracks.size()))throw std::out_of_range("playlist index");return tracks[i];}
    int size()const{return static_cast<int>(tracks.size());}
};
int main(){ Time t(3599); Time a=t++; Time b=++t; std::cout<<"a="<<a<<", b="<<b<<", t="<<t<<'\n';
    Playlist p{"Track One","Track Two"}; std::cout<<p[0]<<'\n';
    try{std::cout<<p[p.size()]<<'\n';}catch(const std::out_of_range& e){std::cout<<"Range error: "<<e.what()<<'\n';}
}
