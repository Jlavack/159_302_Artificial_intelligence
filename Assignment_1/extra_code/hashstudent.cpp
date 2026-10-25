#include <iostream>
#include <unordered_map>
#include <string>

class Student
{
    std::string name;
    
    public:
        Student(std::string n):name(n){ }
        std::string get_name() const { return name; }
        
        bool operator==(const Student& s) const
        {   return s.name == name; }
        
};

namespace std
{
    template<>
    struct hash<Student>
    {
        std::size_t operator()(const Student& s) const
        { return hash<string>()(s.get_name()); }
    };
    
}

int main()
{
    Student s1("Mahesh"), s2("Priyanka");
    
    std::unordered_map<Student, int> marks;
    marks.insert(std::make_pair(s1,20));
    marks.insert(std::make_pair(s2,40));
    marks.insert(std::make_pair(s2,40));
    
    for(auto i : marks)
        std::cout << i.first.get_name() << " " << i.second << std::endl;
    
}