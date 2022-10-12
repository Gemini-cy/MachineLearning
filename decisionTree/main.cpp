#include<iostream>
#include"DecisionTree.h"
using namespace std;

int main(){
    Tree* tree = new Tree;
    cout<< "Trained........."<<endl;
    while(true){
        tree->GetOutput();
    }
    return 0;
}


