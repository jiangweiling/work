#include <iostream>
#include <string>
#include <tuple>
using namespace std;


int main() {
    typedef tuple<string,int> Person;
    Person p1("zheng",25);
    string name;
    int age;
    std::tie(name,age) = p1;
    cout<<name<<" "<<age<<endl;
    name=string("aaa");
    cout<<name<<" "<<age<<endl;
    return 0;    
}
