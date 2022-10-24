#include "perceptron.h"

//无权重载入的构造函数
Perceptron::Perceptron(int input_size, double lr){
    this->lr = lr;
    //初始化权重
    this->init(input_size);
}

//有初始权重载入的构造函数
Perceptron::Perceptron(double lr, std::vector<double>& weights){
    this->lr = lr;
    this->weights.assign(weights.begin(),weights.end());
}

//打印输出感知机权重信息
void Perceptron::print_weights(){
    for(auto weight:this->weights){
        std::cout<<weight<<" ";
    }
    std::cout<<std::endl;
}


//初始化权重
void Perceptron::init(int size){
    //产生特定分布的随机数
    std::random_device rd_device;    //非确定性随机数生成设备,通常仅用于播种
    std::mt19937 rd_generator(rd_device());    //产生伪随机数
    std::uniform_int_distribution<int> dist(1,52);    //生成1-52服从均匀分布的整数随机数
    auto gen = [&dist, &rd_generator](){return dist(rd_generator);};

    //构建初始化权重
    std::vector<double> weights(size+1, 0);
    std::generate(weights.begin(),weights.end(),gen);    //根据gen规则产生数字存放在vector容器中
    this->weights.assign(weights.begin(), weights.end());
    //添加偏置
    this->weights[size] = 1;
}

//根据当前样本的值进行分类
bool Perceptron::classifier(std::vector<double> inputs){
    //对当前样本进行分类
    //计算当前样本的wx+b
    double weight_sum = 0;
    for(int i=0;i<inputs.size();i++){
        weight_sum = inputs[i]*this->weights[i];
    }
    //激活函数sign
    int label;
    label = weight_sum>=0?1:-1;
    return label==1?true:false;
}


//训练过程
void Perceptron::train(std::vector<std::pair<std::vector<double>, bool>> train_dataset){
    bool is_finished = false;    //判断当前训练集的样本点是否全部被正确分类
    //直到训练集里样本可以全部正确分类停止
    while(!is_finished){
        is_finished = true;
        //判断每一个样本
        for(auto sample_data:train_dataset){
            std::vector<double> input_data;
            input_data.assign(sample_data.first.begin(),sample_data.first.end());
            input_data.push_back(1);    //添加bias
            bool true_label = sample_data.second;
            //对当前未更新样本进行判断
            bool predict_label = this->classifier(input_data);
            if(true_label==predict_label){
                continue;
            }
            //根据误分类样本信息对权重进行更新--梯度下降
            is_finished = false;
            for(int i=0;i<this->weights.size();i++){
                double error = true_label - predict_label;    //+1 或 -1,将bool标签区间转化为{+1，-1}
                this->weights[i] += this->lr*error*input_data[i];    // w <----- w+n*y*x
            }
        }        
    }
}

//预测分类函数
bool Perceptron::predict(std::vector<double> data){
    data.push_back(1);    //加入bias
    double sum = 0;
    for(int i=0;i<this->weights.size();i++){
        sum += this->weights[i]*data[i];
    }
    bool label = sum>=0?true:false;
    return label;
}


