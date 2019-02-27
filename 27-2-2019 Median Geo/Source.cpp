#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <iostream>
#include <cmath>
#include <iomanip>

#define Depth 35
#define maxn 1000
#define eps 0.001
#define inf 1e18 

#define foru(l,r,step) for ( int i = l; i<r; i+= step)

using namespace std;

struct point {
	double x, y;
};

struct tree {
	point pos;
	int type;
};

struct farm {
	tree TreeArr[maxn];
	point bot_left;
	point top_right;
	int n;
};

void countx(farm a) {
	int countarr[3] = { 0,0,0 };

	foru(0, a.n, 1)
		countarr[a.TreeArr[i].type]++;
	cout << countarr[0] << " ";
	cout << countarr[1] << " ";
	cout << countarr[2] << endl;
}
void CalcP(farm &a) {
	a.bot_left.x = a.TreeArr[0].pos.x, a.bot_left.y = a.TreeArr[0].pos.y;
	a.top_right = a.bot_left;

	foru(0, a.n, 1)
	{
		if (a.bot_left.x > a.TreeArr[i].pos.x)
			a.bot_left.x = a.TreeArr[i].pos.x;

		if (a.bot_left.y > a.TreeArr[i].pos.y)
			a.bot_left.y = a.TreeArr[i].pos.y;

		if (a.top_right.x < a.TreeArr[i].pos.x)
			a.top_right.x = a.TreeArr[i].pos.x;

		if (a.top_right.y < a.TreeArr[i].pos.y)
			a.top_right.y = a.TreeArr[i].pos.y;
	}
	cout << 2 * (a.top_right.x - a.bot_left.x + a.top_right.y - a.bot_left.y) << endl;
}
double sqr(double x)
{
	return (x*x);
}
double Distance(double x1, double y1, double x2, double y2) {
	return (sqrt(sqr(x1 - x2) + sqr(y1 - y2)));
}
double CalcSumDis(farm a, double x, double y) {
	double Sum = 0;
	foru(0, a.n, 1)
		Sum += Distance(x, y, a.TreeArr[i].pos.x, a.TreeArr[i].pos.y);
	return Sum;

}
// Search1D with x is defined 
double F(farm a, double _X) { 
	double L, R, y_mid1, y_mid2;

	L = a.bot_left.y;
	R = a.top_right.y;
	//	cout << L << ' ' << R << endl;
	while(R-L > eps)
	{
		y_mid1 = L + (R - L) / 3.0;
		y_mid2 = R - (R - L) / 3.0;
		double temp1 = CalcSumDis(a, _X, y_mid1);
		double temp2 = CalcSumDis(a, _X, y_mid2);

		if (temp1 > temp2) L = y_mid1;
		else R = y_mid2;


		//		cout << L << " " <<  << endl;
		//		cout << temp1 << " " << temp2 << endl;
		//		cout << "_________________" << endl;
	}
	return ((L+R)/2);
}
void LocalSearch2D(farm a) {
	double L, R, x_mid1, x_mid2;
	L = a.bot_left.x;
	R = a.top_right.x;
	double y = inf;
	while (R - L > eps)
	{
		x_mid1 = L + (R - L) / 3.0;
		x_mid2 = R - (R - L) / 3.0;
		double y_temp1 = F(a, x_mid1);
		double y_temp2 = F(a, x_mid2);
		double temp1 = CalcSumDis(a, x_mid1, y_temp1);
		double temp2 = CalcSumDis(a, x_mid2, y_temp2);
		if (temp1 > temp2) L = x_mid1;
		else R = x_mid2;
	}	

	cout << fixed << L << ' ' << (F(a, L)) << endl;
}

double climb(farm a, double x, double R) {
	double G = F(a,x);
	for (int i = 1; i <= Depth; i++) {
		R /= 2;
		double G1 = F(a, x - R);
		double G2 = F(a, x + R);
		if (G < G1 || G < G2) {
			if (G1 > G2) { x -= R; G = G1; }
			else { x += R; G = G2; }
		}
	}
	return x;	
}
void GlobalSearch(farm a) {
	double  L = a.bot_left.x;
	double  R = a.top_right.x;
	double Length = ceil(R - L);
	double  res = inf;
	point checkpoint;
//	cout << Length << endl;
	const int B = 100;
	foru(1, B + 1, 1)
	{
		double x_tmp = climb(a, L + Length / B * i * 1.0, Length / B * 1.0);
		double y_tmp = F(a,x_tmp);
		double res_tmp = CalcSumDis(a, x_tmp, y_tmp);
	
		//	cout << "X = " << L + Length / B * i*1.0 << " R = " << Length / B * 1.0 << endl;
		
		if (res_tmp < res) {
			res = res_tmp;
			checkpoint.x = x_tmp;
			checkpoint.y = y_tmp;
		}
	}
	cout << checkpoint.x << ' ' << checkpoint.y << endl;

}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	farm S;
	cin >> S.n;
	foru(0, S.n, 1)
		cin >> S.TreeArr[i].pos.x >> S.TreeArr[i].pos.y >> S.TreeArr[i].type;

	countx(S);
	CalcP(S);

	//cout << Search1D(S, 1.0);
	//LocalSearch2D(S);

	GlobalSearch(S);
	return 0;

}