//
// Created by kr63454 on 5/6/2022.
//

#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include "vec3.h"

#include <iostream>

template<typename vec_type>
inline void write_color(std::ostream &out, vec_type pixel_color) {
    // Write the translated [0, 255] value of each color component
    out << static_cast<int>(255.999 * pixel_color.x()) << " "
    << static_cast<int>(255.999 * pixel_color.y()) << " "
    << static_cast<int>(255.999 * pixel_color.z()) << "\n";
}

#endif //RAYTRACING_COLOR_H
