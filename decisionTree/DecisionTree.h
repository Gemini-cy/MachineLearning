#ifndef DECISIONTREE
#define DECISIONTRE
#include<vector>
#include<math.h>
using namespace std;



//training data 训练所用数据
class TrainData{
public:
    vector<vector<int>> Input;    //一行一条数据
    vector<int> Output;    //允许离散的输出值
    void InsertData(vector<int> data, int out){
        //输入一行数据和目标输出
        Input.push_back(data);    //特征
        Output.push_back(out);    //标签label
    }
};




#endif
