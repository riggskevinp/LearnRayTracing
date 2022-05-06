#include <iostream>

#include "color.h"
#include "vec3.h"
#include "ray.h"

color ray_color(const ray& r){
    vector3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

struct Image {
    static constexpr auto const aspect_ratio = 16.0 / 9.0;
    static constexpr auto const width = 400;
    static constexpr auto const height = static_cast<int>(width / aspect_ratio);
};

struct Camera {
    constexpr Camera(const Image& img):
    viewport_height(2.0),
    viewport_width(img.aspect_ratio * viewport_height),
    focal_length(1.0),
    origin(0, 0, 0),
    horizontal(viewport_width, 0, 0),
    vertical(0, viewport_height, 0),
    lower_left_corner(origin - horizontal/2 - vertical/2 - vector3(0, 0, focal_length))
    {
    }
    const double viewport_height;
    const double viewport_width;
    const double focal_length;

    const point3 origin;
    const vector3 horizontal;
    const vector3 vertical;
    const point3 lower_left_corner;
};

void render_helloworld(){
    /*
     * Creates a simple gradient image
     * Format is ppm
     */
    // Image
    const Image img;
    //const auto aspect_ratio = 16.0 / 9.0;
    //const int image_width = 400;
    //const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    const Camera cam = Camera(img);

    // Render
    std::cout << "P3\n" << img.width << " " << img.height << "\n255" << std::endl;

    for(int j = img.height - 1; j >= 0; --j){
        std::cerr << "\rScanLines remaining: " << j << " " << std::flush;
        for(int i = 0; i < img.width; ++i){
            auto u = double(i) / (img.width-1);
            auto v = double(j) / (img.height-1);
            ray r(cam.origin, cam.lower_left_corner + u*cam.horizontal + v*cam.vertical - cam.origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone." << std::endl;
}

int main(int argc, char **argv){
    // Can swap between using custom color type
    // or Vector3d from Eigen library inside vec3.h
    render_helloworld();
}
