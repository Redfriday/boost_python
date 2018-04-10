#ifndef IMPLEMENTATION_A_H
#define IMPLEMENTATION_A_H

#include "interface.h"

class ImplementationA : public Interface {
 public:
    virtual int handle_int(const int& a) {
        return a + 1;
    }

    virtual std::vector<int> handle_vector(boost::python::list& l) {
        std::vector<int> b;
        for (int i = 0; i < boost::python::len(l); ++i) {
            b.push_back(boost::python::extract<int>(l[i]) + 1);
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

#endif  // IMPLEMENTATION_A_H
