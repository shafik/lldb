#include <cstdio>
#include <string>
#include <vector>
#include <optional>

using int_vect = std::vector<int> ;
using string_vec = std::vector<std::string> ;
using optional_int = std::optional<int> ;
using optional_int_vect = std::optional<int_vect> ;
using optional_string = std::optional<std::string> ;

int main()
{
    optional_int number ;

    printf( "%d\n", number.has_value() ) ; // break here

    number = 42 ;

    printf( "%d\n", *number ) ; // break here

    optional_int_vect numbers ;

    printf( "%d\n", numbers.has_value() ) ; // break here

    numbers = {1,2,3,4} ;

    printf( "%d %d\n", numbers.value()[0], numbers.value()[1] ) ; // break here

    optional_string ostring ;

    printf( "%s\n", ostring.has_value() ) ; // break here

    ostring = "hello" ;

    printf( "%s\n", ostring->c_str() ) ; // break here

    return 0;  // break here
}
