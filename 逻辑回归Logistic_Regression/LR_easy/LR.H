#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

/*
*** Function	:	逻辑回归Logistic Regression的c++实现
*** Author		:	TheDetial
*** Platform	:   Windows10+VS2013
*** Time		:	2021/08/03
*** Result		:	结果已通过。
***
*/


/*
相关知识点：线性回归、sigmoid()、梯度下降（上升）
1.//方法1：随机梯度下降  
2.参数w初始化为1.0：  
3.    //开始迭代  
4.    迭代次数N()  
5.    {  
6.        每次取一组训练数据，直到所有数据取完结束本次迭代()  
7.        {  
8.                更新参数w  
9.        }  
10.    }  
11.    迭代结束，返回参数w  
12.  
13.//方法2：批量梯度下降  
14.参数w初始化为1.0：  
15.    //开始迭代  
16.    迭代次数N()  
17.    {  
18.        每次使用所有训练数据一次性计算：  
19.                更新参数w  
20.    }  
21.    迭代结束，返回参数w  

1.//方法3、小批量梯度下降  
2.参数w初始化为1.0：  
3.    //开始迭代  
4.    迭代次数N()  
5.    {  
6.        每次随机抽取一个Batch的数据计算：  
7.                更新参数w  
8.    }  
9.    迭代结束，返回参数w  

*/

struct point
{	
	float x0;
	float x1;
	float x2;
	int label;
};

class Logistic
{

public:
	void dataLoad(vector<point> &, string filepath);//载入数据
	void stoGradDescent(int iters, float steps);//方法1：随机梯度下降
	void plotFilters();//画出散点图和logistic回归曲线
	void logTest(string);//测试逻辑回归模型好坏
	vector<point> dataTrain;//存储训练数据：特征+label
	vector<point> dataTest;//存储测试数据
	
private:
	float sigmoid(float);//sigmoid函数定义
	vector<float> weights;//训练：权重向量
	void add_vector(vector<float> &vec_w, vector<float>& vec_wdelt, float steps);//向量对应位相加

};
