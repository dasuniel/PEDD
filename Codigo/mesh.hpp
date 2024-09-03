#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <string>

struct Vertex {
    float x, y, z;
};

struct Face {
    std::vector<int> vertex_indices;
};

class Mesh {
public:
    std::string name;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    Mesh(const std::string& name);
    bool loadFromFile(const std::string& filename);
    void calculateBoundingBox(Vertex& min, Vertex& max) const;
    void saveToFile(const std::string& filename) const;
};

#endif // MESH_HPP
