#include <iostream>

using namespace std;

#include "geometry/mesh.hpp"
#include "math_utilities/matrix_operations.hpp"
#include "mef_utilities/mef_process.hpp"
#include "gid/input_output.hpp"

// Función principal del programa
int main(int argc, char **argv)
{
    // Verifica si se ha pasado un nombre de archivo como argumento
    if (argc != 2)
    {
        cout << "Incorrect use of the program, it must be: mef filename\n";
        exit(EXIT_FAILURE);
    }

    // Crear un objeto Mesh para almacenar los datos de la malla
    Mesh M;

    cout << "Reading geometry and mesh data...\n\n";
    // Obtener el nombre del archivo desde los argumentos
    string filename(argv[1]);
    // Leer los datos de entrada desde el archivo y almacenarlos en el objeto Mesh
    read_input(filename, &M);
    // M.report(); // Mostrar un reporte de la malla (comentado)

    // Obtener las cantidades de nodos y elementos
    short num_nodes = M.get_quantity(NUM_NODES);
    short num_elements = M.get_quantity(NUM_ELEMENTS);

    // Crear las matrices y vectores necesarios para el análisis
    Matrix K(num_nodes, num_nodes), local_Ks[num_elements];
    Vector b(num_nodes), local_bs[num_elements];

    cout << "Creating local systems...\n\n";
    // Crear los sistemas locales (matrices K y vectores b) para cada elemento
    create_local_systems(local_Ks, local_bs, num_elements, &M);

    cout << "Performing Assembly...\n\n";
    // Ensamblar la matriz global K y el vector global b a partir de los sistemas locales
    assembly(&K, &b, local_Ks, local_bs, num_elements, &M);

    // K.show(); b.show(); // Mostrar la matriz K y el vector b (comentado)

    cout << "Applying Neumann Boundary Conditions...\n\n";
    // Aplicar las condiciones de contorno de Neumann al vector b
    apply_neumann_boundary_conditions(&b, &M);

    // b.show(); // Mostrar el vector b después de aplicar las condiciones de Neumann (comentado)

    cout << "Applying Dirichlet Boundary Conditions...\n\n";
    // Aplicar las condiciones de contorno de Dirichlet a la matriz K y al vector b
    apply_dirichlet_boundary_conditions(&K, &b, &M);

    // K.show(); b.show(); // Mostrar la matriz K y el vector b después de aplicar las condiciones de Dirichlet (comentado)

    cout << "Solving global system...\n\n";
    // Resolver el sistema global de ecuaciones
    Vector T(b.get_size()), T_full(num_nodes);
    solve_system(&K, &b, &T);
    // T.show(); // Mostrar el vector T (comentado)

    cout << "Preparing results...\n\n";
    // Fusionar los resultados con las condiciones de contorno de Dirichlet
    merge_results_with_dirichlet(&T, &T_full, num_nodes, &M);
    // T_full.show(); // Mostrar el vector T completo (comentado)

    cout << "Writing output file...\n\n";
    // Escribir los resultados en un archivo de salida
    write_output(filename, &T_full);

    return 0;
}
