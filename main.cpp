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
    static constexpr auto const aspect_ratio = 3.0 / 2.0;
    static constexpr auto const width = 1200;
    static constexpr auto const height = static_cast<int>(width / aspect_ratio);
    static constexpr auto const samples_per_pixel = 500;
    static constexpr auto const max_depth = 50;
    static constexpr auto const look_from = point3{13,2,3};
    static constexpr auto const look_at = point3{0,0,0};
    static constexpr auto const vup = vector3{0,1,0};
    static constexpr auto const dist_to_focus = 10.0;
    static constexpr auto const aperture = 0.1;
    static constexpr auto const vertical_fov = 20.0;
};

hittable_list random_scene(){
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5,0.5,0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for(int a = -11; a < 11; a++){
        for(int b = -11; b < 11; b++){
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if((center - point3(4, 0.2, 0)).length() > 0.9){
                shared_ptr<material> sphere_material;

                if(choose_mat < 0.8){
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if(choose_mat < 0.95){
                    // metal
                    auto albedo = color::random(0.5,1);
                    auto fuzz = random_double(0,0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else{
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0,1,0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4,0.2,0.1));
    world.add(make_shared<sphere>(point3(-4,1,0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7,0.6,0.5), 0.0);
    world.add(make_shared<sphere>(point3(4,1,0), 1.0, material3));

    return world;
}

void render_helloworld(){
    /*
     * Creates a simple gradient image
     * Format is ppm
     */
    // Image
    const Image img;

    // World
    hittable_list world = random_scene();

    // Camera
    Camera cam(img.look_from, img.look_at, img.vup, img.vertical_fov, img.aspect_ratio, img.aperture, img.dist_to_focus);

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
