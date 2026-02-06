#include <iostream>
#include <fcntl.h>  // Para las banderas O_WRONLY, O_CREAT, etc.
#include <unistd.h> // Para open, write, close
#include <cstring>  // Para strlen

int main() {
    const char* nombreArchivo = "mi_archivo.txt";
    
    // Contenido que vamos a escribir
    const char* texto = "Este contenido fue escrito usando llamadas al sistema (System Calls).\n";

    std::cout << "Intentando abrir el archivo..." << std::endl;

    /**
     * 1. OPEN
     * O_WRONLY: Abrir solo para escritura.
     * O_CREAT: Crear el archivo si no existe.
     * O_TRUNC: Si existe, borrar su contenido anterior (modificar desde cero).
     * 0644: Permisos del archivo (Lectura/Escritura para el dueño, Lectura para otros).
     */
    int descriptorArchivo = open(nombreArchivo, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Verificar si hubo error al abrir (retorna -1 en caso de error)
    if (descriptorArchivo == -1) {
        std::perror("Error al abrir el archivo");
        return 1;
    }

    std::cout << "Archivo abierto con exito. Descriptor: " << descriptorArchivo << std::endl;

    // 2. WRITE
    // Escribimos el buffer en el archivo usando el descriptor
    ssize_t bytesEscritos = write(descriptorArchivo, texto, std::strlen(texto));

    if (bytesEscritos == -1) {
        std::perror("Error al escribir en el archivo");
        close(descriptorArchivo); // Importante cerrar aunque falle
        return 1;
    }

    std::cout << "Se escribieron " << bytesEscritos << " bytes." << std::endl;

    // 3. CLOSE
    // Cerramos el descriptor para liberar el recurso
    if (close(descriptorArchivo) == -1) {
        std::perror("Error al cerrar el archivo");
        return 1;
    }

    std::cout << "Archivo cerrado correctamente." << std::endl;

    return 0;
}
