#include <stdio.h>
#include <sstream>
#include "format.h"

using namespace std;

int main() {
    int *arrint = new int[3];
    arrint[0] = 1;
    arrint[1] = 1;
    cout << format("%#+X \n", 1977);
    printf("%#+X \n", 1977);
}