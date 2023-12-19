#include "apply_filter.hpp"

void handle_image_filter(vector<Filter*>& fs, vector<View>& views, Bmp& bmp, const string& output_name)
{
    Bmp tmp_bmp = bmp;
    for (int i = 0; i < fs.size(); i++) 
    {
        fs[i]->set_view(views[i]);
        const View& view = fs[i]->get_view();
        int startRow = view.x;
        int endRow = view.x + view.w;
        int startCol = view.y;
        int endCol = view.y + view.h;
        if (view.w == 0 && view.h == 0)
        {
            startRow = 0;
            endRow = bmp.infoHdr.height;
            startCol = 0;
            endCol = bmp.infoHdr.width;
        }

        for (int row = startRow; row < endRow; row++) 
        {
            for (int col = startCol; col < endCol; col++) 
            {
                Pixel pixel_tmp = fs[i]->apply_filter(row, col, bmp);
                tmp_bmp.data[row][col] = pixel_tmp;
            }
        }
        bmp = tmp_bmp;
    }
    write(tmp_bmp, output_name);
    delete tmp_bmp.fileData;
}