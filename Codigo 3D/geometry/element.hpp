// Definición de la clase Element
class Element
{
private:
    // Identificador del elemento
    short ID;
    // Punteros a objetos de tipo Node, representando los nodos del elemento
    Node *node1;
    Node *node2;
    Node *node3;
    Node *node4;

public:
    // Constructor que inicializa el identificador y los punteros a nodos con los parámetros proporcionados
    Element(short identifier, Node *first_node, Node *second_node, Node *third_node, Node *fourth_node)
    {
        ID = identifier;
        node1 = first_node;
        node2 = second_node;
        node3 = third_node;
        node4 = fourth_node;
    }

    // Método para asignar un nuevo valor al miembro ID
    void set_ID(short identifier)
    {
        ID = identifier;
    }

    // Método para obtener el valor actual del miembro ID
    short get_ID()
    {
        return ID;
    }

    // Método para asignar un nuevo valor al miembro node1
    void set_node1(Node *node)
    {
        node1 = node;
    }

    // Método para obtener el valor actual del miembro node1
    Node *get_node1()
    {
        return node1;
    }

    // Método para asignar un nuevo valor al miembro node2
    void set_node2(Node *node)
    {
        node2 = node;
    }

    // Método para obtener el valor actual del miembro node2
    Node *get_node2()
    {
        return node2;
    }

    // Método para asignar un nuevo valor al miembro node3
    void set_node3(Node *node)
    {
        node3 = node;
    }

    // Método para obtener el valor actual del miembro node3
    Node *get_node3()
    {
        return node3;
    }

    // Método para asignar un nuevo valor al miembro node4
    void set_node4(Node *node)
    {
        node4 = node;
    }

    // Método para obtener el valor actual del miembro node4
    Node *get_node4()
    {
        return node4;
    }
};
