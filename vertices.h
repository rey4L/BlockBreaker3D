#ifndef VERTICES_CLASS_H
#define VERTICES_CLASS_H

#define _USE_MATH_DEFINES
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

void generateSphere(float radius, unsigned int longitudeCount, unsigned int latitudeCount, std::vector<float>& vertices, std::vector<unsigned int>& indices);

namespace Vertices {
    extern GLfloat diagonal_pyramid_vertices[40];
    extern GLfloat pyramid_vertices[40];
    extern GLuint pyramid_indices[18];
    extern GLfloat house_vertices[200];
    extern GLuint house_indices[48];
    extern GLfloat efficient_cube_vertices[64];
    extern GLuint efficient_cube_indices[36];
    extern GLfloat square_cube_vertices[192];
    extern GLuint square_cube_indices[36];
    extern GLfloat cuboid_vertices[192];
}

#endif // !1