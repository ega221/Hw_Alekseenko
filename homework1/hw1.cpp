#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double find_cos(double main_x, double main_y, double x, double y)
{
    return round((main_x * x + main_y * y) / (sqrt(x * x + y * y) * sqrt(main_y * main_y + main_x * main_x)) *
                 10000000000.0) / 10000000000.0;
}


int main()
{
    double main_x;
    double main_y;
    double cos;
    double leftmost_x = 0;
    double leftmost_y = 0;
    double leftmost_cos = 1;
    double rightmost_x = 0;
    double rightmost_y = 0;
    double rightmost_cos = 1;
    double x;
    double y;


    ifstream input_file("in.txt");
    input_file >> main_x >> main_y;

    while(input_file >> x >> y)
    {
        cos = find_cos(main_x, main_y, x, y);
        if (main_y*x < main_x*y)
        {
            if (cos <= leftmost_cos)
            {
                leftmost_cos = cos;
                leftmost_x = x;
                leftmost_y = y;
            }
        } else if(cos <= rightmost_cos)
        {
            rightmost_cos = cos;
            rightmost_x = x;
            rightmost_y = y;
        }

    }
    input_file.close();


    cout << "Leftmost: " << leftmost_x << ' ' << leftmost_y << endl;
    cout << "Rightmost: " << rightmost_x << ' ' << rightmost_y << endl;

    return 0;
}








