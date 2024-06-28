// Definición de la clase Vector
class Vector
{
private:
    int size;    // Tamaño del vector
    float *data; // Puntero a los datos del vector

    // Función para crear el vector y asignar memoria
    void create()
    {
        data = (float *)malloc(sizeof(float) * size);
    }

public:
    // Constructor por defecto
    Vector() {}

    // Constructor que inicializa el vector con una cantidad de datos especificada
    Vector(int data_qty)
    {
        size = data_qty;
        create();
    }

    // Destructor que libera la memoria asignada al vector
    ~Vector()
    {
        free(data);
    }

    // Función para inicializar todos los elementos del vector a cero
    void init()
    {
        for (int i = 0; i < size; i++)
            data[i] = 0;
    }

    // Función para establecer el tamaño del vector y asignar memoria
    void set_size(int num_values)
    {
        size = num_values;
        create();
    }

    // Función para obtener el tamaño del vector
    int get_size()
    {
        return size;
    }

    // Función para establecer un valor en una posición específica del vector
    void set(float value, int position)
    {
        data[position] = value;
    }

    // Función para añadir un valor a una posición específica del vector
    void add(float value, int position)
    {
        data[position] += value;
    }

    // Función para obtener el valor en una posición específica del vector
    float get(int position)
    {
        return data[position];
    }

    // Función para eliminar una fila del vector
    void remove_row(int row)
    {
        int neo_index = 0;
        float *neo_data = (float *)malloc(sizeof(float) * (size - 1));
        for (int i = 0; i < size; i++)
            if (i != row)
            {
                neo_data[neo_index] = data[i];
                neo_index++;
            }
        free(data);      // Libera la memoria del vector original
        data = neo_data; // Asigna el nuevo arreglo de datos
        size--;          // Decrementa el tamaño del vector
    }

    // Función para mostrar el contenido del vector en la consola
    void show()
    {
        cout << "[ " << data[0];
        for (int i = 1; i < size; i++)
            cout << "; " << data[i];
        cout << " ]\n\n";
    }
};
