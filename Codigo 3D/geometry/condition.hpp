// Definición de la clase Condition
class Condition
{
private:
    // Puntero a un objeto de tipo Node
    Node *node;
    // Valor flotante asociado a la condición
    float value;

public:
    // Constructor que inicializa los miembros node y value con los parámetros proporcionados
    Condition(Node *node_to_assign, float value_to_assign)
    {
        node = node_to_assign;
        value = value_to_assign;
    }

    // Método para asignar un nuevo valor al miembro node
    void set_node(Node *node_to_assign)
    {
        node = node_to_assign;
    }

    // Método para obtener el valor actual del miembro node
    Node *get_node()
    {
        return node;
    }

    // Método para asignar un nuevo valor al miembro value
    void set_value(float value_to_assign)
    {
        value = value_to_assign;
    }

    // Método para obtener el valor actual del miembro value
    float get_value()
    {
        return value;
    }
};
