#include "node.hpp"
#include "element.hpp"
#include "condition.hpp"

// Enumeración para los parámetros del problema
enum parameter
{
    THERMAL_CONDUCTIVITY,
    HEAT_SOURCE
};
// Enumeración para las cantidades involucradas en la malla
enum quantity
{
    NUM_NODES,
    NUM_ELEMENTS,
    NUM_DIRICHLET,
    NUM_NEUMANN
};

// Definición de la clase Mesh
class Mesh
{
private:
    // Datos del problema (conductividad térmica y fuente de calor)
    float problem_data[2];
    // Cantidades de nodos, elementos, y condiciones de contorno
    short quantities[4];
    // Arreglos de punteros a nodos, elementos y condiciones de contorno
    Node **nodes;
    Element **elements;
    Condition **dirichlet_conditions;
    Condition **neumann_conditions;

public:
    // Constructor por defecto
    Mesh() {}

    // Destructor para liberar la memoria asignada dinámicamente
    ~Mesh()
    {
        free(nodes);
        free(elements);
        free(dirichlet_conditions);
        free(neumann_conditions);
    }

    // Método para asignar los datos del problema
    void set_problem_data(float k, float Q)
    {
        problem_data[THERMAL_CONDUCTIVITY] = k;
        problem_data[HEAT_SOURCE] = Q;
    }

    // Método para obtener un dato del problema
    float get_problem_data(parameter position)
    {
        return problem_data[position];
    }

    // Método para asignar las cantidades de nodos, elementos y condiciones de contorno
    void set_quantities(short num_nodes, short num_elements, short num_dirichlet, short num_neumann)
    {
        quantities[NUM_NODES] = num_nodes;
        quantities[NUM_ELEMENTS] = num_elements;
        quantities[NUM_DIRICHLET] = num_dirichlet;
        quantities[NUM_NEUMANN] = num_neumann;
    }

    // Método para obtener una cantidad específica
    short get_quantity(quantity position)
    {
        return quantities[position];
    }

    // Método para inicializar los arreglos de nodos, elementos y condiciones de contorno
    void init_arrays()
    {
        nodes = (Node **)malloc(sizeof(Node *) * quantities[NUM_NODES]);
        elements = (Element **)malloc(sizeof(Element *) * quantities[NUM_ELEMENTS]);
        dirichlet_conditions = (Condition **)malloc(sizeof(Condition *) * quantities[NUM_DIRICHLET]);
        neumann_conditions = (Condition **)malloc(sizeof(Condition *) * quantities[NUM_NEUMANN]);
    }

    // Método para insertar un nodo en una posición específica
    void insert_node(Node *node, short position)
    {
        nodes[position] = node;
    }

    // Método para obtener un nodo de una posición específica
    Node *get_node(short position)
    {
        return nodes[position];
    }

    // Método para insertar un elemento en una posición específica
    void insert_element(Element *element, short position)
    {
        elements[position] = element;
    }

    // Método para obtener un elemento de una posición específica
    Element *get_element(short position)
    {
        return elements[position];
    }

    // Método para insertar una condición de contorno de Dirichlet en una posición específica
    void insert_dirichlet_condition(Condition *dirichlet_condition, short position)
    {
        dirichlet_conditions[position] = dirichlet_condition;
    }

    // Método para obtener una condición de contorno de Dirichlet de una posición específica
    Condition *get_dirichlet_condition(short position)
    {
        return dirichlet_conditions[position];
    }

    // Método para verificar si un nodo tiene una condición de contorno de Dirichlet
    bool does_node_have_dirichlet_condition(int id)
    {
        bool ans = false;
        for (int i = 0; i < quantities[NUM_DIRICHLET]; i++)
            if (dirichlet_conditions[i]->get_node()->get_ID() == id)
            {
                ans = true;
                break;
            }
        return ans;
    }

    // Método para insertar una condición de contorno de Neumann en una posición específica
    void insert_neumann_condition(Condition *neumann_condition, short position)
    {
        neumann_conditions[position] = neumann_condition;
    }

    // Método para obtener una condición de contorno de Neumann de una posición específica
    Condition *get_neumann_condition(short position)
    {
        return neumann_conditions[position];
    }

    // Método para reportar los datos del problema, cantidades y listas de nodos, elementos y condiciones de contorno
    void report()
    {
        cout << "Problem Data\n**********************\n";
        cout << "Thermal Conductivity: " << problem_data[THERMAL_CONDUCTIVITY] << "\n";
        cout << "Heat Source: " << problem_data[HEAT_SOURCE] << "\n\n";
        cout << "Quantities\n***********************\n";
        cout << "Number of nodes: " << quantities[NUM_NODES] << "\n";
        cout << "Number of elements: " << quantities[NUM_ELEMENTS] << "\n";
        cout << "Number of dirichlet boundary conditions: " << quantities[NUM_DIRICHLET] << "\n";
        cout << "Number of neumann boundary conditions: " << quantities[NUM_NEUMANN] << "\n\n";
        cout << "List of nodes\n**********************\n";
        for (int i = 0; i < quantities[NUM_NODES]; i++)
            cout << "Node: " << nodes[i]->get_ID() << ", x= " << nodes[i]->get_x_coordinate() << ", y= " << nodes[i]->get_y_coordinate() << ", z= " << nodes[i]->get_z_coordinate() << "\n";
        cout << "\nList of elements\n**********************\n";
        for (int i = 0; i < quantities[NUM_ELEMENTS]; i++)
        {
            cout << "Element: " << elements[i]->get_ID() << ", Node 1= " << elements[i]->get_node1()->get_ID();
            cout << ", Node 2= " << elements[i]->get_node2()->get_ID() << ", Node 3= " << elements[i]->get_node3()->get_ID() << ", Node 4= " << elements[i]->get_node4()->get_ID() << "\n";
        }
        cout << "\nList of Dirichlet boundary conditions\n**********************\n";
        for (int i = 0; i < quantities[NUM_DIRICHLET]; i++)
            cout << "Condition " << i + 1 << ": " << dirichlet_conditions[i]->get_node()->get_ID() << ", Value= " << dirichlet_conditions[i]->get_value() << "\n";
        cout << "\nList of Neumann boundary conditions\n**********************\n";
        for (int i = 0; i < quantities[NUM_NEUMANN]; i++)
            cout << "Condition " << i + 1 << ": " << neumann_conditions[i]->get_node()->get_ID() << ", Value= " << neumann_conditions[i]->get_value() << "\n";
        cout << "\n";
    }
};
