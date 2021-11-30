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

	// testdb에서 Cars 테이블을 모두 가져옴
	if (mysql_query(con, "SELECT * FROM doc_info"))
	{
		finish_with_error(con);
	}

	// mysql_store_result함수로 result set을 가져오고
	// result set을 MYSQL_RES 구조체에 저장한다
	MYSQL_RES* result = mysql_store_result(con);

	if (result == NULL)
	{
		finish_with_error(con);
	}

	// mysql_num_fields 함수로 테이블의 Column 수를 알아낸다
	int num_fields = mysql_num_fields(result);

	// 

	MYSQL_ROW row;

	/*
		row가 없을때까지 반복해서 row를 가져오면서
		영역의 수만큼 row의 내용을 콘솔에 출력한다
	*/
	while (row = mysql_fetch_row(result))
	{
		for (int loop = 0; loop < num_fields; loop++)
		{
			printf("%s ", row[loop] ? row[loop] : "NULL");
		}
		printf("\n");
	}

	cout << endl;


	// 체온, 산소 포화도, 이름
	vector<tuple<double, double, string>> Patient;

	Patient.push_back(make_tuple(39.2, 85.7, "Yeong Ran Lee"));
	Patient.push_back(make_tuple(36.5, 95, "Yoo Jina"));
	Patient.push_back(make_tuple(38, 75, "Soo Yang Kang"));
	Patient.push_back(make_tuple(36.8, 91, "Ji Woong Kang"));
	Patient.push_back(make_tuple(37.8, 70, "Joong ho Lee"));

	sort(Patient.begin(), Patient.end(), sortdesc);

	for (int loopP = 0; loopP < Patient.size(); loopP++)
	{
		cout << get<0>(Patient[loopP]) << ' ';
	}

	cout << endl;
	
	// result set을 해제(free)해준다

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

bool compare(tuple<double, double, string> Pa, tuple<double, double, string> Pb)
{
	// 체온이 같을 경우
	if (get<0>(Pa) == get<0>(Pb))
	{
		// 산소포화도가 높은 경우가 더 먼저 출력
		return get<1>(Pa) > get<1>(Pb);
	}
	else
	{
		return get<1>(Pa) < get<1>(Pb);
	}
}

bool sortdesc(const tuple<double, double, string>& P1,
	const tuple<double, double, string>& P2)
{
	return (get<0>(P1) > get<0>(P2));
}