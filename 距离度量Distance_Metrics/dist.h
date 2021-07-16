#include <iostream>
#include <iomanip>　
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <ctime>

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
9、杰卡德相似系数
10、编辑距离
11、DTW 距离
12、KL 散度

注：
2、3、4可由1推演而来；
8、9一起分析；
*/


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
	void DisPlay();//显示所有点对和距离结果
	void CalEuclideanDis(); //2、欧氏距离调用
	void CalManhattanDis(); //3、曼哈顿距离调用
	void CalChebyshevDis(); //4、切比雪夫距离调用
	void InitStr();  // 8：汉明字符串初始化：非二进制串和二进制串两种
	void CalHammingDis();  //8、汉明距离调用
	
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
	int HammingDis();  //8、汉明距离定义
	double JaccardSimilarity(); //9、杰卡德相似系数定义
};
