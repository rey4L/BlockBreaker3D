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

//The commented out code in the following functions are responsible 
// for changing the orientation of the cylinder

void generateCylinderVertices(std::vector<GLfloat>& vertices, float radius, float length) {
    const float half_length = length / 2;

    for (int i = 0; i <= segments; ++i) {
        float angle = i * (2 * M_PI / segments);
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        // Top face
        /*vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(half_length);*/
        vertices.push_back(half_length);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.83f);
        vertices.push_back(0.70f);
        vertices.push_back(0.44f);
        vertices.push_back(static_cast<float>(i) / segments);
        vertices.push_back(0.0f);

        // Bottom face
        /*vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(-half_length);*/
        vertices.push_back(-half_length);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.83f);
        vertices.push_back(0.70f);
        vertices.push_back(0.44f);
        vertices.push_back(static_cast<float>(i) / segments);
        vertices.push_back(1.0f);
    }
}

void generateSphereVertices(std::vector<GLfloat>& vertices, float radius, float length) {
    const float half_length = length / 2;

    for (int i = 0; i <= segments / 2; ++i) {
        float v = i * (M_PI / segments);
        float y = cos(v) * radius;
        float slice_radius = sin(v) * radius;

        for (int j = 0; j <= segments; ++j) {
            float u = j * (2 * M_PI / segments);
            float x = cos(u) * slice_radius;
            float z = sin(u) * slice_radius;

            // Top half-sphere
            /*vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z + half_length);*/
            vertices.push_back(half_length);
            vertices.push_back(x);
            vertices.push_back(z);
            vertices.push_back(0.83f);
            vertices.push_back(0.70f);
            vertices.push_back(0.44f);
            vertices.push_back(static_cast<float>(j) / segments);
            vertices.push_back(static_cast<float>(i) / (segments / 2));

            // Bottom half-sphere
            /*vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z - half_length);*/
            vertices.push_back(-half_length);
            vertices.push_back(x);
            vertices.push_back(z);
            vertices.push_back(0.83f);
            vertices.push_back(0.70f);
            vertices.push_back(0.44f);
            vertices.push_back(static_cast<float>(j) / segments);
            vertices.push_back(1.0f - static_cast<float>(i) / (segments / 2));
        }
    }
}

void generateCylinderIndices(std::vector<GLuint>& indices) {
    for (int i = 0; i < segments; ++i) {
        indices.push_back(i * 2);
        indices.push_back(i * 2 + 1);
        indices.push_back((i + 1) * 2 + 1);

        indices.push_back(i * 2);
        indices.push_back((i + 1) * 2 + 1);
        indices.push_back((i + 1) * 2);
    }

    // Connect the last vertex to the first vertex to close the seam
    indices.push_back(segments * 2);
    indices.push_back(segments * 2 + 1);
    indices.push_back(1);

    indices.push_back(segments * 2);
    indices.push_back(1);
    indices.push_back(0);
}

void generateSphereIndices(std::vector<GLuint>& indices) {
    int base_index = segments * 2 + 2;
    for (int i = 0; i < segments / 2; ++i) {
        for (int j = 0; j < segments; ++j) {
            int next_i = (i + 1) % (segments / 2 + 1);
            int next_j = (j + 1) % (segments + 1);

            // Top half-sphere
            indices.push_back(base_index + i * (segments + 1) + j);
            indices.push_back(base_index + next_i * (segments + 1) + j);
            indices.push_back(base_index + next_i * (segments + 1) + next_j);

            indices.push_back(base_index + i * (segments + 1) + j);
            indices.push_back(base_index + next_i * (segments + 1) + next_j);
            indices.push_back(base_index + i * (segments + 1) + next_j);

            // Bottom half-sphere
            int bottom_offset = (segments / 2 + 1) * (segments + 1);
            indices.push_back(base_index + bottom_offset + i * (segments + 1) + j);
            indices.push_back(base_index + bottom_offset + i * (segments + 1) + next_j);
            indices.push_back(base_index + bottom_offset + next_i * (segments + 1) + next_j);

            indices.push_back(base_index + bottom_offset + i * (segments + 1) + j);
            indices.push_back(base_index + bottom_offset + next_i * (segments + 1) + next_j);
            indices.push_back(base_index + bottom_offset + next_i * (segments + 1) + j);
        }
    }
}

void generatePillVertices(std::vector<GLfloat>& vertices, float radius, float length) {
    generateCylinderVertices(vertices, radius, length);
    generateSphereVertices(vertices, radius, length);
}

void generatePillIndices(std::vector<GLuint>& indices) {
    generateCylinderIndices(indices);
    generateSphereIndices(indices);
}

namespace Vertices {

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

    GLfloat paddle_vertices[192] = {
        // Top face
        -1.0f, (0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -1.0f, -(0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        1.0f,  -(0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f,(0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Front face
        -1.0f, (0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -1.0f, (0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        1.0f, (0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f, (0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Left face
        1.0f, (0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        1.0f, (0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        1.0f,-(0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f,-(0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Back face
        1.0f, -(0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
        -1.0f, -(0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        -1.0f, -(0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f, -(0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,

        // Right face
        -1.0f, -(0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
        -1.0f, -(0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        -1.0f, (0.2f) / 2, 0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        -1.0f,(0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,

        // Bottom face
        -1.0f, (0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 1.0f,
        -1.0f, -(0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 1.0f,
        1.0f, -(0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 1.0f, 0.0f,
        1.0f,(0.2f) / 2, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
    };
}