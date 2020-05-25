#include <iostream>
#include <math.h>
#include <ctime>
#include "histogram.h"
#include "svg.h"

vector<double> input_numbers
(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

void input_colors(vector<string>& stroke,vector<string>& fill,size_t bin_count)
{
    for (string x: stroke)
    {
    string current_color;
    cerr<<"enter stroke color:";
    cin>>current_color;

    }
}


void make_histogram(vector<double> numbers,double min,double max,
                    vector<size_t>& bins,
                    size_t number_count,size_t bin_count)
{
    size_t bin_index=0;


    for(double x:numbers)
    {
    if(x==max)
        {
        (bins[bin_count-1])++;
        continue;
        }

    bin_index = floor((x - min) * bin_count / (max - min));
    (bins[bin_index])++;
    }


if(min==max)
    {
    bins.resize(1);
    bins[0]=number_count;
    }

}


void
show_histogram_svg(const vector<size_t>& bins,size_t bin_count,const vector<string>& stroke,const vector<string>& fill )
{

const auto IMAGE_WIDTH = 400;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 50;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);


    double top = 0;
for (size_t i=0;i<bin_count;i++)
    {

    const size_t SCREEN_WIDTH = 400;
    const size_t MAX_in_BIN = SCREEN_WIDTH-TEXT_WIDTH;

    size_t max_count = 0;

        if (bins[i] > max_count)
        {
            max_count = bins[i];
        }

    const bool scaling_needed = max_count > (size_t)floor(MAX_in_BIN/BLOCK_WIDTH);

    size_t height = bins[i];
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_in_BIN/BLOCK_WIDTH / max_count;
            height = (size_t)(bins[i] * scaling_factor);
        }

    double bin_width = BLOCK_WIDTH * height;

    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,stroke[i],fill[i]);
    top += BIN_HEIGHT;
    }


    svg_end();


}



int main()
{
    srand(time(0));
    // Ввод,объявление первичных переменных(вводных)
size_t number_count;
cerr << "Enter number count: ";
cin >> number_count;


size_t bin_count;
cerr << "Enter bin count: ";
cin >> bin_count;


const auto numbers = input_numbers(number_count);


vector<string> stroke(bin_count,"red");
vector<string> fill(bin_count,"#ffeeee");

input_colors(stroke,fill,bin_count);

    // Вычисление,обработка вторичных переменных(промежуточных)
vector<size_t> bins(bin_count, 0);


double min;
double max;
find_minmax(numbers,min,max);


make_histogram(numbers,min,max,bins,number_count,bin_count);


show_histogram_svg(bins,bin_count,stroke,fill);


    return 0;
}
