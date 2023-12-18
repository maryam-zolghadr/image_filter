#include "filter.hpp"

Bmp Filter::get_bmp() {return bmp;};
void Filter::set_view(View& view) {this ->view = view;};
void Filter::set_bmp(const Bmp& bmp) { this -> bmp = bmp;};
void KernelFilter::set_filter_kernel(const float filter_kernel[3][3]) 
{
    for(int i = 0; i < 3; i++) 
    {
        for(int j = 0; j < 3; j++) 
        {
            this->filter_kernel[i][j] = filter_kernel[i][j];
        }
    }
}
Pixel KernelFilter::apply_filter(const int& i,const int& j) 
{
    int kernel_size = 3;
    Bmp original_bmp = get_bmp();
    Pixel result_pixel;

    float sum_red = 0.0, sum_green = 0.0, sum_blue = 0.0;
    int count = 0;
    for (int row = -kernel_size / 2; row <= kernel_size / 2; ++row)
    {
        for (int col = -kernel_size / 2; col <= kernel_size / 2; ++col)
        {
            int neighbor_row = i + row;
            int neighbor_col = j + col;

            if (neighbor_row >= 0 && neighbor_row < original_bmp.infoHdr.height &&
                neighbor_col >= 0 && neighbor_col < original_bmp.infoHdr.width)
            {
                Pixel neighborPixel = original_bmp.data[neighbor_row][neighbor_col];
                float weight = get_matrix()[row + kernel_size / 2][col + kernel_size / 2];
                sum_red += neighborPixel.red * weight;
                sum_green += neighborPixel.grn * weight;
                sum_blue += neighborPixel.blu * weight;
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
Blur::Blur() : KernelFilter() {set_filter_kernel(kernel_matrix);}
Sharpen::Sharpen() : KernelFilter() {set_filter_kernel(kernel_matrix);}
Emboss::Emboss() : KernelFilter() {set_filter_kernel(kernel_matrix);}
Pixel GrayScale::apply_filter(const int& i, const int& j)
{
    Pixel pixel;
    if (i >= 0 && i < get_bmp().infoHdr.height && j >= 0 && j < get_bmp().infoHdr.width)
    {
        pixel = get_bmp().data[i][j];
        int average = (pixel.blu + pixel.red + pixel.grn) / 3;
        if (average > 255)
            average = 255;
        else if (average < 0)
            average = 0;
        pixel.red = average;
        pixel.grn = average;
        pixel.blu = average;
    }
    return pixel;
}
Pixel Invert::apply_filter(const int& i,const int& j)
{
    Pixel& pixel = get_bmp().data[i][j];
    Pixel result;
    
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