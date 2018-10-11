#include <iostream>
#include "Log.h"

using namespace std;

int main(int argc, char *argv[])
{
    Test::Log log;
    log.WriteError("haha %d\n", 1);
    log << "Another one" << endl << "Third" << endl;
    return 0;
}