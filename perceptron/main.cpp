#include "perceptron.h"
#include <vector>
#include <iostream>


int main(){
    Perceptron per(2);
    per.print_weights();    //打印输出初始化权重

    /*
        param1:height;
        param2:weight;
        label:bad(0),good(1);
    */

    std::vector<std::pair<std::vector<double>, bool>> train_dataset{
        make_pair(std::vector<double> {6.3, 80}, true),
        make_pair(std::vector<double> {5.4, 60}, true),
        make_pair(std::vector<double> {4.1, 60}, false),
        make_pair(std::vector<double> {6, 120}, false),
        make_pair(std::vector<double> {6, 70}, true),
        make_pair(std::vector<double> {5, 70}, true),
        make_pair(std::vector<double> {3, 120}, false)
    };

    per.train(train_dataset);    //训练
    per.print_weights();
    std::cout << "height:5.5, weight:65, true_label:good(1), predict_label:" <<per.predict(std::vector<double> {5.5,65}) <<std::endl;
    std::cout<< "height:3.4, weight:90, true_label:bad(0), predict_label:" <<per.predict(std::vector<double> {3.4, 90}) <<std::endl;

    return 0;

}


