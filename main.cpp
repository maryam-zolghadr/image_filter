#include "read_input.hpp"
#include "apply_filter.hpp"

int main(int argc, char* argv[]) 
{
    Bmp bmp;
    create(bmp, 0, 0);
    vector<char> filters;
    vector<View> views;
    vector<Filter*> fs;
    handle_input(argc, argv, filters, views);
    for(int i = 0; i < filters.size(); i++)
    {
        switch(filters[i])
        {
            case 'G':
            {
                cout << "here" << endl;
                fs.push_back(new GrayScale());
                break;
            }
            case 'B':
            {
                fs.push_back(new Blur());
                break;
            }
            case 'S':
            {
                fs.push_back(new Sharpen());
                break;
            }
            case 'E':
            {                
                fs.push_back(new Emboss());
                break;
            }      
            case 'I':
            {
                fs.push_back(new Invert());
                break;
            }      
            default: 
                break;
        }
    }
    for(int i = 0; i < filters.size(); i++)
    {
        cout << filters[i] << " " << views[i].x << " " << views[i].y << " " << views[i].w << " " << views[i].h << endl;
    }
    read(bmp, "A6-Sample-Picture.bmp");
    bmp.data[56][12] = Pixel(255, 0, 0);
    int a = bmp.data[0][0].red ;
    //cout << a << " " << bmp.data[0][0].blu << " " << bmp.data[0][0].grn << endl;
    write(bmp, "test.bmp");
    handle_image_filter(fs, views, bmp);
    return 0;
}