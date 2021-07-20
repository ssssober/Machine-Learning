#include <iostream>
#include <iomanip>　
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <ctime>
#include <set>

using namespace std;

/*
*** Function:	距离度量的c++实现
*** Time:		2021/07/08--
*** Platform：	Windows10+VS2013
*** Result:		---
*** Website:	基本原理： https://www.cnblogs.com/daniel-D/p/3244718.html

***
1、闵可夫斯基距离
2、欧几里得距离
3、曼哈顿距离
4、切比雪夫距离
5、马氏距离
6、余弦相似度
7、皮尔逊相关系数
8、汉明距离
9、杰卡德相似系数/距离
10、编辑距离
11、DTW 距离：序列信号在时间或者速度上不匹配的时候一种衡量相似度的方法，不再给出代码
12、KL 散度

注：
2、3、4可由1推演而来；
8、9一起分析；
*/

struct point2d
{
	int val1;
	int val2;
	int val3;
	int val4;
};

struct pointbuff
{
	double x;
	double y;
	double z;
};

class DISTANCE
{
public:
	void Init();  // 2、3、4：初始化(x,y,z)点对
	
	void MaDisInit(); // 5、初始化(x, y)点对
	void DisPlay();//显示所有点对和距离结果
	void CalEuclideanDis(); //2、欧氏距离调用
	void CalManhattanDis(); //3、曼哈顿距离调用
	void CalChebyshevDis(); //4、切比雪夫距离调用
	//void InitStr();  // 8、汉明字符串初始化
	//void CalHammingDis();  //8、汉明距离调用
	void CalJaccardSimilarity();//9、杰卡德系数和距离调用
	int CalEditDis(string, string);  //10、编辑距离定义
	
private:
	vector<pointbuff> test_vec1; // 随机初始化需要计算的点对vec1
	vector<pointbuff> test_vec2; // 随机初始化需要计算的点对vec2
	vector<double> dis_vec;		 // 存放vec1和vec2点对的距离计算结果
	string flag;  // 标志：调用某个距离函数,用于屏幕打印
	//friend inline double MAXCompare(DISTANCE dictan); //三数比较取最大需要对private的pointbuff进行访问，因此需要定义为friend函数,此处未使用
	double MinkowskiDis(pointbuff &, pointbuff &, int );  //1、闵可夫斯基距离通式(一组距离的定义)
	double EuclideanDis(pointbuff &, pointbuff &);	//2、欧氏距离定义
	double ManhattanDis(pointbuff &, pointbuff &);	//3、曼哈顿距离定义
	double ChebyshevDis(pointbuff &, pointbuff &);  //4、切比雪夫距离定义
	double MahalanobisDis();//5、马氏距离
	int HammingDis(unsigned, unsigned);  //8、汉明距离定义
	void JaccardInit(vector<point2d> &, vector<point2d> &); //杰卡德初始化
	void JaccardSimilarity(point2d &, point2d &, double &, double &); //9、杰卡德相似系数和距离函数定义
	
};
