#include "filter.hpp"
#include <iostream>
void Filter::set_view(View& view) {this ->view = view;};
View Filter::get_view(){return view;};
Pixel KernelFilter::apply_filter(const int& i,const int& j, const Bmp& bmp) 
{
    int kernel_size = 3;
    Pixel result_pixel;
    float sum_red = 0.0, sum_green = 0.0, sum_blue = 0.0;
    int count = 0;
    for (int row = -kernel_size / 2; row <= kernel_size / 2; ++row)
    {
        for (int col = -kernel_size / 2; col <= kernel_size / 2; ++col)
        {
            int neighbor_row = i + row;
            int neighbor_col = j + col;

            if (neighbor_row >= 0 && neighbor_row < bmp.infoHdr.height &&
                neighbor_col >= 0 && neighbor_col < bmp.infoHdr.width)
            {
                Pixel neighbor_pixel = bmp.data[neighbor_row][neighbor_col];
                float weight = kernel_matrix[row + kernel_size / 2][col + kernel_size / 2];
                sum_red += neighbor_pixel.red * weight;
                sum_green += neighbor_pixel.grn * weight;
                sum_blue += neighbor_pixel.blu * weight;
                count++;
            }
        }
    }
    if (sum_red > 255)
        sum_red = 255;
    else if (sum_red < 0)
        sum_red = 0;
    if (sum_blue > 255)
        sum_blue = 255;
    else if (sum_blue < 0)
        sum_blue = 0;
    if (sum_green > 255)
        sum_green = 255;
    else if (sum_green < 0)
        sum_green = 0;
    result_pixel.red = static_cast<int>(sum_red);
    result_pixel.grn = static_cast<int>(sum_green);
    result_pixel.blu = static_cast<int>(sum_blue);

    return result_pixel;
}
KernelFilter::KernelFilter() : Filter(){};
NoKernel::NoKernel() : Filter(){};
Blur::Blur() : KernelFilter() 
{
    kernel_matrix[0][0] = 1.0/16;
    kernel_matrix[0][1] = 2.0/16;
    kernel_matrix[0][2] = 1.0/16;
    kernel_matrix[1][0] = 2.0/16;
    kernel_matrix[1][1] = 4.0/16;
    kernel_matrix[1][2] = 2.0/16;
    kernel_matrix[2][0] = 1.0/16;
    kernel_matrix[2][1] = 2.0/16;
    kernel_matrix[2][2] = 1.0/16; 
}
Sharpen::Sharpen() : KernelFilter() 
{
    kernel_matrix[0][0] = 0;
    kernel_matrix[0][1] = -1;
    kernel_matrix[0][2] = 0;
    kernel_matrix[1][0] = -1;
    kernel_matrix[1][1] = 5;
    kernel_matrix[1][2] = -1;
    kernel_matrix[2][0] = 0;
    kernel_matrix[2][1] = -1;
    kernel_matrix[2][2] = 0; 
}
Emboss::Emboss() : KernelFilter() 
{ 
    kernel_matrix[0][0] = -2;
    kernel_matrix[0][1] = -1;
    kernel_matrix[0][2] = 0;
    kernel_matrix[1][0] = -1;
    kernel_matrix[1][1] = 1;
    kernel_matrix[1][2] = 1;
    kernel_matrix[2][0] = 0;
    kernel_matrix[2][1] = 1;
    kernel_matrix[2][2] = 2; 
}
GrayScale::GrayScale() : NoKernel(){};
Invert::Invert() : NoKernel(){};
Pixel GrayScale::apply_filter(const int& i, const int& j,const  Bmp& bmp)
{
    Pixel pixel = bmp.data[i][j];
        int average = (pixel.blu + pixel.red + pixel.grn) / 3;
        if (average > 255)
            average = 255;
        else if (average < 0)
            average = 0;
        pixel.red = average;
        pixel.grn = average;
        pixel.blu = average;
    return pixel;
}

Pixel Invert::apply_filter(const int& i, const int& j, const Bmp& bmp)
{
    Pixel result;
    Pixel pixel = bmp.data[i][j];
    int green = 255 - pixel.grn;
    int red = 255 - pixel.red;
    int blue = 255 - pixel.blu;
    if (red > 255)
        red = 255;
    else if (red < 0)
        red = 0;
    if (blue > 255)
        blue = 255;
    else if (blue < 0)
        blue = 0;
    if (green > 255)
        green = 255;
    else if (green < 0)
        green = 0;
    result.red = red;
    result.blu = blue;
    result.grn = green;
    return result;
}
