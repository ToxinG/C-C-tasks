#include <stdio.h>
#include <sstream>
#include "format.h"

using namespace std;

int main() {

    printf("%s\n", format("%@", nullptr).c_str());

//    printf("%s\n", format("%d%d", 1).c_str());
}
