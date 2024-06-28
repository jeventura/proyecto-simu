#include <cmath>

#include "vector.hpp"
#include "matrix.hpp"

// Función para multiplicar un escalar por una matriz y almacenar el resultado en otra matriz
void product_scalar_by_matrix(float scalar, Matrix *M, int n, int m, Matrix *R)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            R->set(scalar * M->get(r, c), r, c);
}

// Función para multiplicar una matriz por un vector y almacenar el resultado en otro vector
void product_matrix_by_vector(Matrix *M, Vector *V, int n, int m, Vector *R)
{
    for (int r = 0; r < n; r++)
    {
        float acc = 0;
        for (int c = 0; c < n; c++)
            acc += M->get(r, c) * V->get(c);
        R->set(acc, r);
    }
}

// Función para multiplicar dos matrices y almacenar el resultado en otra matriz
void product_matrix_by_matrix(Matrix *A, Matrix *B, Matrix *R)
{
    int n = A->get_nrows(), m = A->get_ncols(), p = B->get_nrows(), q = B->get_ncols();
    if (m == p)
    {
        R->set_size(n, q);
        R->init();

        for (int r = 0; r < n; r++)
            for (int c = 0; c < q; c++)
                for (int i = 0; i < m; i++)
                    R->add(A->get(r, i) * B->get(i, c), r, c);
    }
    else
    {
        cout << "Incompatibilidad de dimensiones al multiplicar matrices.\n\nAbortando...\n";
        exit(EXIT_FAILURE);
    }
}

// Prototipo de la función para calcular el determinante de una matriz
float determinant(Matrix *M);

// Función auxiliar para calcular el determinante de una matriz
float determinant_auxiliar(Matrix *M)
{
    int n = M->get_ncols();
    float acc = 0;

    for (int c = 0; c < n; c++)
    {
        Matrix clon(n, n);
        M->clone(&clon);
        clon.remove_row(0);
        clon.remove_column(c);
        acc += pow(-1, c) * M->get(0, c) * determinant(&clon);
    }

    return acc;
}

// Función para calcular el determinante de una matriz
float determinant(Matrix *M)
{
    float ans;
    switch (M->get_ncols())
    {
    case 1:
        ans = M->get(0, 0);
        break;
    case 2:
        ans = M->get(0, 0) * M->get(1, 1) - M->get(0, 1) * M->get(1, 0);
        break;
    case 3:
        ans = M->get(0, 0) * M->get(1, 1) * M->get(2, 2) - M->get(0, 0) * M->get(1, 2) * M->get(2, 1) - M->get(0, 1) * M->get(1, 0) * M->get(2, 2) + M->get(0, 1) * M->get(1, 2) * M->get(2, 0) + M->get(0, 2) * M->get(1, 0) * M->get(2, 1) - M->get(0, 2) * M->get(1, 1) * M->get(2, 0);
        break;
    default:
        ans = determinant_auxiliar(M);
    }
    return ans;
}

// Función para obtener el menor de una matriz
float get_minor(Matrix *M, int n, int r, int c)
{
    Matrix clon(n, n);
    M->clone(&clon);

    clon.remove_row(r);
    clon.remove_column(c);

    return determinant(&clon);
}

// Función para calcular la matriz conjugada de una matriz
void conjugate_matrix(Matrix *M, int n, Matrix *C)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            C->set(pow(-1, r + c) * get_minor(M, n, r, c), r, c);
}

// Función para transponer una matriz y almacenar el resultado en otra matriz
void transpose(Matrix *M, int n, int m, Matrix *T)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            T->set(M->get(r, c), c, r);
}

// Función para calcular la inversa de una matriz usando la descomposición de Cholesky
void calculate_inverse_with_cholesky(Matrix *M, int n, Matrix *R)
{
    Matrix L(n, n), Y(n, n);
    float acum;

    // Fase de descomposición de Cholesky
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                acum = 0;
                for (int k = 0; k < j; k++)
                {
                    acum += pow(L.get(j, k), 2);
                }
                float rad = M->get(j, j) - acum;
                L.set(((rad <= 0) ? 0.000001 : sqrt(rad)), j, j);
            }
            else
            {
                if (i > j)
                {
                    acum = 0;
                    for (int k = 0; k < j; k++)
                    {
                        acum += L.get(i, k) * L.get(j, k);
                    }
                    L.set((1 / L.get(j, j)) * (M->get(i, j) - acum), i, j);
                }
                else
                {
                    L.set(0, i, j);
                }
            }
        }
    }

    // Fase de cálculo de Y
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                Y.set(1 / L.get(i, i), i, i);
            }
            else
            {
                if (i > j)
                {
                    acum = 0;
                    for (int k = j; k < i; k++)
                    {
                        acum += L.get(i, k) * Y.get(k, j);
                    }
                    Y.set(-(1 / L.get(i, i)) * acum, i, j);
                }
                else
                {
                    Y.set(0, i, j);
                }
            }
        }
    }

    // Fase de cálculo de la inversa
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            acum = 0;
            for (int k = i + 1; k < n; k++)
            {
                acum += L.get(k, i) * R->get(k, j);
            }
            R->set((1 / L.get(i, i)) * (Y.get(i, j) - acum), i, j);
        }
    }
}
