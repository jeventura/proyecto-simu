// Definición de la clase Node
class Node
{
private:
    // Identificador del nodo
    short ID;
    // Coordenadas del nodo en los ejes x, y y z
    float x_coordinate;
    float y_coordinate;
    float z_coordinate;

public:
    // Constructor que inicializa el identificador y las coordenadas del nodo con los parámetros proporcionados
    Node(short identifier, float x_value, float y_value, float z_value)
    {
        ID = identifier;
        x_coordinate = x_value;
        y_coordinate = y_value;
        z_coordinate = z_value;
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

    // Método para asignar un nuevo valor a la coordenada x
    void set_x_coordinate(float x_value)
    {
        x_coordinate = x_value;
    }

    // Método para obtener el valor actual de la coordenada x
    float get_x_coordinate()
    {
        return x_coordinate;
    }

    // Método para asignar un nuevo valor a la coordenada y
    void set_y_coordinate(float y_value)
    {
        y_coordinate = y_value;
    }

    // Método para obtener el valor actual de la coordenada y
    float get_y_coordinate()
    {
        return y_coordinate;
    }

    // Método para asignar un nuevo valor a la coordenada z
    void set_z_coordinate(float z_value)
    {
        z_coordinate = z_value;
    }

    // Método para obtener el valor actual de la coordenada z
    float get_z_coordinate()
    {
        return z_coordinate;
    }
};
