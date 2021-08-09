#include "kmeans.h"

//��ʼ��
void KMEAN::init(string filepath, int k)
{
	// ����traindata.txt
	std::ifstream list_path(filepath);
	std::vector<std::string> fileNames;
	std::string stemp;
	while (getline(list_path, stemp))
	{
		fileNames.push_back(stemp);
	}
	vector<float> xx1;
	vector<float> xx2;
	for (int i = 0; i < fileNames.size(); i++)
	{
		const char* sep = ",";
		int posFirst = fileNames[i].find(sep);
		int posLast = fileNames[i].find_last_of(sep);
		//�ֱ�ȡ������x,y��label
		string xx = fileNames[i].substr(0, posFirst);
		string yy = fileNames[i].substr(posFirst + 1, posLast);
		//string lab = fileNames[i].substr(posLast + 1, fileNames[i].size());
		//int labint = atoi(lab.c_str());//atof
		point c;
		//c.x0 = 1.0;
		c.x1 = stod(xx);
		c.x2 = stod(yy);
		xx1.push_back(c.x1);
		xx2.push_back(c.x2);
		c.label = k + 1;  //��k+1��Ϊdata.label��ʼ��
		vecData.push_back(c);
	}

	//����
	bubbleSort(xx1);
	bubbleSort(xx2);
	float x1_min = xx1.front();
	float x2_min = xx2.front();
	vector<float>::iterator itx1 = xx1.end() - 1;
	vector<float>::iterator itx2 = xx2.end() - 1;
	float x1_max = *itx1;
	float x2_max = *itx2;

	//��ʼ��veck���߽������ȡk������,�����ر�ǩ
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 genx1(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::mt19937 genx2(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> disx1(x1_min, x1_max);
	std::uniform_real_distribution<> disx2(x2_min, x2_max);
	for (int i = 0; i < k; i++)
	{
		point cc;
		cc.x1 = disx1(genx1);
		cc.x2 = disx2(genx2);
		cc.label = i;	//k�����ĵ�labelΪi���ɣ�ȡֵ��ΧΪ[0,k-1]
		vecK.push_back(cc);
	}
}

//ŷ�Ͼ���
float KMEAN::eluDistance(point data_pos, point k_pos)
{
	return pow(pow(data_pos.x1 - k_pos.x1, 2) + pow(data_pos.x2 - k_pos.x2, 2), 0.5);
}

//ð������
void KMEAN::bubbleSort(vector<float> &sortVecori)
{
	int index = sortVecori.size() - 1;
	while (index > 1)
	{
		bool flag = true;//��־λ���Ƿ���Ҫ����������Ϊ������Ѿ����������ŵ������
		for (int i = 0; i < index; i++)//ÿ�δ�ͷ��ʼ�Ƚϣ������Ѿ��ŵ�β��
		{
			if (sortVecori[i]>sortVecori[i + 1])
			{
				swap(sortVecori[i], sortVecori[i + 1]);
				flag = false;//��false���ʾ���򣬲����˳�
			}
		}
		index--;
		//��Ϊtrue���ʾ�Ѿ����򣬿���ֱ���˳���������������
		if (flag)
			break;
	}
}

//����data.labelΪ��Ӧ�������ĵ�label���м�ѭ�����£�
void KMEAN::updataLabel(vector<point>& vecdata, vector<point>& veck, vector<int>& veclabel)
{
	//	1. ����ÿ�����ݵ���������
	//  2. ����ÿ�����ݵ��labelΪ��������ĵ�label
	//  3. ��־λ�ж��Ƿ���Ҫ��������flag,ֻҪ��һ�����ݵ��label����ǰ�����仯,��Ҫ����������ȥ,�������ݵ�labelȫ���䣬��ֹͣ����	
	for (int i = 0; i < vecdata.size(); i++)
	{
		//int frontlabel = vecdata[i].label;//����֮ǰ���ݵ��label
		veclabel.push_back(vecdata[i].label);//����֮ǰ���ݵ��label����vector
		float mindis = eluDistance(vecdata[i], veck[0]);
		for (int j = 0; j < veck.size(); j++)
		{
			float eludis = eluDistance(vecdata[i], veck[j]);  
			if (eludis <= mindis)
			{
				vecdata[i].label = veck[j].label;//һֱ���ֽ�����������ĵ�label��data.label
				mindis = eludis;
			}
		}
	}
}

//�Ƚϸ���ǰ���data.label�Ƿ�仯
bool KMEAN::compareLabel(vector<int>& veclabel, vector<point>& vecdata)
{
	for (int i = 0; i < veclabel.size(); i++)
	{
		if (veclabel[i] != vecdata[i].label)
			return flagChange;
	}
	flagChange = true;
	return flagChange;
}

// ����ÿ���ص�������,veck��label���ñ�
void KMEAN::updateK(vector<point>& vecdata, vector<point>& veck)
{
	//1.��ͬlabelΪһ���أ���ͬ�ؼ�������ƽ������
	for (int i = 0; i < veck.size(); i++)
	{
		int num = 0;
		float avgx1 = 0.0f;
		float avgx2 = 0.0f;
		for (int j = 0; j < vecdata.size(); j++)
		{
			if ( veck[i].label == vecdata[j].label )
			{
				avgx1 += vecdata[j].x1;
				avgx2 += vecdata[j].x2;
				num++;
			}
		}
		cout << "num: " << num << endl;  //��ӡÿһ���ص����ݵ����
		avgx1 = avgx1 / num;
		avgx2 = avgx2 / num;
		veck[i].x1 = avgx1;//������������
		veck[i].x2 = avgx2;
	}
}

//kmeans��������
void KMEAN::kmeansCluster(string savepath)
{
	//ע�⣺frontlabel����ÿ��Ҫ���㣡����
	//���ĸ��½���������vecdata��label���ٸı䣨˵��ÿ�����ݵ㱻�ֵ��˺��ʵĴأ�
	while (!flagChange)
	{
		updataLabel(vecData, vecK, frontlabel);//����data��label,ͬʱ�洢data����ǰ��label��frontlabel
		compareLabel(frontlabel, vecData); // �ж����ݵ����ǰ��data.label�Ƿ�ı�
		frontlabel.clear(); //��ÿ�αȶ���data.label�Ƿ�ı��ÿ����Ҫ���㣡����
		//��ӡflag
		if (flagChange == true)//���Ϊtrue��˵������ǰ��data.labelδ�ı䣬���˳�whileѭ�������ٸ���
		{
			cout << "flagChange��" << flagChange  << " ,�������,������д�뱾���ļ�..." << endl;
			break;
		}
		updateK(vecData, vecK);//����k����

		//��ӡvecK��������
		for (int i = 0; i < vecK.size(); i++)//debug
		{
			cout << i << ": " << vecK[i].x1 << "," << vecK[i].x2 << "," << vecK[i].label << endl;
		}

		cout << "flagChange��" << flagChange << endl;
	}

	//������д�뱾��txt
	ofstream fout(savepath);
	for (int i = 0; i < vecData.size(); i++)
	{
		fout << vecData[i].x1 << "," << vecData[i].x2 << "," << vecData[i].label << endl;
	}
	cout << "д������������˳���" << endl;
}
