
#include <iostream>
#include <math.h>
#include <cstring>

#include "histogram.h"
#include "svg.h"


//���� �����

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


//���������� ���������� ����� � ������ �������

void make_histogram
(vector<double> numbers,double min,double max,
 vector<size_t>& bins,size_t number_count,size_t bin_count)
{
    size_t bin_index=0;


    for(double x:numbers)
    {
    if(x==max)
        {
        (bins[bin_count-1])++;
        continue;
        }

    //������ ������ ������� ��� ������� ����� � ������ min/max
    bin_index = floor((x - min) * bin_count / (max - min));
    (bins[bin_index])++;
    }


if(min==max)
    {
    bins.resize(1);
    bins[0]=number_count;
    }

}


//����� �����������

void show_histogram_svg
(const vector<size_t>& bins,size_t bin_count,
 const vector<string>& stroke,const vector<string>& fill )
{
//���������
const auto IMAGE_WIDTH = 800;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 50;


//�����������
//              ������������� svg
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

size_t max_count = 0;

    //���������� ������������� �������� �� ��������
for(size_t i=0;i<bin_count;i++)
{

    if (bins[i] > max_count)
        {
            max_count = bins[i];
        }
}


    double top = 0;


for (size_t i=0;i<bin_count;i++)
    {
    // ���� �������� � ������ ����������
    const size_t SCREEN_WIDTH = 800;
    const size_t MAX_in_BIN = SCREEN_WIDTH-TEXT_WIDTH;




    //�������� ������������� ���������������
    const bool scaling_needed = max_count > (size_t)floor(MAX_in_BIN/BLOCK_WIDTH);


    //���������������
    size_t height;

        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_in_BIN/BLOCK_WIDTH / max_count;

            height = (bins[i] * scaling_factor);
        }
        else
        {
            height = bins[i];
        }

    double bin_width = BLOCK_WIDTH * height;

    //�����������
    //              ����� ������
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));

    //�����������
    //              ����� ���������� ����������
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,stroke[i],fill[i]);
    top += BIN_HEIGHT;
    }

//�����������
//              ����� ������
    svg_end();


}



int main()
{
//���� �������� ������

size_t number_count;
cerr << "Enter number count: ";
cin >> number_count;


size_t bin_count;
cerr << "Enter bin count: ";
cin >> bin_count;

//���� �������� ������
//                        ���� �����
const auto numbers = input_numbers(number_count);


//���� �������� ������
//                        ���� ������
vector<string> stroke(bin_count,"red");
vector<string> fill(bin_count,"#ffeeee");


//��������� ������
vector<size_t> bins(bin_count, 0);


//��������� ������
//                  ���������� ������������, ������������� ��������
double min;
double max;

find_minmax(numbers,min,max);


//��������� ������
//                  ���������� ���������� ����� � ������ �������
make_histogram(numbers,min,max,bins,number_count,bin_count);

//��������� ������
//                  ����� �����������
show_histogram_svg(bins,bin_count,stroke,fill);


    return 0;
}
