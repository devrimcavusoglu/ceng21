#include "myarray.h"

using namespace std;

int main()
{
    MyArray arr_obj;
    std::cout << "n is: " << arr_obj.get_n() << " size is: " << arr_obj.get_size() << "\n";
    arr_obj.print(' ');
    arr_obj.insert_data(3);
    std::cout << "n is: " << arr_obj.get_n() << " size is: " << arr_obj.get_size() << "\n";
    arr_obj.print(' ');
    arr_obj.insert_data(4);
    std::cout << "n is: " << arr_obj.get_n() << " size is: " << arr_obj.get_size() << "\n";
    arr_obj.print(' ');
    arr_obj.double_size();
    std::cout << "n is: " << arr_obj.get_n() << " size is: " << arr_obj.get_size() << "\n";
    arr_obj.print(' ');
    arr_obj.insert_data(5);
    std::cout << "n is: " << arr_obj.get_n() << " size is: " << arr_obj.get_size() << "\n";
    arr_obj.print(' ');
    arr_obj.delete_data(1);
    std::cout << "n is: " << arr_obj.get_n() << " size is: " << arr_obj.get_size() << "\n";
    arr_obj.print(' ');

    std::cout << "Constructors\n";

    MyArray arr_obj2(arr_obj);

    arr_obj2.print(' ');
    arr_obj2.insert_data(9);
    arr_obj2.print(' ');
    arr_obj2.delete_data(1);
    arr_obj2.print(' ');

    arr_obj2 = arr_obj;
    
    arr_obj2.print(' ');

    return 0;
}
