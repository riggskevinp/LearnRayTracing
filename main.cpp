#include <iostream>

#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"


constexpr color ray_color(const ray& r, const hittable& world, int depth){
    hit_record rec;

    if(depth <= 0){
        return color(0,0,0);
    }

    if(world.hit(r, 0.001, infinity, rec)){
        point3 target = rec.p + rec.normal + random_in_hemisphere(rec.normal);
        //point3 target = rec.p + rec.normal + random_unit_vector();
        //point3 target = rec.p + rec.normal + random_in_unit_sphere();
        //return 0.5 * (rec.normal + color(1,1,1));
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
    }
    vector3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

struct Image {
    static constexpr auto const aspect_ratio = 16.0 / 9.0;
    static constexpr auto const width = 400;
    static constexpr auto const height = static_cast<int>(width / aspect_ratio);
    static constexpr auto const samples_per_pixel = 100;
    static constexpr auto const max_depth = 50;
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
    Camera cam;

    // Render
    std::cout << "P3\n" << img.width << " " << img.height << "\n255" << std::endl;

    for(int j = img.height - 1; j >= 0; --j){
        std::cerr << "\rScanLines remaining: " << j << " " << std::flush;
        for(int i = 0; i < img.width; ++i){
            color pixel_color(0,0,0);
            for(int s = 0; s < img.samples_per_pixel; ++s){
                auto u = (i + random_double()) / (img.width-1);
                auto v = (j + random_double()) / (img.height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, img.max_depth);
            }
            write_color(std::cout, pixel_color, img.samples_per_pixel);
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
