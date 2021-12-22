#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

double get_x(string num) {
    int probel = num.find(" "); // возвращается номер пробела
    string X;
    for (int i = 0; i<probel; ++i){
        X.append(1, num[i]); // добавление в конец строки 1 символ num[i]
    }
    double x = atof(X.c_str());
    return x;
}

double get_y(string num)
{
    int probel = num.find(" "); // возвращается номер пробела
    string Y;
    for (int i = probel; i<num.length(); ++i){
        Y.append(1, num[i]); // добавление в конец строки 1 символ num[i]
    }
    double y = atof(Y.c_str());
    return y;
}

void phys(double x0,double h0, double vx, double vy, vector<double> &X, vector<double> &H, int &result, int dir)
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
            phys(X[i], y, vx, vyt, X, H, result, dir);
            return;
        }
    }
}




int main(int argc, char** argv)
//int main()
{

    string input_filename;

    if (argc == 2)
    {
        input_filename = argv[1];
    } else {
        input_filename = "input.txt";
    }
    ifstream file_in(input_filename);


    // все необходимые переменные:
    int sector=0;
    double h0;
    double vx;
    double vy;
    double t; // текущее время
    double y; // высота полета шарика при данном t
    vector<double> X;
    vector<double> Y;
    string num;

    if (file_in.is_open())
    {
        // Получаем начальную высоту и координаты вектора начальной скорости:
        getline(file_in,num);
        h0 = atof(num.c_str());
        getline(file_in,num);
        vx = get_x(num);
        vy = get_y(num);

        //Непосредственно сам рассчет

        // Сначала мы считаем данные до 1го столкновения
        // dir: 1 - вправо, -1 - влево

        while (getline(file_in,num))
        {
            X.push_back(get_x(num));
            Y.push_back(get_y(num));

            t =  (X.back() - 0)/(vx);
            y =  h0 + vy * t - 9.81 * t * t / 2;

            if(Y.back() < y) // если пролетает выше
            {
                sector++;
            }
            else if((y < 0) || (sector == 0)) // если не долетел до следующей
            {

            }
            else // столкновение
            {
                double vy_t = vy - 9.81 * t ;
                phys(X.back(), y, vx, vy_t, X, Y, sector, -1);

            }
        }
    }
    cout << sector;

    return 0;
}
