#include "list.hpp"

int main(){
    List <int>ints;
    ints.insert(0,3);
    std::cout<<"size : "<<ints.size()<<std::endl;
    ints.insert(1,5);
    std::cout<<"size : "<<ints.size()<<std::endl;
    ints.insert(1,4);
    std::cout<<"size : "<<ints.size()<<std::endl;
    ints.insert(1,1000);
    std::cout<<"size : "<<ints.size()<<std::endl;
    ints.Delete(3);
    std::cout<<"size : "<<ints.size()<<std::endl;
    ints.push_back(123456);
    std::cout<<"size : "<<ints.size()<<std::endl;
    ints.pop_back();
    std::cout<<"size : "<<ints.size()<<std::endl;
    return 0;
}
