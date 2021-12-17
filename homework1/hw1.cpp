#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

bool compare(float main_x, float main_y, float x, float y)
{
    bool result = false;

    if (main_y*x < y*main_x)
    {
        result = true;
    }

    return result;
}

double dot_prod(float main_x,float main_y,float x, float y) // функция скалярного произведения
{
    return (main_x*x+main_y*y)/(sqrt(x*x+y*y)*sqrt(main_x*main_x+main_y*main_y));
}


float get_coords_x(ifstream &input_file) // функция получения координаты x
{
    float x;
    input_file >> x;
    return x;
}

float get_coords_y(ifstream &input_file)  // функция получения координаты y
{
    float y;
    input_file >> y;
    return y;
}


int main()
{
    float main_x;
    float main_y;
    double temp_dot_prod;
    double leftmost_x = 0;
    double leftmost_y = 0;
    double leftmost_cos = 2;
    double rightmost_x = 0;
    double rightmost_y = 0;
    double rightmost_cos = 2;
    float x;
    float y;

    string line;

    ifstream input_file("in1M.txt");

    main_x = get_coords_x(input_file);
    main_y = get_coords_y(input_file);



    while (getline(input_file, line))
    {
        x = get_coords_x(input_file);
        y = get_coords_y(input_file);
        temp_dot_prod = dot_prod(main_x, main_y, x, y);
        if (compare(main_x, main_y, x, y) && temp_dot_prod <= leftmost_cos)
        {

            leftmost_x = x;
            leftmost_y = y;
            leftmost_cos = temp_dot_prod;

        } else if (temp_dot_prod <= rightmost_cos)
        {
            rightmost_x = x;
            rightmost_y = y;
            rightmost_cos = temp_dot_prod;
        }
    }
    input_file.close();

    cout << "Leftmost: " << leftmost_x << ' ' << leftmost_y << endl;
    cout << "Rightmost: " << rightmost_x << ' ' << rightmost_y << endl;

    return 0;
}








