#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
using namespace std;


/*
*** *** Function	:	决策树的C++实现
*** *** Author		:	TheDetial
*** *** Platform	:	win10+vs2013
*** *** Time		:	2021/8/9、2021/8/17(debug)
*** *** Result		:
*** *** Website		:   
*/

/*
ID3：
（1）多种特征最终决定了分类结果，每种特征下有多个特征标签；
（2）需要计算每种特征的信息熵：等于该种特征下的多个特征标签分别计算信息熵后综合得来；
（3）信息增益大小决定每一次决策时使用哪种特征；

 [注]：
 信息增益=总体信息熵-条件信息熵，总体信息熵是一定的，信息增益越大表示该特征的条件信息熵越小，即不确定度越小，系统越有序；
 每次使用特征X进行决策后，需要按照X下的特征标签将数据重新进行划分，并再次计算划分后数据的总体信息熵，条件信息熵和信息增益；
 测试：给定一组待预测数据标签（只有特征X，没有标签Y），需要按照决策树的决策流程预测出该测试数据的标签Y；
 需要记录每次决策使用的特征X下的特征标签，送入新数据后按照此决策流程进行决策！决策流程即为二（多）叉树形式；
  
  *** *** *** *** *** 决策树(多叉树构建) *** *** *** *** *** 
 （1）初始化根节点,节点成员：value（特征），子树（X1），子树(X2),子树（Xi）...子树(Xn)；
 （2）由于每条特征X下的特征标签Xi数目不一致，因此每次决策后子树的创建数目是不固定的；
 （3）决策树最终的叶子节点为最后的标签Yi；
 （4）决策树的生长和决策过程是同步的，每决策一次，树生成一层；
 （5）针对待测数据，特征依次通过根节点和子树节点进行判断，找到最后归属的叶子结点即为该数据的标签Y；

 伪代码流程：
 决策树构建开始：
		(1)计算该批数据总体信息熵H(D){计算每种标签Y的次数，计算每种标签的信息熵，所有标签信息熵加和得到总体信息熵}
		(2)计算该批数据每种特征X的条件信息熵：
			for i in 特征X：
				for j in 特征X的特征标签Xn:
							特征标签Xj的信息熵
				每种特征X的条件信息熵H(D|X)
		(3)计算该批数据每种特征X的信息增益：
		    for i in 特征X：
				G(X)=H(D)-H(D|X)
		(4)根据信息增益大小排序，选择最大的信息增益对应的特征做为此次决策特征；
		(5)根据此次决策特征X下的不同特征标签Xi构建此层决策树：
			for i in 特征X：
				构建此层决策树节点
		(6)决策后得到新的数据，对决策后的新数据循环(1)-(5)步，直至所有特征判断结束；
		(7)当某批数据的总体信息熵为0时，说明数据完全有序，将此标签做为此步决策的最终叶子节点即可，不再进行下一步决策操作；
决策树构建结束；	
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



	struct entropy
	{
		int colum;
		double prob;
	};


	class ID3
	{
	public:
		// *** *** 变量 *** ***
		vector<float> vecProb;					//存储每一种特征的信息熵

		// *** *** 函数 *** ***
		void init(string filePath);				//初始化
		void calEntropy();						//计算信息熵
		
		
		//
		void functionTest();
	private:
		// *** *** 变量 *** ***
		vector<vector<string>> vecData;						//存放原始数据
		set<string> labSet;									//存标签Label

		// *** *** 函数 *** ***
		vector<string> strSplit(string str, string sep);	//切割字符串
		int calTimes(string x, string y);					//统计次数
		inline double calLog(int num1, int num2);			//计算log结果
		vector<sinData> singleTimes();						//计算各出现次数
		vector<vector<sinData>> sortVec();					//重排vecSingle的函数	

		

		// *** *** 给定数据vector<vector<string>> *** ***
		double totalEntropy(vector<vector<string>>& vec);	//计算总体信息熵
		void condEntropy(vector<vector<string>>& vec);	//计算条件信息熵
		map<string, int> calFeature(vector<vector<string>>& vec, int row);

	};



	class C45:public ID3
	{
	public:
		

	private:

	};
}

