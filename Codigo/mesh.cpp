#include "mesh.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Mesh::Mesh(const std::string& name) : name(name) {}

bool Mesh::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "El archivo " << filename << " no existe o es ilegible.\n";
        return false;
    }

    file >> name;

    int num_vertices;
    file >> num_vertices;

    vertices.resize(num_vertices);
    for (int i = 0; i < num_vertices; ++i) {
        file >> vertices[i].x >> vertices[i].y >> vertices[i].z;
    }

    int num_faces;
    file >> num_faces;

    faces.resize(num_faces);
    for (int i = 0; i < num_faces; ++i) {
        int num_indices;
        file >> num_indices;
        faces[i].vertex_indices.resize(num_indices);
        for (int j = 0; j < num_indices; ++j) {
            file >> faces[i].vertex_indices[j];
        }
    }

    return true;
}

void Mesh::calculateBoundingBox(Vertex& min, Vertex& max) const {
    if (vertices.empty()) return;

    min = max = vertices[0];
    for (const auto& v : vertices) {
        if (v.x < min.x) min.x = v.x;
        if (v.y < min.y) min.y = v.y;
        if (v.z < min.z) min.z = v.z;
        if (v.x > max.x) max.x = v.x;
        if (v.y > max.y) max.y = v.y;
        if (v.z > max.z) max.z = v.z;
    }
}

void Mesh::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    file << name << "\n";
    file << vertices.size() << "\n";
    for (const auto& v : vertices) {
        file << v.x << " " << v.y << " " << v.z << "\n";
    }
    for (const auto& f : faces) {
        file << f.vertex_indices.size() << " ";
        for (const auto& idx : f.vertex_indices) {
            file << idx << " ";
        }
        file << "\n";
    }
    file << "-1\n";
}
