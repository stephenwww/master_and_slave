#include "slave.h"

int main(int argc, char* argv[])
{
    mpi::environment env;
    mpi::communicator world;

    slave s(world);
    s.action();
}