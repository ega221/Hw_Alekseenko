#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

bool compare(int main_x, int main_y, int x, int y)
{
    bool result = false;
    if (main_x != 0)
    {
        if (main_y/main_x*x > y)
        {
            result = true;
        }
    } else
    {
        if (x < 0)
        {
            result = true;
        }
    }
    return result;
}

double dot_prod(int main_x,int main_y,int x, int y) // функция скалярного произведения
{
    return (main_x*main_x + main_y*y)/(sqrt(pow(x,2)+pow(y, 2))*sqrt(pow(main_x,2)+pow(main_y,2)));
}


int get_coords_x(ifstream &input_file) // функция получения координаты x
{
    string coord1;
    int x;
    input_file >> coord1;
    x = stoi(coord1);
    return x;
}

int get_coords_y(ifstream &input_file)  // функция получения координаты y
{
    string coord2;
    int y;
    input_file >> ws >> coord2;
    y = stoi(coord2);
    return y;
}


int main()
{
    int main_x;
    int main_y;
    double temp_dot_prod;
    double leftmost_x = 0;
    double leftmost_y = 0;
    double leftmost_cos = 2;
    double rightmost_x = 0;
    double rightmost_y = 0;
    double rightmost_cos = 2;
    int x;
    int y;

    string line;

    ifstream input_file("in.txt");
    ofstream output_file("result.txt");

    main_x  = get_coords_x(input_file);
    main_y  = get_coords_y(input_file);


    while (getline(input_file, line))
    {
        x = get_coords_x(input_file);
        y = get_coords_y(input_file);
        temp_dot_prod = dot_prod(main_x, main_y, x, y);
        if (compare(main_x, main_y, x, y))
        {
            if ( temp_dot_prod < leftmost_cos)
            {
                leftmost_x = x;
                leftmost_y = y;
                leftmost_cos = temp_dot_prod;
            }
        } else if (temp_dot_prod < rightmost_cos)
        {
            rightmost_x = x;
            rightmost_y = y;
            rightmost_cos = temp_dot_prod;
        }
    }

    output_file << "Leftmost: " << leftmost_x << ' ' << leftmost_y << endl;
    output_file << "Rightmost: " << rightmost_x << ' ' << rightmost_y << endl;

    return 0;
}








