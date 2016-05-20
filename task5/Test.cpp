#include <stdio.h>
#include <sstream>
#include "format.h"

using namespace std;

int main() {

    printf("%s\n", format("%d%d", 1).c_str());

/*    printf("Variable width control:\n");
    printf("%s\n", format("Variable width control:\n").c_str());

    printf("right-justified variable width: '%*c'\n", 5, 'x');
    printf("%s\n", format("right-justified variable width: '%*c'\n", 5, 'x').c_str());

    int r1, r2;
    printf("left-justified variable width : '%*c'%n\n", -5, 'x', &r1);
    printf("%s\n", format("left-justified variable width : '%*c'%n\n", -5, 'x', &r2).c_str());

    printf("(the last printf printed %d characters)\n", r1);
    printf("%s\n", format("(the last printf printed %d characters)\n", r2).c_str());

    printf("%17.4000d\n", 4000);
    printf("%s\n", format("%.4000d", 4000).c_str()); */

    int* arrint = new int [3];
    arrint[0] = 1;
    arrint[1] = 1;
 /*   cout << format("%#+X \n", 1977);
    printf("%#+X \n", 1977);*/

    arrint[2] = 1;
/*    cout << format("Characters: %c %c \n", 'a', 65);
    cout << format("Decimals: %d %ld\n", 1977, 650000L);
    cout << format("Preceding with blanks: %10d \n", 1977);
    cout << format("Preceding with zeros: %010d \n", 1977);
    cout << format("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
    cout << format("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416); */
/*    cout << format("Width trick: %*d \n", 5, 10);
    cout << format("%s \n", "A string"); */
    cout << format("%p\n", arrint);


//    printf("%p\n", arrint);
/*    printf("Characters: %c %c \n", 'a', 65);
    printf("Decimals: %d %ld\n", 1977, 650000L);
    printf("Preceding with blanks: %10d \n", 1977);
    printf("Preceding with zeros: %010d \n", 1977);
    printf("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
    printf("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
    printf("Width trick: %*d \n", 5, 10);
    printf("%s \n", "A string");
*/
}