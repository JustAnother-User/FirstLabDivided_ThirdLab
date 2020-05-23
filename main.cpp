#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
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


    //Задание варианта

   /* for(size_t i=0;i<number_count;i++)
    {   size_t deleted_count=0;
        for(size_t j=i+1;j<number_count;j++)
        {
            if(numbers[j]==numbers[i])
            {
            numbers.erase(numbers.begin()+i);
            deleted_count++;
            }
        }
        (number_count)-=deleted_count;
    }*/


    // Вычисление,обработка вторичных переменных(промежуточных)
vector<size_t> bins(bin_count, 0);


double min = numbers[0];
double max = numbers[0];
for (double x : numbers)
{
    if (x < min)
    {
        min = x;
    }
    else if (x > max)
    {
        max = x;
    }
}

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
    //Масштабирование

double max_count = bins[0];
for (double x : bins)
{
    if (x > max_count)
    {
        max_count = x;
    }
}

vector <size_t> height(bin_count,0);

for(size_t i=0;i<bin_count;i++){

height[i] = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);

}
    //Вывод

for(size_t i=0 ;i<bin_count;i++)
{
   // if(bins[i]<1000){ cout<<' ';
    if(bins[i]<100){
        cout<<' ';
        if(bins[i]<10){
            cout<<' ';
        }
    }
  //  }
    cout<<bins[i]<<'|';
    for(size_t j=0;j<height[i];j++)
    {
        cout<<'*';
    }
    if (height[i]<76)cout<<"\n";
}




    return 0;
}
