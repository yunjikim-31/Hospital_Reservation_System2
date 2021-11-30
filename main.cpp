#include "databaseLoading.h"

int main()
{
	MYSQL* con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "mysql_init() failed \n");
		exit(1);
	}

	if (mysql_real_connect(con, "localhost", "connectuser", "1234",
		"molou", 0, NULL, 0) == NULL)

	{
		finish_with_error(con);
	}

	// testdb���� Cars ���̺��� ��� ������
	if (mysql_query(con, "SELECT * FROM doc_info"))
	{
		finish_with_error(con);
	}

	// mysql_store_result�Լ��� result set�� ��������
	// result set�� MYSQL_RES ����ü�� �����Ѵ�
	MYSQL_RES* result = mysql_store_result(con);

	if (result == NULL)
	{
		finish_with_error(con);
	}

	// mysql_num_fields �Լ��� ���̺��� Column ���� �˾Ƴ���
	int num_fields = mysql_num_fields(result);

	// 

	MYSQL_ROW row;

	/*
		row�� ���������� �ݺ��ؼ� row�� �������鼭
		������ ����ŭ row�� ������ �ֿܼ� ����Ѵ�
	*/
	while (row = mysql_fetch_row(result))
	{
		for (int loop = 0; loop < num_fields; loop++)
		{
			printf("%s ", row[loop] ? row[loop] : "NULL");
		}
		printf("\n");
	}

	// result set�� ����(free)���ش�

	mysql_free_result(result);

	mysql_close(con);

	exit(0);
}

void finish_with_error(MYSQL* con)
{
	fprintf(stderr, "%s \n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

bool compare(int temp, int oxygen)
{
	
}