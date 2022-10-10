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

//decision tree node 决策树节点
class Node{
public:
    int Attribute;    //属性序号
    bool IsLeaf;    //是否是叶节点
    vector<Node*> Num;    //子节点
    Node(int ID, bool a):Attribute(ID), IsLeaf(a){}
};


//decision tree 决策树
class Tree{
private:
    Node* root;    //根节点
    vector<vector<int>> AttrData;    //属性列表
    Node* CreateTree(TrainData data, vector<int> usedAttr);    //ID3算法生成树
    int MostNormalOutput(TrainData data);    //计算所有训练样本的类别数，并返回数量最多的种类
    int Best(TrainData data, vector<int> usedAttr);    //计算信息增益最高的属性
public:

};

//构建决策树
Node* Tree::CreateTree(TrainData data, vector<int> usedAttr){
    Node* root = new Node(0, 0);    //创建根节点
    
    /*1.如果输出标签都一样，则创建一个节点，值为该输出，且为叶节点;
        即当D中所有实例属于同一类，则T为单节点树*/
    bool stopFlag = 1;
    for(unsigned int i=1;i<data.Output.size();i++){
        if(data.Output[i]!=data.Output[i-1]) {
            stopFlag = 0;
            printf("Not all nodes are leaf nodes.\n");
        }
    }
    if(stopFlag){
        printf("All nodes are leaf nodes.\n");
        return new Node(data.Output[0], 1);
    }

    /*2.如果所有属性都用过，那么返回的节点的值为最普遍的输出，且为叶节点；
        若特征A为空，则T为单节点树，并将D中实例数最大的类作为该节点的类标记，返回T*/
    if(usedAttr.size()==AttrData.size()) return new Node(MostNormalOutput(data), 1);

    /*3.选出信息增益最高的属性（特征）作为节点；
        计算A中各特征对D的信息增益，选择信息增益最大的特征Ag*/


}


//计算所有训练样本的类别数，返回数量最多的种类
int Tree::MostNormalOutput(TrainData data){
    vector<int> out;    //记录输出的种类
    vector<int> count;    //记录种类的数量

    /*1.统计当前所有训练样本的标签类别和数量*/
    for(unsigned int i=0;i<data.Output.size();i++){
        bool ex = 0;    //用来判断当前类标签是否出现过，出现过则变为1，则当前样本不放进out中，只是对应位置的count++
        int index = 0;    //当前样本与之前的哪个样本是同一类
        //遍历之前已经存在的标签，查询当前第i个样本标签是否重复
        for(unsigned int j=0;j<out.size();j++){
            if(out[j]==data.Output[i]){
                //出现重复
                ex = 1;
                index = j;
                break;     //此时后面的不需要遍历
            }
        }
        if(ex){
            //出现重复，count++
            count[index]++;
        }else{
            //将不同类标签放入out中，每个标签出现的次数初始值为1（count）
            out.push_back(data.Output[i]);
            count.push_back(1);
        }
    }

    /*2.计算数量最多的种类*/
    int maxIndex = 0;
    int maxCount = 0;
    for(unsigned int i=0;i<count.size();i++){
        if(count[i]>maxCount){
            maxCount = count[i];
            maxIndex = i;
        }
    }
    return out[maxIndex];

}


/*********************************************
 *********************************************
 **************待完成部分在下面***************
 *********************************************
 ******************************************* */


//计算信息增益
int Tree::Best(TrainData data, vector<int> usedAttr){
    vector<double> Gain;    //记录每一个属性的信息增益
    bool used;
    /*将使用过的属性的信息增益设置为0*/

}



#endif
