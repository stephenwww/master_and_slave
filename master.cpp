#include "master.h"

int main(int argc, char* argv[])
{
    mpi::environment env;
    mpi::communicator world;

    master m(world);

    std::string cmd = "ping";
    m.issue(cmd);
}