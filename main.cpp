#include <iostream>

#include "color.h"
#include "vec3.h"


void render_helloworld(){
    // Image
    const int image_width = 256;
    const int image_height = 256;

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255" << std::endl;

    for(int j = image_height - 1; j >= 0; --j){
        std::cerr << "\rScanLines remaining: " << j << " " << std::flush;
        for(int i = 0; i < image_width; ++i){
            color pixel_color(double(i)/(image_width - 1), double(j)/(image_height - 1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone." << std::endl;
}

int main(int argc, char **argv){
    // Can swap between using custom color type
    // or Vector3d from Eigen library
    render_helloworld();
}
