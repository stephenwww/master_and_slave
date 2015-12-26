#ifndef _MASTER_H
#define _MASTER_H

#include <iostream>
#include <string>

#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>
#include <boost/mpi/collectives.hpp>

#include "const.h"

namespace mpi = boost::mpi;

class master
{
public:
	master(const mpi::communicator& world):
	    _world(world) {}

	master(const master&) = delete;
	master& operator=(const master&) = delete;

	// note that this cmd cannot be const due to broadcast's second parameter
	void issue(std::string& cmd) const
	{
		std::cout << "master issue" << std::endl;
		boost::mpi::broadcast(_world, cmd, 0);
		// todo receive all
		_world.barrier();
		std::cout << "master issue done" << std::endl;
	}

private:
	// we don't use shared_ptr, 'cause communicator's 
	// member functions all are const.
	mpi::communicator _world;
};

#endif