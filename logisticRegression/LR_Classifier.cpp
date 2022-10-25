#include "LR_Classifier.h"
#include <ctime>

//读取iris数据
std::vector<IrisData> read_iris_data(const std::string &path){
    std::vector<IrisData> data;
    std::ifstream ifs(path);
    std::string line;
    //开始读取数据
    while(std::getline(ifs, line)){
        //逐行读取数据
        std::stringstream ss(line);
        std::string token;
        double *fields = new double[10];    //储存特征
        IrisData iris_data;
        iris_data.fields = fields;
        iris_data.feature_num = 4;
        int index = 0;
        while(std::getline(ss, token, ',')){
            //以‘,’为分割符读取每个数字
            if(index==0) {
                iris_data.data_num = std::stoi(token);
                index++;
                continue;
            }
            if(index==(iris_data.feature_num+1)){
                fields[index-1] = 1;
                iris_data.label = std::stoi(token);
                break;
            }
            fields[index-1] = std::stod(token);
            index++;
        }
        data.push_back(iris_data);
    }
    return data;
}


//划分训练集和测试集
std::pair<std::vector<IrisData>,std::vector<IrisData>> split_data(std::vector<IrisData> data){
    std::vector<IrisData> train_data;
    std::vector<IrisData> test_data;
    std::srand(time(nullptr));
    std::random_shuffle(data.begin(),data.end());
    int percentage70 = data.size()*0.7;
    int index = 0;
    while(index<percentage70){
        train_data.push_back(data[index]);
        index++;
    }
    while(index<data.size()){
        test_data.push_back(data[index]);
        index++;
    }
    return std::make_pair(train_data, test_data);
}


//构造函数
LogisticRegression::LogisticRegression(int size, double lr){
    this->learning_rate = lr;
    this->init_weights(size);
}
LogisticRegression::~LogisticRegression(){}    //析构函数

//打印输出权重信息
void LogisticRegression::print_weights(){
    for(int i=0;i<this->weights.size();i++){
        std::cout<<this->weights[i]<<" ";
    }
    std::cout<<std::endl;
}

//权重参数初始化
void LogisticRegression::init_weights(int size){
    //产生特定分布的随机数
    std::random_device rd_device;
    std::mt19937 rd_generator(rd_device());
    std::uniform_int_distribution<int> dist(1,52);
    auto gen = [&dist,&rd_generator](){return dist(rd_generator);};

    //构建初始化权重
    std::vector<double> weights(size+1,0);
    std::generate(weights.begin(),weights.end(),gen);
    this->weights.assign(weights.begin(),weights.end());
}




//训练过程
void LogisticRegression::train(std::vector<IrisData> train_data, int epoch){
    std::cout<<"Training Start...." <<std::endl;
    while(epoch){
        epoch--;
        //遍历所有样本
        for(auto data: train_data){
            //计算该样本的概率
            double weight_sum = 0;
            for(int i=0;i<this->weights.size();i++){
                weight_sum += this->weights[i]*data.fields[i];
            }
            double predicted_value = 1/(1+std::exp(-weight_sum));    //logistic回归
            double true_value = static_cast<double>(data.label);
            //更新权重--sgd
            for(int i=0;i<this->weights.size();i++){
                double gradient_descent = (predicted_value-true_value)*data.fields[i];
                this->weights[i] -= this->learning_rate*gradient_descent;
            }
        }
    }
    std::cout<<"Training Done." <<std::endl;
    this->print_weights();
}


//测试过程
void LogisticRegression::predict(std::vector<IrisData> test_data){
    std::cout<<"Predict Start...."<<std::endl;
    //计算测试集准确率
    int cnt = 0;
    for(auto data:test_data){
        int true_label = data.label;
        double weight_sum = 0;
        for(int i=0;i<this->weights.size();i++){
            weight_sum += this->weights[i]*data.fields[i];
        }
        double predicted_value = 1/(1+std::exp(-weight_sum));
        int predict_label = predicted_value>=0.5?1:0;    //二分类
        if(true_label==predict_label) cnt++;
    }
    double acc = static_cast<double>(cnt)/static_cast<double>(test_data.size());
    std::cout<<"Predict Done."<< std::endl;
    std::cout<<"The accuracy of test data is "<<acc<<" ("<<cnt<<"/"<<test_data.size()<<")"<<std::endl;
}







