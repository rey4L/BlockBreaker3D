#ifndef IMPORTER_H
#define IMPORTER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

// Load a model from a file
bool loadModelFromFile(const std::string& filePath, std::vector<float>& vertices, std::vector<unsigned int>& indices);

// Process the nodes of the scene
void processNode(aiNode* node, const aiScene* scene, std::vector<float>& vertices, std::vector<unsigned int>& indices);

// Process a mesh
void processMesh(aiMesh* mesh, const aiScene* scene, std::vector<float>& vertices, std::vector<unsigned int>& indices);

#endif