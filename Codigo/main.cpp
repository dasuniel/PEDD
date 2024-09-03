#include <iostream>
#include <string>

void mostrarAyuda() {
    std::cout << "Comandos disponibles:\n";
    std::cout << "  cargar nombre_archivo\n";
    std::cout << "  listado\n";
    std::cout << "  envolvente nombre_objeto\n";
    std::cout << "  envolvente\n";
    std::cout << "  descargar nombre_objeto\n";
    std::cout << "  guardar nombre_objeto nombre_archivo\n";
    std::cout << "  salir\n";
    std::cout << "  ayuda\n";
}

int main() {
    std::string comando;

    std::cout << "$ ";
    while (std::getline(std::cin, comando)) {
        if (comando == "salir") {
            break;
        } else if (comando == "ayuda") {
            mostrarAyuda();
        } else {
            std::cout << "Comando no reconocido: " << comando << "\n";
            std::cout << "Escribe 'ayuda' para ver la lista de comandos disponibles.\n";
        }
        std::cout << "$ ";
    }

    return 0;
}
