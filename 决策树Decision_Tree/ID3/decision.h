#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
using namespace std;


/*
*** *** Function:	决策树的C++实现
*** *** Author	:	TheDetial
*** *** Platform:	win10+vs2013
*** *** Time	:	2021/8/9
*** *** Result	:	
*** *** Website	:
*/

/*
ID3：
（1）多种特征最终决定了分类结果；
（2）每种特征下有多个特征标签；
（3）需要计算每种特征的信息熵：等于该种特征下的多个特征标签分别计算信息熵后综合得来；
（4）信息熵大小决定每一次决策时使用哪种特征；
*/


//DECTREE
namespace DECTREE
{
	

	struct sinData			//单个特征和最后的标签，用于统计次数
	{
		string x;			//单一特征
		string y;			//对应的label
		int xytimes;		//x+y的组合出现的次数
		int xtimes;
	};

	struct point
	{
		string xp;
		double prob;
	};

	class ID3
	{
	public:
		void init(string filePath);				//初始化
		void calEntropy();						//计算信息熵
		void decID3();							//ID3算法调用函数
		
		vector<float> vecProb;								//存储每一种特征的信息熵
	private:
		vector<vector<string>> vecData;						//载入原始数据
		//vector<float> vecProb;								//存储每一种特征的信息熵
		vector<string> strSplit(string str, string sep);	//切割字符串
		int calTimes(string x, string y);					//统计次数
		inline double calLog(int num1, int num2);			//计算log结果
		vector<sinData> singleTimes();						//计算各出现次数
		vector<vector<sinData>> sortVec();					//重排vecSingle的函数	
	};



	class C45:public ID3
	{
	public:
		

	private:

	};
}

