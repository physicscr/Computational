
#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>
#include <string>
#include "stb_image_write.h" 
#define STB_IMAGE_WRITE_IMPLEMENTATION

using namespace std;


//largo y iteraciones: Define el tamaño de la malla (50x50) y el número de pasos de tiempo (1000).
const int largo = 50;
const int iteraciones = 1000;

//alpha: Coeficiente de difusión térmica.
const double alpha = 2.0;

//delta_x y delta_t: Parámetros para discretización espacial y temporal.
const double delta_x = 1.0;
const double delta_t = (delta_x * delta_x) / (4.0 * alpha);

//gamma_value: Valor relacionado con la estabilidad del esquema numérico
const double gamma_value = (alpha * delta_t) / (delta_x * delta_x);

// Inicializa la malla tridimensional T: Contiene los valores de temperatura en el tiempo y el espacio.
// Establece condiciones iniciales: Cada celda empieza con temperatura 0.0.
void initializeGrid(vector<vector<vector<double>>>& T) {
    for (int l = 0; l < iteraciones; ++l) {
        for (int i = 0; i < largo; ++i) {
            for (int j = 0; j < largo; ++j) {
                T[l][i][j] = 0.0;  // condiciones iniciales
            }
        }
    }

    // Declaramos condiciones de frontera, Superior (100.0), inferior (25.0), izquierdo (50.0), derecho (0.0).
    for (int l = 0; l < iteraciones; ++l) {
        // Superior
        for (int i = 0; i < largo; ++i) {
            T[l][i][largo-1] = 100.0;
        }

        // Izquierdo
        for (int j = 0; j < largo; ++j) {
            T[l][0][j] = 50.0;
        }

        // Inferior
        for (int i = 0; i < largo; ++i) {
            T[l][i][0] = 25.0;
        }

        // derecha
        for (int j = 0; j < largo; ++j) {
            T[l][largo-1][j] = 0.0;
        }
    }
}

// Calcula nuevas temperaturas con diferencias finitas: Combina valores de celdas adyacentes para simular la propagación del calor.
void solveHeatEquation(vector<vector<vector<double>>>& T) {
    // Paralelización de los ciclos for para acelerar el cálculo
    #pragma omp parallel for
    for (int l = 0; l < iteraciones - 1; ++l) {
        for (int i = 1; i < largo - 1; ++i) {
            for (int j = 1; j < largo - 1; ++j) {
                T[l + 1][i][j] = T[l][i][j] + gamma_value * (T[l][i + 1][j] + T[l][i - 1][j] + T[l][i][j + 1] + T[l][i][j - 1] - 4 * T[l][i][j]);
            }
        }
    }
}

// Extrae el estado final de la simulación (T[iteraciones - 1]).
void saveTemperatureToImage(const vector<vector<vector<double>>>& T) {
    
    vector<unsigned char> image(largo * largo * 3);  // imagen que contiene 3 colores

    for (int i = 0; i < largo; ++i) {
        for (int j = 0; j < largo; ++j) {
            double temperature = T[iteraciones - 1][i][j];

            // Escala temperaturas a valores de color (0-255): Convierte valores de temperatura a colores para visualizar.
            unsigned char color_value = static_cast<unsigned char>(min(255.0, max(0.0, temperature)));

            // 
            image[(i * largo + j) * 3 + 0] = color_value;  // Rojo 
            image[(i * largo + j) * 3 + 1] = 0;            // Verde 
            image[(i * largo + j) * 3 + 2] = 255 - color_value;  // Azul
        }
    }

    // Guarda la imagen en formato pdf
    stbi_write_png("heat_map_final.png", largo, largo, 3, image.data(), largo * 3);
}

int main() {
    // auto start: Captura el tiempo inicial.
    auto start = chrono::high_resolution_clock::now();
    cout << "2D Ecuacion de Calor\n";

    // Crea la malla 3D T: Vector de dimensiones [tiempo][x][y] inicializado con ceros.
    vector<vector<vector<double>>> T(iteraciones, vector<vector<double>>(largo, vector<double>(largo, 0.0)));

    //  Inicializamos las condiciones.
    initializeGrid(T);

    // Resolvemos la ecuación del calor.
    solveHeatEquation(T);

    // Guarda el resultado como imagen.
    saveTemperatureToImage(T);

    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Time taken: " << duration.count() << " seconds\n";

    return 0;
}
