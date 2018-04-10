This repo is an example of calling c++ function in python using boost python.
It also shows how to transfer python dict to c++ map, how to transfer c++ map python dict
and how to transter c++ list to python list.
After reading this example, you can transter all data type between c++ and python.

Steps to run this example.
 1. Install boost in your system, the example needs boost python.
     (1) Get a copy of the source code of boost.
     (2) $cd $root_path_boost_source
         $sudo ./bootstrap.sh --prefix=/usr/local
         $sudo ./b2 cxxflags=-fPIC cflags=-fPIC --c++11
      Note: You must specify -fPIC, because python needs the imported .so lib location independent.
     (3) Go into root path of this repo; mkdir build; cd build && make.
     (4) run python test.py.
