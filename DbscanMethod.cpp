#include "DbscanMethod.h"

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

void Dbscan(DbscanPoint* dbscan_point_ptr, int cluster_current)
{
	if (dbscan_point_ptr->visited == VISIT_NO)
	{
		S_temp++;
		std::cout << "������" << S_temp << "����" << std::endl;

		dbscan_point_ptr->cluster += cluster_current;
		dbscan_point_ptr->visited = VISIT_YES;
	}
	else
		return;
	if (dbscan_point_ptr->point_type == POINT_CORE)
		for (auto m : dbscan_point_ptr->vec_dbscan_point_ptr)
			Dbscan(m, cluster_current);
	else
		dbscan_point_ptr->point_type = POINT_BOUNDARY;//����������������������������ϱ߽��Ķ��壬���Ըĳɱ߽��
}


void DbscanMethod(std::vector<DbscanPoint>& vec_dbscan_point, double Eps, int MinPts)
{
	size_t num = vec_dbscan_point.size();
	
	//��1��
	//�������������ľ���
	//ȷ��ÿ���������
	//��ÿ�������������ڵĵ�
	for (size_t i = 0; i != num; ++i)
	{
		for (size_t j = i + 1; j != num; ++j)
		{
			double distance = CalculateDistance(&vec_dbscan_point[i], &vec_dbscan_point[j]);
			if (distance <= Eps)
			{
				//�ܶ�����
				vec_dbscan_point[i].num_pts++;				
				vec_dbscan_point[j].num_pts++;
				//�����¼���Լ���������
				vec_dbscan_point[i].vec_dbscan_point_ptr.push_back(&vec_dbscan_point[j]);
				vec_dbscan_point[j].vec_dbscan_point_ptr.push_back(&vec_dbscan_point[i]);

			}
		}
		if (vec_dbscan_point[i].num_pts >= MinPts)			//�ܶȴ���һ��ֵ���Ǻ��ĵ�
			vec_dbscan_point[i].point_type = POINT_CORE;		
		else
			vec_dbscan_point[i].point_type = POINT_NOISE;	//ʣ�µ���ʱ��Ϊ����
	}

	//��2��
	//��ʼ���
	int cluster_current = 0;
	for (size_t i = 0; i != num; ++i)
		if (vec_dbscan_point[i].visited == VISIT_NO && vec_dbscan_point[i].point_type == POINT_CORE)
		{
			cluster_current++;//����һ���µĴ�
			vec_dbscan_point[i].cluster += cluster_current;
			vec_dbscan_point[i].visited = VISIT_YES;

			S_temp++;
			std::cout << "������" << S_temp << "����" << std::endl;

			for (auto m : vec_dbscan_point[i].vec_dbscan_point_ptr)
				Dbscan(m, cluster_current);
		}
}