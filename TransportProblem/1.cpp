#include<iostream>
#include<locale>
using namespace std;

void input(int**, int, int, int*, int*);
void output(int**, int, int, int*, int*);
void balance(int**, int*, int*, int*, int*);
void NorthWestMethod(int**, int, int, int*, int*, int**);
int sumElements(int *, int);
int findOptimal(int**, int, int, int**);

int main()
{
	setlocale(LC_ALL, "Ukrainian");
	int N, M;
	cout << "Кiлькiсть сховищ -> "; cin >> N;
	cout << "Кiлькiсть центрiв використання -> "; cin >> M;
	int **plan = new int*[N + 1];
	int **result = new int*[N + 1];
	for (int i = 0; i < N + 1; i++)
	{
		plan[i] = new int[M + 1];
		result[i] = new int[M + 1];
		for (int j = 0; j < M + 1; j++)
			result[i][j] = 0;
	}
	int *zap = new int[N + 1];
	int *centr = new int[M + 1];
	system("cls");
	input(plan, N, M, zap, centr);
	system("cls");
	output(plan, N, M, zap, centr);
	balance(plan, &N, &M, zap, centr);
	cout << "\n\nПiсля балансування:\n";
	output(plan, N, M, zap, centr);
	NorthWestMethod(plan, N, M, zap, centr, result);
	cout << "\n\nРезультат:\n";
	output(result, N, M, zap, centr);
	cout << "\n\nОптимальне рiшення: " << findOptimal(plan, N, M, result);
	cout << "\n\n";
	system("pause");
	return 0;
}

void input(int **mas, int N, int M, int *zap, int *centr)
{
	cout << "\nЗаповнiть опорний план:\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << i + 1 << " сховище, " << j + 1 << " центр -> "; cin >> mas[i][j];
		}
	}
	cout << "\nЗапаси в сховищах:\n";
	for (int i = 0; i < N; i++)
	{
		cout << i + 1 << " сховище -> "; cin >> zap[i];
	}
	cout << "\nПотреба центрiв:\n";
	for (int i = 0; i < M; i++)
	{
		cout << i + 1 << " центр -> "; cin >> centr[i];
	}
}

void output(int **mas, int N, int M, int *zap, int *centr)
{
	for (int i = 0; i < M; i++)
		cout << "\t" << i + 1 << "ц.";
	cout << "\tЗапаси";
	for (int i = 0; i < N; i++)
	{
		cout << "\n" << i + 1 << "сх.";
		for (int j = 0; j < M; j++)
		{
			cout << "\t" << mas[i][j];
		}
		cout << "\t" << zap[i];
	}
	cout << "\nПотреби";
	for (int i = 0; i < M; i++)
		cout << "\t" << centr[i];
}

void balance(int **mas, int *N, int *M, int *zap, int *centr)
{
	int sum1 = sumElements(zap, *N);
	int sum2 = sumElements(centr, *M);
	if (sum1 > sum2)
	{
		*M = *M + 1;
		for (int i = 0; i < *N; i++)
			mas[i][*M - 1] = 0;
		centr[*M - 1] = sum1 - sum2;
	}
	else if (sum1 < sum2)
	{
		*N = *N + 1;
		for (int i = 0; i < *M; i++)
			mas[*N - 1][i] = 0;
		zap[*N - 1] = sum2 - sum1;
	}
}

int sumElements(int *mas, int N)
{
	int sum = 0;
	for (int i = 0; i < N; i++)
		sum += mas[i];
	return sum;
}

void NorthWestMethod(int **mas, int N, int M, int *zap, int *centr, int **result)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (zap[i] <= centr[j])
			{
				result[i][j] = zap[i];
				centr[j] -= zap[i];
				zap[i] = 0;
				break;
			}
			else
			{
				result[i][j] = centr[j];
				zap[i] -= centr[j];
				centr[j] = 0;
			}
		}
	}
}

int findOptimal(int **mas, int N, int M, int **result)
{
	int sum = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			sum += mas[i][j] * result[i][j];
	return sum;
}