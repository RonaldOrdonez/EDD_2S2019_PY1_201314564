#include <iostream>
#include <string>
#include "prueba.cpp"

using namespace std;

int main(){
    prueba p;
    string res = p.returnName();
    cout<< res <<endl;

    return 0;
}