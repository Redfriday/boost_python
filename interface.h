#ifndef INTERFACE_H
#define INTERFACE_H

#include <boost/python.hpp>
#include <boost/unordered_map.hpp>
#include <vector>

class Interface {
 public:
    virtual int handle_int(const int& a) = 0;

    virtual std::vector<int> handle_vector(boost::python::list& l) = 0;

    virtual boost::unordered_map<int, int> handle_map(const boost::unordered_map<int, int>& a) = 0;
};

#endif  // INTERFACE_H
