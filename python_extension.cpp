#include <boost/python.hpp>
#include <boost/unordered_map.hpp>

#include "interface.h"
#include "implementation_a.h"
#include "implementation_b.h"

using boost::noncopyable;
using boost::python::class_;
using boost::python::bases;
using boost::python::list;
using boost::python::dict;

#define CLASS_DEF(parent, sub) class_<sub, bases<parent> >(#sub)

// Convert boost map to python dictionary.
template <class K, class V>
struct MapToDictConverter {
    static PyObject* convert(boost::unordered_map<K, V> map) {
        typename boost::unordered_map<K, V>::iterator iter;
        dict d;
        for (iter = map.begin(); iter != map.end(); ++iter) {
            d[iter->first] = iter->second;
        }
        return boost::python::incref(d.ptr());
    }
};

// Convert std vector to python list.
template <class K>
struct VectorToListConverter {
    static PyObject* convert(std::vector<K> vec) {
        typename std::vector<K>::iterator iter;
        list l;
        for (iter = vec.begin(); iter != vec.end(); ++iter) {
            l.append(*iter);
        }
        return boost::python::incref(l.ptr());
    }
};

// Convert python (int, int) dict to c++ (int, int) boost map.
// From this example, you could convert any python object to c++ object.
struct boost_map_from_python_dict {
    boost_map_from_python_dict() {
        boost::python::converter::registry::push_back(
                     &convertible,
                     &construct,
                     boost::python::type_id<boost::unordered_map<int, int>>());
    }

    static void* convertible(PyObject* obj_ptr) {
        if (!PyDict_Check(obj_ptr)) {
            return 0;
        }
        return obj_ptr;
    }

    static void construct(PyObject* obj_ptr,
             boost::python::converter::rvalue_from_python_stage1_data* data) {
        boost::unordered_map<int, int> t_map;
        Py_ssize_t i = 0;
        PyObject *key;
        PyObject *value;
        while (PyDict_Next(obj_ptr, &i, &key, &value)) {
            long lkey = PyLong_AsLong(key);
            long lvalue = PyLong_AsLong(value);
            t_map[lkey] = lvalue;
        }
               
        void* storage = ((boost::python::converter::rvalue_from_python_storage<boost::unordered_map<int, int>>*)
                         data)->storage.bytes;
        new (storage) boost::unordered_map<int, int>(t_map);
        data->convertible = storage;
    }
};

// Define module.
BOOST_PYTHON_MODULE(libpyextension) {
    boost::python::to_python_converter<boost::unordered_map<int, int>, MapToDictConverter<int, int> >();
    boost::python::to_python_converter<std::vector<int>, VectorToListConverter<int> >();
    boost_map_from_python_dict();

    class_<Interface, noncopyable>("Interface", boost::python::no_init)
            .def("handle_int", &Interface::handle_int)
            .def("handle_vector", &Interface::handle_vector)
            .def("handle_map", &Interface::handle_map);

    CLASS_DEF(Interface, ImplementationA);
    CLASS_DEF(Interface, ImplementationB);
}
