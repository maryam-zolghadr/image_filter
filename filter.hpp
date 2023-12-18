#include "bmp.hpp"

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
    Bmp get_bmp() {};
    void set_view(View& view) {};
    View get_view() {};
    void set_bmp(const Bmp& bmp) {};
    virtual Pixel apply_filter(const int& i,const int& j) = 0;
private:
    View view;
    Bmp bmp;
};

class NoKernel : public Filter
{
public:
    NoKernel() : Filter() {};
};

class KernelFilter : public Filter
{
public:
    KernelFilter() : Filter() {};
    void set_filter_kernel(const float filter_kernel[3][3]) {};
    float (*get_matrix())[3] {return filter_kernel;};
    Pixel apply_filter(const int& i,const int& j) override{};
private:
    float filter_kernel[3][3];
};

class Blur : public KernelFilter
{
public:
    Blur() : KernelFilter() {};
private:
    float kernel_matrix[3][3] = 
    {
        {1.0/16, 2.0/16, 1.0/16},
        {2.0/16, 4.0/16, 2.0/16},
        {1.0/16, 2.0/16, 1.0/16}
    };
};

class Sharpen : public KernelFilter
{
public:
    Sharpen() : KernelFilter() {};
private:
    float kernel_matrix[3][3] = 
    {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };
};

class Emboss : public KernelFilter
{
public:
    Emboss() : KernelFilter() {};
private:
    float kernel_matrix[3][3] = 
    {
        {-2, -1, 0},
        {-1, 1, 1},
        {0, 1, 2}
    };
};

class Invert : public NoKernel
{
public:
    Invert() : NoKernel() {}
    Pixel apply_filter(const int& i,const int& j) override;
private:

};

class GrayScale : public NoKernel
{
public:
    GrayScale() : NoKernel() {}
    Pixel apply_filter(const int& i, const int& j) override;
};

