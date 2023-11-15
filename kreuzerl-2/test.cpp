#include <iostream>

auto addThree = [] (int a){
    return [a] (int b){
        return [a, b] (int c){
            return a+b+c;
        };
    };
};

int main(){
    std::cout << addThree(1)(2)(3) << std::endl;
}