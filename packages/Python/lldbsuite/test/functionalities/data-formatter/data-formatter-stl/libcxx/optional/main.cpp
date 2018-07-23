#include <cstdio>
#include <string>
#include <vector>
#include <optional>

using int_vect = std::vector<int> ;
using optional_int = std::optional<int> ;
using optional_int_vect = std::optional<int_vect> ;
using optional_string = std::optional<std::string> ;

int main()
{
    optional_int number_not_engaged ;
    optional_int number_engaged = 42 ;

    printf( "%d\n", *number_engaged) ;
                                        //% self.expect("frame variable number_not_engaged", substrs=["Has Value=false",  "{}"])
                                       //% self.expect("frame variable number_engaged", substrs=["Has Value=true", "Value = 42", "}"])

    optional_int_vect numbers{{1,2,3,4}} ;

    printf( "%d %d\n", numbers.value()[0], numbers.value()[1] ) ;
    //% self.expect("frame variable numbers", substrs=["Has Value=true", "Value = size=4", "[0] = 1", "[1] = 2", "[2] = 3", "[3] = 4", "}"])

    optional_string ostring = "hello" ;

    printf( "%s\n", ostring->c_str() ) ;
    //% self.expect("frame variable ostring", substrs=["Has Value=true", "Value = \"hello\"", "}"])

    return 0; // break here
}
