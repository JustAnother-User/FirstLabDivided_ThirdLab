#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>

using namespace std;

void svg_begin (double width, double height);
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height,
        string stroke = "black", string fill = "black");
void svg_end();

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


void find_minmax
(vector<double> numbers, double& min, double& max)
{
    min = numbers[0];
    max = numbers[0];
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


void show_histogram_text(vector <size_t> bins)
{

    //Масштабирование
const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

    size_t max_count = 0;

    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }

}


void
show_histogram_svg(const vector<size_t>& bins) {

const auto IMAGE_WIDTH = 400;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);


    double top = 0;
for (size_t bin : bins) {
    const double bin_width = BLOCK_WIDTH * bin;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"red","#ffeeee");
    top += BIN_HEIGHT;
}


    svg_end();


}


void svg_begin
(double width, double height) {

    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}


void svg_text
(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>"<<text<<"</text>";}



void svg_rect(double x, double y, double width, double height,
        string stroke , string fill)
{
    cout<< "<rect x = '"<<x<<"' y = '"<<y<<"' width= '"<<width<<"' height= '"<<height<<"' stroke= '"<<stroke<<"' fill= '"<<fill<<"'/> ";
}


void svg_end() {
    cout << "</svg>\n";
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


    // Вычисление,обработка вторичных переменных(промежуточных)
vector<size_t> bins(bin_count, 0);


double min;
double max;
find_minmax(numbers,min,max);


make_histogram(numbers,min,max,bins,number_count,bin_count);


show_histogram_svg(bins);


    return 0;
}
