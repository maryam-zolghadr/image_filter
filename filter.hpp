#include "bmp.hpp"
#ifndef FILTER_H
#define FILTER_H
struct View 
{
    int x;
    int y;
    int w;
    int h;
};
class Filter
{
public:
    void set_view(View& view);
    View get_view();
    virtual Pixel apply_filter(const int& i,const int& j,  const Bmp& bmp) = 0;
private:
    View view;
};

class NoKernel : public Filter
{
public:
    NoKernel();
    float kernel_matrix[3][3];
};

class KernelFilter : public Filter
{
public:
    KernelFilter();
    float kernel_matrix[3][3];
    Pixel apply_filter(const int& i,const int& j,  const Bmp& bmp) override;
private:
};

class Blur : public KernelFilter
{
public:
    Blur();
private:

};

class Sharpen : public KernelFilter
{
public:
    Sharpen();
private:

};

class Emboss : public KernelFilter
{
public:
    Emboss();
private:
};

class Invert : public NoKernel
{
public:
    Invert();
    Pixel apply_filter(const int& i,const int& j,  const Bmp& bmp) override;
private:

};

class GrayScale : public NoKernel
{
public:
    GrayScale();
    Pixel apply_filter(const int& i,const int& j, const Bmp& bmp) override;
};

#endif