#include "knn.h"

void KNN::Init(int k, double testx, double testy, string path)
{/*
 1��kֵ��ʼ����
 2����������test��ʼ��
 3��traindata���ݴ���vector��ʼ����
 */
	// 1��kֵ��ʼ��
	m_k = k;  
	// 2����������pointbuf��ʼ��
	pointtest.x = testx;
	pointtest.y = testy;
	// ����teaindata.txt
	std::ifstream list_path(path);
	std::vector<std::string> fileNames;
	std::string stemp;
	while (getline(list_path, stemp))
	{
		fileNames.push_back(stemp);
	}
	// 3��vector��ʼ��
	for (int i = 0; i < fileNames.size(); i++)
	{
		const char* sep = ",";  //�ַ��ָ�
		int posFirst = fileNames[i].find(sep);
		int posLast = fileNames[i].find_last_of(sep);
		//�ֱ�ȡ������x,y��label
		string xx = fileNames[i].substr(0, posFirst);
		string yy = fileNames[i].substr(posFirst + 1, posLast);
		string lab = fileNames[i].substr(posLast + 1, fileNames[i].size());;
		pointbuf c;	//��ʱ����
		int label = atoi(lab.c_str());//atof
		c.x = stod(xx);
		c.y = stod(yy);
		m_vec.push_back(c);
		m_label.push_back(label);
	}
}

double KNN::GetDistance(pointbuf &t1, pointbuf t2)
{
	return pow(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2), 0.5);
}

void KNN::GetDistanceAll()
{
	for (int i = 0; i < m_vec.size(); i++)
	{
		dic_vec.push_back(get_distance(m_vec[i], pointtest));
	}

	//map<pointbuf, const char*>::iterator iter;
	//for (iter = m_map.begin(); iter != m_map.end(); iter++)
	//{	
	//	//cout << iter->first.x << "  " << iter->second << endl;
	//	double dis = get_distance(pointtest, iter->first);
	//	mm_map.insert(pair<double, const char*>(dis, iter->second));
	//}
}
//����map�������ԣ�����key��С�������򣨼������õ���dic������ͬ��
void KNN::SmallSort()
{
	for (int i = 0; i < dic_vec.size(); i++)
	{
		dic_map.insert(make_pair(dic_vec[i], m_label[i]));
	}
}

void KNN::SeekProb()
{
	//1��ȡ��ǰk��dis��label��vector
	int n = 0;
	vector<int> k_label;
	map<double, int>::iterator iter;
	//��ӡ�����е�distance�Ͷ�Ӧ��label
	for (iter = dic_map.begin(); iter != dic_map.end(); iter++)
	{
		cout << iter->first << "---" << iter->second << endl;
	}

	//ȡǰm_k��label����ӡ
	for (iter = dic_map.begin(); iter != dic_map.end(); iter++)
	{
		n++;
		if (n <= m_k)
			k_label.push_back(iter->second);
		else
			break;
	}
	//2�������������label
	int sum_a = 0;
	int sum_b = 0;
	for (int i = 0; i < m_k; i++)
	{
		cout << k_label[i] << endl;
		if (k_label[i] == 0)
			sum_a++;
		else
			sum_b++;
	}
	int m_label = (sum_a > sum_b) ? 0 : 1;
	cout << "���������������Ϊ�� " << m_label;
	cout << endl << "���Խ���!" << endl;
}