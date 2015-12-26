make: master.h master.cpp slave.h slave.cpp const.h
	mpic++ -L/Users/stephen/lib/c++/boost_1_60_0/lib -lboost_mpi-mt -lboost_serialization-mt \
 -std=c++11 master.cpp -o master
	mpic++ -L/Users/stephen/lib/c++/boost_1_60_0/lib -lboost_mpi-mt -lboost_serialization-mt \
 -std=c++11 slave.cpp -o slave