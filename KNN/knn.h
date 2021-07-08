#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct pointbuf
{
	double x;
	double y;
};

//����KNN��
class KNN
{
public:
	void Init(int k, double testx, double texty, string path); //��ʼ������
	void GetDistanceAll();
	void SmallSort();         // ŷ�Ͼ����С��������
	void SeekProb();		// ���ǰk�������У�ռ�������ʵı�ǩlabel
private:
	int m_k;	//kֵ��С
	pointbuf pointtest;//��������
	vector<pointbuf> m_vec;// ���traindata��x,y����
	vector<double> dic_vec;//��ż���ŷ�Ͼ�����vector
	vector<int> m_label;//���traindata�б�ǩ0��1
	map<double, int> dic_map; //��dis_vec��m_label����
	double GetDistance(pointbuf &, pointbuf ); //�������������pointbuf֮���ŷ�Ͼ���
	
};
