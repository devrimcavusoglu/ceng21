#ifndef __myvector_h__
#define __myvector_h__


#include <iostream>
#include <string>

#define DEFAULT_VEC_SIZE 4
#define DEFAULT_INIT_VAL_STR "OK"
#define DEFAULT_INIT_VAL_INT 10
#define DEFAULT_INIT_VAL_FLT 3.14


template <class T>
class MyVector
{
    public:
        /************************************************************/
        /*                      INITIALIZATION                      */
        
        // Constructor. The default value for vector size is 1.
        MyVector(const T& init_val, const int vector_size = 1);
        // Destructor.
        ~MyVector();

        /*************************************************************/
        /*                    MEMBER OPERATIONS                      */
        
        // Getter Function for size value
        int get_size() const;
        // Setter Function for vector's initial value
        void set_init_val(const T& new_val);
        // [] Operator Overloading
        T& operator[] (int i) const;

        /*************************************************************/
        /*                    OTHER OPERATIONS                      */

        // Appends val to the end of the vector
        void append(const T& val);
        // Resizing vector function. It gets new size as parameter.
        int resize(const int new_size);

        /*************************************************************/

        // Output operator overloading. IT IS IMPLEMENTED.
        template <class U>
        friend std::ostream& operator<<(std::ostream& os, const MyVector<U>& myVector);
    private:
        int size;       // Your vector's size
        T init_val;     // Vector's initialization value. used as default value
                        // to initialize cells.
        T* vector;      // Vector itself

        /*************************************************************/
        /*                 YOUR HELPER FUNCTIONS                     */
        void set_all(T elem);
        /*************************************************************/
};



#endif
