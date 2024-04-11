#include"vertices.h"

// Function to generate sphere vertices and indices
void generateSphere(float radius, unsigned int longitudeCount, unsigned int latitudeCount,
    std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    vertices.clear();
    indices.clear();

    // Generate vertices
    for (unsigned int lat = 0; lat <= latitudeCount; ++lat) {
        float theta = lat * M_PI / latitudeCount;
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);

        for (unsigned int lon = 0; lon <= longitudeCount; ++lon) {
            float phi = lon * 2 * M_PI / longitudeCount;
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;
            float u = 1.0f - (float(lon) / longitudeCount);
            float v = 1.0f - (float(lat) / latitudeCount);
            //float v = -(theta / M_PI);

            if (lon == longitudeCount) {
                u = 0.0f;
            }

            vertices.push_back(x * radius);
            vertices.push_back(y * radius);
            vertices.push_back(z * radius);
            vertices.push_back(u);
            vertices.push_back(v);
        }
    }

    // Generate indices
    for (unsigned int lat = 0; lat < latitudeCount; ++lat) {
        for (unsigned int lon = 0; lon < longitudeCount; ++lon) {
            unsigned int first = (lat * (longitudeCount + 1)) + lon;
            unsigned int second = first + longitudeCount + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
}

namespace Vertices {
    //Pyramid (diagnoal texture map)
    GLfloat diagonal_pyramid_vertices[40] =
    {
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
         0.0f, 0.9f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
    };

    // Pyramid (quad texture map)
    GLfloat pyramid_vertices[40] =
    {
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 1.0f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
         0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 1.0f,
         0.0f, 0.9f,  0.0f,     0.92f, 0.86f, 0.76f,	0.5f, 0.5f
    };
    //
    // Pyramid indices
    GLuint pyramid_indices[18] =
    {
        0, 1, 2,  // First triangle of the base
        2, 3, 0,  // Second triangle of the base
        0, 1, 4,  // Triangle connecting to the top vertex
        1, 2, 4,  // Triangle connecting to the top vertex
        2, 3, 4,  // Triangle connecting to the top vertex
        3, 0, 4   // Triangle connecting to the top vertex
    };

    GLfloat house_vertices[200] = {
        // Front face
        -0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Right face
         0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

         // Top face
         -0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
          0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
          0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,

         // Bottom face
         -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
          0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
          0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,

         // Pyramid apex
         0.0f,  1.0f,  0.0f,  0.92f, 0.86f, 0.76f,  0.5f, 0.5f
    };

    GLuint house_indices[48] = {
        // Cube
        // Front face
        0, 1, 2,
        0, 2, 3,
        // Back face
        4, 5, 6,
        4, 6, 7,
        // Left face
        8, 9, 10,
        8, 10, 11,
        // Right face
        12, 13, 14,
        12, 14, 15,
        // Top face
        16, 17, 18,
        16, 18, 19,
        // Bottom face
        20, 21, 22,
        20, 22, 23,

        // Pyramid face 1 
        16, 17, 24,
        // Pyramid face 2 
        17, 18, 24,
        // Pyramid face 3 
        18, 19, 24,
        // Pyramid face 4 
        19, 16, 24
    };


    // Efficient vertices
    GLfloat efficient_cube_vertices[64] = {
        // Front face
        -0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f
    };

    // Efficient indices
    GLuint efficient_cube_indices[36]{
        0,1,2,2,3,0,
        4,5,1,1,0,4,
        7,3,0,0,4,7,
        6,2,3,3,7,6,
        5,1,2,2,6,5,
        6,7,4,4,5,6
    };


    GLfloat square_cube_vertices[192] = {
        // Front face
        -0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Right face
         0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

         // Top face
         -0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
          0.5f,  0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
          0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,

         // Bottom face
         -0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
          0.5f, -0.5f, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
          0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f
    };

    GLuint square_cube_indices[36] = {
         0,  1,  2,  2,  3,  0,  // Front face
         4,  5,  6,  6,  7,  4,  // Back face
         8,  9, 10, 10, 11,  8,  // Left face
        12, 13, 14, 14, 15, 12,  // Right face
        16, 17, 18, 18, 19, 16,  // Top face
        20, 21, 22, 22, 23, 20   // Bottom face
    };

    // Cuboid
    GLfloat cuboid_vertices[192] = {
        // Top face
        -1.0f, (0.5f) / 2,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -1.0f, -(0.5f) / 2,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        1.0f, -(0.5f) / 2,  0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f, (0.5f) / 2,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Front face
        -1.0f, (0.5f) / 2,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -1.0f, (0.5f) / 2,  -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        1.0f, (0.5f) / 2,  -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f, (0.5f) / 2,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Left face
        1.0f, (0.5f) / 2,  0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        1.0f, (0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        1.0f, -(0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f, -(0.5f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Back face
        1.0f, -(0.5f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -1.0f, -(0.5f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        -1.0f, -(0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f, -(0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Right face
        -1.0f, -(0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
        -1.0f, -(0.5f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        -1.0f, (0.5f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        -1.0f, (0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,

        // Bottom face
        -1.0f, (0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
        -1.0f, -(0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f, -(0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        1.0f, (0.5f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
    };
}