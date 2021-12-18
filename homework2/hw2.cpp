#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double get_t(double x0, double x, double vx,int dir)
{
    return (x - x0)/(dir*vx);
}

double get_vy(double vy0, double t)
{
    return vy0 - 9.81*t;
}

double get_height(double h0, double vy, double t)
{
    return h0 + vy*t - 9.81/2 * pow(t, 2);
}

void get_h0(ifstream &input_file, double &h) // Функция получения начальной высоты
{
    input_file >> h;
}

void get_v0(ifstream &input_file, double &vx,double &vy) // Функция получения начальной скорости
{

    input_file >> vx >> vy;

}

void get_bar(ifstream &input_file,vector<double> &X, vector<double> &H) // функция считывания параметров столбов
{
    double x;
    double h;
    input_file >> x >>  h;
    X.push_back(x);
    H.push_back(h);
}
void calculate_2(double x0,double h0, double vx, double vy, vector<double> &X, vector<double> &H, int &result,
                 int dir)
{
    double y;
    double t;
    for (int i = result; (i > -1 && i < X.size()); i = i + dir) {
        if (i == -1)
        {
            break;
        }
        t = get_t(x0, X[i+dir], vx, dir);
        y = get_height(h0, vy, t);
        if (H[i + dir] < y)
        {
            result += dir;
        } else if((y < 0) || (result == 0))
        {

        }
        else
        {
            double vyt = get_vy(vy, t);
            dir = dir * -1;
            calculate_2(X[i], y, vx, vyt, X, H, result, dir);
            return;
        }
    }
}


void calculate_1(ifstream &input_file, double &h0, double &vx, double &vy, vector<double> &X, vector<double> &H,
    int &result)
{
    string line;
    double t;
    double y;
    while (getline(input_file,line))
    {
        get_bar(input_file, X, H);
        t = get_t(0, X.back(), vx, 1);
        y = get_height(h0, vy, t);
        if(H.back() < y)
        {
            result++;
        }
        else if((y < 0) || (result == 0))
        {
            return;
        }
        else
        {
            double vyt = get_vy(vy, t);
            calculate_2(X.back(), y, vx, vyt, X, H, result, -1);
            return;
        }
    }
}



int main(int argc, char** argv)
{
    string input_filename;

    if (argc == 2)
    {
        input_filename = argv[1];
    } else {
        input_filename = "input.txt";
    }
    ifstream input_file(input_filename);

    // Начальные данные
    double h0;
    double vx;
    double vy;

    // Результат
    int result = 0;

    // Вспомогательные переменные
    int i = 0;
    string line;

    // Векторы с координатами и высотами столбов
    vector<double> X;
    vector<double> H;

    // Получаем начальные данные
    get_h0(input_file, h0);
    get_v0(input_file, vx, vy);

    calculate_1(input_file, h0, vx, vy, X, H, result);

    cout << result<< endl;
    return 0;
}
