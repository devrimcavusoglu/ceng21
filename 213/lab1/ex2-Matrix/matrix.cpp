#include "matrix.hpp"

/*              Default Constructor for Matrix Class

In the constructor, you should initialize class members as the following:
Your dimension should be set to given parameter. And your matrix should be
initialized with full of zeros in nxn dimension.                           */

Matrix::Matrix(int dimension)
{
    n = dimension;
    matrix = new int*[dimension];
    for (int i=0; i<n; i++){
        matrix[i] = new int[dimension];
    }
}

/*                    Destructor for Matrix Class
In the destructor you should free all the memory you allocated for your
matrix.                                                                   */
Matrix::~Matrix()
{
    for (int i=0; i<n; i++){
        delete matrix[i];
    }
    delete matrix;
}

/*                Get Dimension Function
This function should return the dimension of the matrix.   */
int Matrix::get_dimension() const
{
    return n;
}

/*                  Get Number Function
This function should return the value in the ith row and
jth column of the matrix. For example, consider matrix A,

    2 3 4
A = 1 0 9
    8 7 5

A.get_number(2,2) should return 5

or

A.get_number(0,1) should return 3.                         */
int Matrix::get_number(int i, int j) const
{   
    return matrix[i][j];
}


/*                  Set Number Function
This function should set the value in the ith row and
jth column of the matrix. For example, consider matrix A,

    2 3 4
A = 1 0 9
    8 7 5

A.set_number(2, 2, 6) will make A as:
    2 3 4
A = 1 0 9
    8 7 6                                                 */
void Matrix::set_number(int i, int j, int value)
{
    matrix[i][j] = value;
}

/*               Assignment Operator Overloading
THE ANSWER IS GIVEN, INSPECT IT.
This function should make a deep copy of the rhs Matrix to the
current one. The function return a reference to Matrix Class Object. */
/* Assume that dimensions of this and rhs are the same. */
/* Just update values of this with values from rhs. */
Matrix& Matrix::operator=(const Matrix& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    
    int i, j;
    
    this->n = rhs.get_dimension();
    
    for (i = 0; i < this->n; i++)
    {
        for (j = 0; j < this->n; j++)
            this->matrix[i][j] = rhs.get_number(i, j);
    }
    
    return *this;
}

/*                      Sum With Function
This function adds all corresponding values to the current matrix.
For Example, consider matrices A and B:

    2 3 4      2 5 1
A = 1 0 9  B = 3 8 0
    8 7 5      1 2 1

A.sum_with(B) will change A as:

    4 8 5
A = 4 8 9
    9 9 6

However, Matrix B will remain same as:

    2 5 1
B = 3 8 0
    1 2 1
*/
/* Assume that dimensions of this and rhs are the same. */
void Matrix::sum_with(const Matrix& rhs)
{
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            this->matrix[i][j] += rhs.get_number(i,j);
        }
    }
}


/*                      Substract Function
This function substracts all corresponding values from the current
matrix. For Example, consider matrices A and B:

    2 3 4      2 5 1
A = 1 0 9  B = 3 8 0
    8 7 5      1 2 1

A.substract(B) will change A as:

     0  -2  3
A = -2  -8  9
     7   5  4

However, Matrix B will remain same as:

    2 5 1
B = 3 8 0
    1 2 1
*/
/* Assume that dimensions of this and rhs are the same. */
void Matrix::substract(const Matrix& rhs)
{
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            matrix[i][j] -= rhs.get_number(i,j);
        }
    }
}

/*              << Operator Overloading
This friend function used for creating a output format for
our Matrix implementation. This is implemented for you. Don't
change any of the code in this function.                        */
std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    int i, j, n;
    n = matrix.get_dimension();
    os << "[";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (!j && i)
                os << " ";
            os << matrix.get_number(i, j) << ", ";
        }
        os << matrix.get_number(i, n - 1);
        if (i == n - 1)
            os << "]" << std::endl;
        else
            os << std::endl;
    }
    return os;
}
