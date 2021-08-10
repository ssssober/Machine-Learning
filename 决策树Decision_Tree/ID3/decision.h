#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
using namespace std;


/*
*** *** Function:	��������C++ʵ��
*** *** Author	:	TheDetial
*** *** Platform:	win10+vs2013
*** *** Time	:	2021/8/9
*** *** Result	:	
*** *** Website	:
*/

/*
ID3��
��1�������������վ����˷�������
��2��ÿ���������ж��������ǩ��
��3����Ҫ����ÿ����������Ϣ�أ����ڸ��������µĶ��������ǩ�ֱ������Ϣ�غ��ۺϵ�����
��4����Ϣ�ش�С����ÿһ�ξ���ʱʹ������������
*/


//DECTREE
namespace DECTREE
{
	

	struct sinData			//�������������ı�ǩ������ͳ�ƴ���
	{
		string x;			//��һ����
		string y;			//��Ӧ��label
		int xytimes;		//x+y����ϳ��ֵĴ���
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
		void init(string filePath);				//��ʼ��
		void calEntropy();						//������Ϣ��
		void decID3();							//ID3�㷨���ú���
		
		vector<float> vecProb;								//�洢ÿһ����������Ϣ��
	private:
		vector<vector<string>> vecData;						//����ԭʼ����
		//vector<float> vecProb;								//�洢ÿһ����������Ϣ��
		vector<string> strSplit(string str, string sep);	//�и��ַ���
		int calTimes(string x, string y);					//ͳ�ƴ���
		inline double calLog(int num1, int num2);			//����log���
		vector<sinData> singleTimes();						//��������ִ���
		vector<vector<sinData>> sortVec();					//����vecSingle�ĺ���	
	};



	class C45:public ID3
	{
	public:
		

	private:

	};
}

