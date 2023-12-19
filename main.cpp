#include "read_input.hpp"
#include "apply_filter.hpp"

int main(int argc, char* argv[]) 
{
    Bmp bmp;
    create(bmp, 0, 0);
    vector<char> filters;
    vector<View> views;
    vector<Filter*> fs;
    string input_name, output_name;
    cin >> input_name >> output_name;
    handle_input(argc, argv, filters, views);

    for(int i = 0; i < filters.size(); i++)
    {
        switch(filters[i])
        {
            case 'G':
            {
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

    read(bmp, input_name);
    handle_image_filter(fs, views, bmp, output_name);
    return 0;
}