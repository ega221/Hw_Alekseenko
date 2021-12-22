#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void get_prop(ifstream &input_file,double &prop)
{
    input_file >> prop;
}
void get_bar(ifstream &input_file, vector<double> &X, vector<double> &H)
{
    double temp;
    get_prop(input_file, temp);
    X.push_back(temp);
    get_prop(input_file, temp);
    H.push_back(temp);
}


void calculate(double x0,double h0, double vx, double vy, vector<double> &X, vector<double> &H, int &result, int dir)
{
    double y;
    double t;
    for (int i = result; i < X.size(); i = i + dir)
    {
        if (i == -1)
        {
            break;
        }
        t = (X[i+dir] - x0)/(vx);

        y =  h0 + vy * t * dir - 9.81 * t * t / 2;

        if (H[i + dir] < y) // если пролетает выше
        {
            result += dir;
        } else if((y < 0) || (result == 0)) // если не долетел до следующей
        {
            return;
        }
        else // столкновение
        {
            double vyt = vy - 9.81 * t * dir;

            dir = dir * -1;
            calculate(X[i], y, vx, vyt, X, H, result, dir);
            return;
        }
    }
}




int main(int argc, char** argv)
//int main()
{

    string filename;

    if (argc == 2)
    {
        filename = argv[1];
    } else {
        filename = "input.txt";
    }
    ifstream input_file(filename);


    // все необходимые переменные:
    int sector=0;
    double h0;
    double vx;
    double vy;
    string line;

    vector<double> X;
    vector<double> H;

    if (input_file.is_open())
    {
        // Получаем начальную высоту и координаты вектора начальной скорости:
        get_prop(input_file,h0);
        get_prop(input_file,vx);
        get_prop(input_file,vy);

        //Непосредственно сам рассчет

        // Сначала мы считаем данные до 1го столкновения
        // dir: 1 - вправо, -1 - влево
        // func
        double t; // текущее время
        double y; // высота полета шарика при данном t
        while (getline(input_file, line))
        {
            get_bar(input_file, X, H);

            t =  (X.back() - 0)/(vx);
            y =  h0 + vy * t - 9.81 * t * t / 2;

            if(H.back() < y) // если пролетает выше
            {
                sector++;
            }
            else if((y < 0) || (sector == 0)) // если не долетел до следующей
            {
                break;
            }
            else // столкновение
            {
                double vy_t = vy - 9.81 * t ;
                calculate(X.back(), y, vx, vy_t, X, H, sector, -1);
                break;
            }
        }
    }

    cout << sector;
    return 0;
}