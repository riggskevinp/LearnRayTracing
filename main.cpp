#include <iostream>

#include "rtweekend.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"


color ray_color(const ray& r, const hittable& world, int depth){
    hit_record rec;

    if(depth <= 0){
        return {0,0,0};
    }

    if(world.hit(r, 0.001, infinity, rec)){
        ray scattered;
        color attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation * ray_color(scattered, world, depth-1);
        }
        return {0,0,0};
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

    auto material_ground = make_shared<lambertian>(color(0.8,0.8,0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color(0.8,0.6,0.2), 0.0);

    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    // trick for hollow spheres: negative radius doesn't affect geometry but the surface normal points outward
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));


    // Camera
    Camera cam(point3(-2,2,1), point3(0,0,-1), vector3(0,1,0), 20, img.aspect_ratio);

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
