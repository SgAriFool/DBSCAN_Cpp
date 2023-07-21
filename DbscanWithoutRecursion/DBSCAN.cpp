#include "DBSCAN.h"

double CalculateDistance(DbscanPoint* point1, DbscanPoint* point2)
{
	if (point1->xn.size() != point2->xn.size())
	{
		std::cout << "���ݵ��쳣" << std::endl;
		return 0;
	}
	double distance = 0;

	double sum = 0;
	for (size_t i = 0; i != point1->xn.size(); ++i)
		sum += (point1->xn[i] - point2->xn[i]) * (point1->xn[i] - point2->xn[i]);

	distance = sqrt(sum);

	return distance;
}


void DbscanMethod(std::vector<DbscanPoint>& vec_dbscan_point, const double& Eps, const int& MinPts)
{
	std::vector<DbscanPoint*> vec_dbscan_point_ptr;//��ת��Ϊָ�룬��֤���������һ����
	for (auto &i : vec_dbscan_point)
		vec_dbscan_point_ptr.push_back(&i);

	//��1��
	//�������������ľ���
	//ȷ��ÿ���������
	//��ÿ�������������ڵĵ�
	for (auto m : vec_dbscan_point_ptr)
	{
		for (auto n : vec_dbscan_point_ptr)
			if (n->calculated == CALCULATE_NO && m != n)
			{
				double distance = CalculateDistance(m, n);

				if (distance <= Eps)
				{
					//�ܶ�����
					m->num_pts++;
					n->num_pts++;
					//�����¼���Լ���������
					m->vec_dbscan_point_ptr.push_back(n);
					n->vec_dbscan_point_ptr.push_back(m);
				}
			}
		m->calculated = CALCULATE_YES;

		if (m->num_pts >= MinPts)			//�ܶȴ���һ��ֵ���Ǻ��ĵ�
			m->point_type = POINT_CORE;
		else
			m->point_type = POINT_NOISE;	//��������ʱ��Ϊ����
	}

	int cluster_current = 0;
	for (auto m : vec_dbscan_point_ptr)
	{
		std::stack<DbscanPoint*> ps;

		if (m->visited == VISIT_YES || m->point_type != POINT_CORE)
			continue;
		++cluster_current;//����һ���µĴ�
		m->cluster = cluster_current;

		ps.push(m);
		DbscanPoint* current_ptr;

		while (!ps.empty())
		{
			current_ptr = ps.top();
			ps.pop();
			if (current_ptr->visited == VISIT_YES)
				continue;
			current_ptr->visited = VISIT_YES;
			if (current_ptr->point_type == POINT_CORE)
			{
				for (auto n : current_ptr->vec_dbscan_point_ptr)
				{
					if (n->visited == VISIT_YES)
						continue;
					ps.push(n);					
				}
				current_ptr->cluster = cluster_current;
			}
			else
			{
				current_ptr->point_type == POINT_BOUNDARY;
				current_ptr->cluster = cluster_current;
			}

			++S_temp;
			std::cout << "������" << S_temp << "����" << std::endl;
		}
	}
}