#include "LR_Classifier.h"
#include <iostream>



int main(){
    //处理数据
    std::string data_file = "Iris.txt";
    std::vector<IrisData> all_data= read_iris_data(data_file);
    auto data = split_data(all_data);
    std::vector<IrisData> train_data = data.first;
    std::vector<IrisData> test_data = data.second;

    //训练logistic回归模型
    LogisticRegression lr(4, 0.3);
    lr.print_weights();
    lr.train(train_data, 100);
    lr.predict(test_data);
    return 0;
}
