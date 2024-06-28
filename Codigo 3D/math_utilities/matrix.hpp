#include <stdio.h>

// Definición de la clase Matrix
class Matrix
{
private:
    int nrows, ncols; // Número de filas y columnas
    float **data;     // Puntero a los datos de la matriz

    // Función para crear la matriz y asignar memoria
    void create()
    {
        data = (float **)malloc(sizeof(float *) * nrows);
        for (int r = 0; r < nrows; r++)
            data[r] = (float *)malloc(sizeof(float) * ncols);
    }

public:
    // Constructor por defecto
    Matrix() {}

    // Constructor que inicializa la matriz con un número de filas y columnas
    Matrix(int rows, int cols)
    {
        nrows = rows;
        ncols = cols;
        create();
    }

    // Destructor que libera la memoria asignada
    ~Matrix()
    {
        for (int r = 0; r < nrows; r++)
            free(data[r]);
        free(data);
    }

    // Función para inicializar todos los elementos de la matriz a cero
    void init()
    {
        for (int r = 0; r < nrows; r++)
            for (int c = 0; c < ncols; c++)
                data[r][c] = 0;
    }

    // Función para establecer el tamaño de la matriz y asignar memoria
    void set_size(int rows, int cols)
    {
        nrows = rows;
        ncols = cols;
        create();
    }

    // Función para obtener el número de filas
    int get_nrows()
    {
        return nrows;
    }

    // Función para obtener el número de columnas
    int get_ncols()
    {
        return ncols;
    }

    // Función para establecer un valor en una posición específica de la matriz
    void set(float value, int row, int col)
    {
        data[row][col] = value;
    }

    // Función para añadir un valor a una posición específica de la matriz
    void add(float value, int row, int col)
    {
        data[row][col] += value;
    }

    // Función para obtener el valor en una posición específica de la matriz
    float get(int row, int col)
    {
        return data[row][col];
    }

    // Función para eliminar una fila de la matriz
    void remove_row(int row)
    {
        int neo_index = 0;
        float **neo_data = (float **)malloc(sizeof(float *) * (nrows - 1));
        for (int i = 0; i < nrows; i++)
            if (i != row)
            {
                neo_data[neo_index] = data[i];
                neo_index++;
            }
        free(data[row]); // Libera la memoria de la fila eliminada
        free(data);      // Libera la memoria de la matriz original
        data = neo_data; // Asigna el nuevo arreglo de datos
        nrows--;         // Decrementa el número de filas
    }

    // Función para eliminar una columna de la matriz
    void remove_column(int col)
    {
        int neo_index = 0;
        float **neo_data = (float **)malloc(sizeof(float *) * nrows);
        for (int r = 0; r < nrows; r++)
            neo_data[r] = (float *)malloc(sizeof(float) * (ncols - 1));

        for (int r = 0; r < nrows; r++)
        {
            for (int c = 0; c < ncols; c++)
                if (c != col)
                {
                    neo_data[r][neo_index] = data[r][c];
                    neo_index++;
                }
            neo_index = 0;
        }
        for (int r = 0; r < nrows; r++)
            free(data[r]); // Libera la memoria de las filas originales
        free(data);        // Libera la memoria de la matriz original
        data = neo_data;   // Asigna el nuevo arreglo de datos
        ncols--;           // Decrementa el número de columnas
    }

    // Función para clonar los datos de la matriz actual a otra matriz
    void clone(Matrix *other)
    {
        for (int r = 0; r < nrows; r++)
            for (int c = 0; c < ncols; c++)
                other->set(data[r][c], r, c);
    }

    // Función para mostrar los datos de la matriz en la consola
    void show()
    {
        cout << "[ ";
        for (int r = 0; r < nrows; r++)
        {
            cout << "[ " << data[r][0];
            for (int c = 1; c < ncols; c++)
            {
                cout << ", " << data[r][c];
            }
            cout << " ] ";
        }
        cout << " ]\n\n";
    }
};
