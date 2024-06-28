#include <fstream>

// Función para leer los datos de entrada desde un archivo y poblar la malla
void read_input(string filename, Mesh *M)
{
    string line;
    float k, Q, T_bar, T_hat;
    short num_nodes, num_elements, num_dirichlet, num_neumann;
    ifstream dat_file(filename + ".dat"); // Abre el archivo con la extensión .dat

    // Lee los datos del problema desde el archivo
    dat_file >> k >> Q >> T_bar >> T_hat >> num_nodes >> num_elements >> num_dirichlet >> num_neumann;

    // Establece los datos del problema y las cantidades en el objeto Mesh
    M->set_problem_data(k, Q);
    M->set_quantities(num_nodes, num_elements, num_dirichlet, num_neumann);

    // Inicializa los arreglos en el objeto Mesh
    M->init_arrays();

    // Lee la línea de separación en el archivo
    dat_file >> line;

    // Lee los nodos desde el archivo y los inserta en la malla
    for (int i = 0; i < num_nodes; i++)
    {
        short id;
        float x, y, z;
        dat_file >> id >> x >> y >> z;
        M->insert_node(new Node(id, x, y, z), i);
    }

    // Lee las líneas de separación en el archivo
    dat_file >> line >> line;

    // Lee los elementos desde el archivo y los inserta en la malla
    for (int i = 0; i < num_elements; i++)
    {
        short id, node1_id, node2_id, node3_id, node4_id;
        dat_file >> id >> node1_id >> node2_id >> node3_id >> node4_id;
        M->insert_element(new Element(id, M->get_node(node1_id - 1), M->get_node(node2_id - 1), M->get_node(node3_id - 1), M->get_node(node4_id - 1)), i);
    }

    // Lee las líneas de separación en el archivo
    dat_file >> line >> line;

    // Lee las condiciones de contorno de Dirichlet desde el archivo y las inserta en la malla
    for (int i = 0; i < num_dirichlet; i++)
    {
        short id;
        dat_file >> id;
        M->insert_dirichlet_condition(new Condition(M->get_node(id - 1), T_bar), i);
    }

    // Lee las líneas de separación en el archivo
    dat_file >> line >> line;

    // Lee las condiciones de contorno de Neumann desde el archivo y las inserta en la malla
    for (int i = 0; i < num_neumann; i++)
    {
        short id;
        dat_file >> id;
        M->insert_neumann_condition(new Condition(M->get_node(id - 1), T_hat), i);
    }

    // Cierra el archivo de entrada
    dat_file.close();
}

// Función para escribir los resultados en un archivo de salida
void write_output(string filename, Vector *T)
{
    ofstream res_file(filename + ".post.res"); // Abre el archivo con la extensión .post.res

    // Escribe el encabezado del archivo de resultados
    res_file << "GiD Post Results File 1.0\n";

    int n = T->get_size(); // Obtiene el tamaño del vector T

    // Escribe la información de los resultados
    res_file << "Result \"Temperature\" \"Load Case 1\" " << 1 << " Scalar OnNodes\n";
    res_file << "ComponentNames \"T\"\n";
    res_file << "Values\n";

    // Escribe los valores de temperatura en el archivo
    for (int i = 0; i < n; i++)
        res_file << i + 1 << "     " << T->get(i) << "\n";

    // Escribe el final de los valores
    res_file << "End values\n";

    // Cierra el archivo de salida
    res_file.close();
}
