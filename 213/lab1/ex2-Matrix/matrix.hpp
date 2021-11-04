#ifndef __matrix_v1_hpp__
#define __matrix_v1_hpp__

#include <iostream>

class Matrix
{
    public:
        /*************************************************************/
        /*                      INITIALIZATION                      */

        // Constructor. The default value for dimension is 4.
        Matrix(int dimension = 4);
        // Destructor.
        ~Matrix();

        /*************************************************************/
        /*                    MEMBER OPERATIONS                      */

        // Getter Function for dimension value
        int get_dimension() const;
        // Getter Function for ith row and jth column member of matrix
        int get_number(int i, int j) const;
        // Setter Function for ith row and jth column member of matrix
        void set_number(int i, int j, int value);

        /*************************************************************/
        /*                    OTHER OPERATIONS                       */

        // Assignment Operator Overloading
        Matrix& operator=(const Matrix& rhs);
        // Addition operation. Adds rhs matrix to the current one.
        void sum_with(const Matrix& rhs);
        // Substraction operation. Substracts rhs matrix from the current one.
        // Result is stored in the current one.
        void substract(const Matrix& rhs);

        /*************************************************************/

        // Output operator overloading. IT IS IMPLEMENTED.
        friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    private:
        int n;                 // Your dimension value (nxn matrix)
        int** matrix;          // Your nxn Matrix

        /*************************************************************/
        /*              YOUR HELPER FUNCTIONS(OPTIONAL)              */
        // You can define any helper functions here. Don't change any
        // given for you in the above.

        /*************************************************************/
};

#endif // __matrix_v1_hpp__
