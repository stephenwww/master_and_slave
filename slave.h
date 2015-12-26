#ifndef _SLAVE_H
#define _SLAVE_H

#include <iostream>
#include <string>

#include <boost/mpi.hpp>
#include <boost/serialization/string.hpp>

#include "const.h"

namespace mpi = boost::mpi;

class slave
{
public:
	slave(const mpi::communicator& world):
	    _world(world) {}

	slave(const slave&) = delete;
	slave& operator=(const slave&) = delete;

	// note that this cmd cannot be const due to broadcast's second parameter
	void action() const
	{
		std::cout << "slave " << _world.rank() << " action" << std::endl;		
		std::string cmd;
		broadcast(_world, cmd, MASTER_RANK);
		std::cout << "slave " << _world.rank() << " commit: " << cmd << std::endl;
		_world.barrier();
	}

private:
	// we don't use shared_ptr, 'cause communicator's 
	// member functions all are const.
	mpi::communicator _world;
};

#endif