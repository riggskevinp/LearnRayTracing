#include <iostream>

#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"


constexpr color ray_color(const ray& r, const hittable& world){
    hit_record rec;
    if(world.hit(r, 0, infinity, rec)){
        return 0.5 * (rec.normal + color(1,1,1));
    }
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
    constexpr explicit Camera(const Image& img):
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

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

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
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone." << std::endl;
}

int main(int argc, char **argv){
    // silence unused warnings
    (void)argc;
    (void)argv;
    // Can swap between using custom color type
    // or Vector3d from Eigen library inside vec3.h
    render_helloworld();
}
