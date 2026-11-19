#include <cstring>
#include <iostream>
#include <utility>
class Text {
    char* data;
public:
    Text(const char* s="") { data=new char[std::strlen(s)+1]; std::strcpy(data,s); }
    Text(const Text& o) { data=new char[std::strlen(o.data)+1]; std::strcpy(data,o.data); }
    Text& operator=(const Text& o) { if(this!=&o){char* fresh=new char[std::strlen(o.data)+1];std::strcpy(fresh,o.data);delete[] data;data=fresh;}return *this; }
    ~Text(){delete[] data;}
    Text operator+(const Text& o)const { Text result; delete[] result.data; result.data=new char[std::strlen(data)+std::strlen(o.data)+1]; std::strcpy(result.data,data);std::strcat(result.data,o.data);return result; }
    bool operator==(const Text& o)const{return std::strcmp(data,o.data)==0;}
    bool operator!=(const Text& o)const{return !(*this==o);}
    friend std::ostream& operator<<(std::ostream& os,const Text& t){return os<<t.data;}
};
int main(){Text a("Hello "),b("C++ "),c("World");Text combined=a+b+c;Text empty;Text copy=combined;copy=copy;
    std::cout<<combined<<'\n'<<std::boolalpha<<(combined==copy)<<' '<<(empty==a)<<'\n';}
