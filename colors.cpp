#include "colors.h"


void input_colors(vector<string>& stroke,vector<string>& fill,size_t bin_count)
{
    for (size_t i=0;i<bin_count;i++)
    {
    string current_stroke;
    cerr<<"enter stroke color:";
    cin>>current_stroke;
    if(current_stroke[0]=='#')
        {
            stroke[i]=current_stroke;
        }
    string current_fill;
    cerr<<"enter stroke color:";
    cin>>current_fill;
    if(current_fill[0]=='#')
        {
            fill[i]=current_fill;
        }
    }
}
