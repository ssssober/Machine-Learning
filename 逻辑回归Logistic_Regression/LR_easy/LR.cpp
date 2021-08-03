#include "LR.h"

//��������
void Logistic::dataLoad(vector<point>& vec, string filepath)
{
	// ����traindata.txt
	std::ifstream list_path(filepath);
	std::vector<std::string> fileNames;
	std::string stemp;
	while (getline(list_path, stemp))
	{
		fileNames.push_back(stemp);
	}
	
	for (int i = 0; i < fileNames.size(); i++)
	{
		const char* sep = ",";
		int posFirst = fileNames[i].find(sep); 
		int posLast = fileNames[i].find_last_of(sep);
		//�ֱ�ȡ������x,y��label
		string xx = fileNames[i].substr(0, posFirst);
		string yy = fileNames[i].substr(posFirst + 1, posLast);
		string lab = fileNames[i].substr(posLast + 1, fileNames[i].size());
		int labint = atoi(lab.c_str());//atof
		point c;
		c.x0 = 1.0;
		c.x1 = stod(xx);
		c.x2 = stod(yy);
		c.label = labint;
		vec.push_back(c);
	}
}

//����1������ݶ��½� ---> һ��ȡһ������
void Logistic::stoGradDescent(int iters, float steps)
{
	weights = { 1.0, 1.0, 1.0 };//Ȩ�س�ʼ��Ϊ1.0���������w����=����x��Ŀ+1
	
	for (int n = 0; n < iters; n++)//һ�ε���������������ȡ��
	{
		cout <<"����������" << n << "  ����w��" << "w0: " << weights[0] << "  w1: " << weights[1] << "  w2: " << weights[2] << endl;
		for (int i = 0; i < dataTrain.size(); i++)//һ��ȡһ�飬����һ�β���w
		{

			//����w���£���Ҫһ�θ���w0,w1,w2��������
			float z = weights[0] * dataTrain[i].x0 + weights[1] * dataTrain[i].x1 + weights[2] * dataTrain[i].x2;//sigmoid����������
			float p = sigmoid(z); // sigmoidԤ�����y
			vector<float> w_delt;//�ݶȣ���w��ƫ�� 
			//ƫ������
			w_delt.push_back(-(dataTrain[i].label - p)*dataTrain[i].x0);
			w_delt.push_back(-(dataTrain[i].label - p)*dataTrain[i].x1);
			w_delt.push_back(-(dataTrain[i].label - p)*dataTrain[i].x2);
			add_vector(weights, w_delt, steps);//���²���w0, w1, w2
		}
	}
}

//sigmoid   --->�������
float Logistic::sigmoid(float wx)
{
	return 1 / (1 + exp(-wx));
}


//һά������Ӧλ�üӷ�����
void Logistic::add_vector(vector<float> &vec_w, vector<float>& vec_wdelt,float steps)
{
	for (int i = 0; i < weights.size(); i++)
	{
		vec_wdelt[i] *= -steps; //w_delt���Բ���
		vec_w[i] += vec_wdelt[i];//������Ӧλ�ӷ�
	}
}

//�ع�����
void Logistic::plotFilters()
{
	
}

//�ع����
void Logistic::logTest(string savepath)
{
	ofstream fout(savepath);
	fout << "����X1��" << "����X2��" << "ԭʼ��ǩ��" << "Ԥ�����P," << "Ԥ���ǩ" << endl;
	int trueNum = 0;
	for (int i = 0; i < dataTest.size(); i++)
	{
		float z = weights[0] * dataTest[i].x0 + weights[1] * dataTest[i].x1 + weights[2] * dataTest[i].x2;//sigmoid����������
		float p = sigmoid(z); // sigmoidԤ�����y
		int prediction = p > 0.5 ? 1 : 0;
		if (prediction == dataTest[i].label)
		{
			trueNum++;
		}
		//д��txt���뱾��
		fout << dataTest[i].x1 << "," << dataTest[i].x2 << "," << dataTest[i].label << "," << p << "," << prediction << endl;

	}
	cout << "��ȷԤ���ʣ� " << 1.0*trueNum / dataTest.size()  << endl;
}
