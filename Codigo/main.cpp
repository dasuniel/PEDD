#include <iostream>
#include <string>
#include <map>
#include "mesh.hpp"

std::map<std::string, Mesh> memoria;

void cargarArchivo(const std::string& nombre_archivo) {
    Mesh mesh(nombre_archivo);
    if (mesh.loadFromFile(nombre_archivo)) {
        memoria[nombre_archivo] = mesh;
        std::cout << "El objeto " << nombre_archivo << " ha sido cargado exitosamente desde el archivo " << nombre_archivo << ".\n";
    }
}

void listarObjetos() {
    if (memoria.empty()) {
        std::cout << "Memoria vacía\n";
    } else {
        for (const auto& [nombre, mesh] : memoria) {
            std::cout << nombre << " contiene " << mesh.vertices.size() << " vértices y " << mesh.faces.size() << " caras.\n";
        }
    }
}

void generarEnvolvente(const std::string& nombre_objeto) {
    auto it = memoria.find(nombre_objeto);
    if (it == memoria.end()) {
        std::cerr << "El objeto " << nombre_objeto << " no ha sido cargado en memoria.\n";
        return;
    }

    Vertex min, max;
    it->second.calculateBoundingBox(min, max);
    std::cout << "Caja envolvente: (" << min.x << ", " << min.y << ", " << min.z << ") a (" << max.x << ", " << max.y << ", " << max.z << ")\n";
}

void descargarObjeto(const std::string& nombre_objeto) {
    if (memoria.erase(nombre_objeto)) {
        std::cout << "El objeto " << nombre_objeto << " ha sido eliminado de la memoria de trabajo.\n";
    } else {
        std::cerr << "El objeto " << nombre_objeto << " no ha sido cargado en memoria.\n";
    }
}

void guardarObjeto(const std::string& nombre_objeto, const std::string& nombre_archivo) {
    auto it = memoria.find(nombre_objeto);
    if (it == memoria.end()) {
        std::cerr << "El objeto " << nombre_objeto << " no ha sido cargado en memoria.\n";
        return;
    }
    it->second.saveToFile(nombre_archivo);
    std::cout << "La información del objeto " << nombre_objeto << " ha sido guardada exitosamente en el archivo " << nombre_archivo << ".\n";
}

int main() {
    std::string comando;

    std::cout << "$ ";
    while (std::getline(std::cin, comando)) {
        if (comando == "salir") {
            break;
        } else if (comando.find("cargar") == 0) {
            std::string nombre_archivo = comando.substr(7);
            cargarArchivo(nombre_archivo);
        } else if (comando == "listado") {
            listarObjetos();
        } else if (comando.find("envolvente") == 0) {
            std::string nombre_objeto = comando.substr(11);
            generarEnvolvente(nombre_objeto);
        } else if (comando.find("descargar") == 0) {
            std::string nombre_objeto = comando.substr(10);
            descargarObjeto(nombre_objeto);
        } else if (comando.find("guardar") == 0) {
            std::istringstream iss(comando.substr(7));
            std::string nombre_objeto, nombre_archivo;
            iss >> nombre_objeto >> nombre_archivo;
            guardarObjeto(nombre_objeto, nombre_archivo);
        } else if (comando == "ayuda") {
            mostrarAyuda();
        } else {
            std::cerr << "Comando no reconocido: " << comando << "\n";
            std::cerr << "Escribe 'ayuda' para ver la lista de comandos disponibles.\n";
        }
        std::cout << "$ ";
    }

    return 0;
}
