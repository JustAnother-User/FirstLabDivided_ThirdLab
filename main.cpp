
#include <iostream>
#include <math.h>
#include <cstring>

#include "histogram.h"
#include "colors.h"
#include "svg.h"


//Ввод чисел

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


//Нахождение количества чисел в каждой корзине

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

    //Расчёт номера корзины для каждого числа с учетом min/max
    bin_index = floor((x - min) * bin_count / (max - min));
    (bins[bin_index])++;
    }


if(min==max)
    {
    bins.resize(1);
    bins[0]=number_count;
    }

}


//Вывод гистограммы

void show_histogram_svg
(const vector<size_t>& bins,size_t bin_count,
 const vector<string>& stroke,const vector<string>& fill )
{
//Константы
const auto IMAGE_WIDTH = 800;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 5;


//Гистограмма
//              Инициализация svg
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);


    double top = 0;
for (size_t i=0;i<bin_count;i++)
    {
    // Ввод констант и нужных переменных
    const size_t SCREEN_WIDTH = 800;
    const size_t MAX_in_BIN = SCREEN_WIDTH-TEXT_WIDTH;

    size_t max_count = 0;

    //Нахождение максимального значения по корзинам
        if (bins[i] > max_count)
        {
            max_count = bins[i];
        }

    //Проверка необходимости масштабирования
    const bool scaling_needed = max_count > (size_t)floor(MAX_in_BIN/BLOCK_WIDTH);


    //Масштабирование
    size_t height = bins[i];
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_in_BIN/BLOCK_WIDTH / max_count;
            height = (size_t)(bins[i] * scaling_factor);
        }

    double bin_width = BLOCK_WIDTH * height;

    //Гистограмма
    //              Вывод текста
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));

    //Гистограмма
    //              Вывод собственно гистограмм
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,stroke[i],fill[i]);
    top += BIN_HEIGHT;
    }

//Гистограмма
//              Конец вывода
    svg_end();


}



int main()
{
//Ввод исходных данных

size_t number_count;
cerr << "Enter number count: ";
cin >> number_count;


size_t bin_count;
cerr << "Enter bin count: ";
cin >> bin_count;

//Ввод исходных данных
//                        Ввод чисел
const auto numbers = input_numbers(number_count);


//Ввод исходных данных
//                        Ввод цветов
vector<string> stroke(bin_count,"red");
vector<string> fill(bin_count,"#ffeeee");

input_colors(stroke,fill,bin_count);



//Обработка данных
vector<size_t> bins(bin_count, 0);


//Обработка данных
//                  Нахождение минимального, максимального значений
double min;
double max;

find_minmax(numbers,min,max);


//Обработка данных
//                  Нахождение количества чисел в каждой корзине
make_histogram(numbers,min,max,bins,number_count,bin_count);

//Обработка данных
//                  Вывод гистограммы
show_histogram_svg(bins,bin_count,stroke,fill);


    return 0;
}
