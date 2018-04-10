#ifndef IMPLEMENTATION_B_H
#define IMPLEMENTATION_B_H

#include "interface.h"

class ImplementationB : public Interface {
 public:
    virtual int handle_int(const int& a) {
        return a + 2;
    }

    virtual std::vector<int> handle_vector(boost::python::list& l) {
        std::vector<int> b;
        for (int i = 0; i < boost::python::len(l); ++i) {
            b.push_back(boost::python::extract<int>(l[i]) + 2);
        }

        return b;
    }

    virtual boost::unordered_map<int, int> handle_map(const boost::unordered_map<int, int>& a) {
        boost::unordered_map<int, int> b;
        for (boost::unordered_map<int, int>::const_iterator it = a.begin(); it != a.end(); it++) {
            b[it->first] = it->second + 1;
        }

        return b;
    }
};

#endif  // IMPLEMENTATION_B_H
