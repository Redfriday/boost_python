# -*- coding:utf-8 -*-
import sys
import libpyextension

a = libpyextension.ImplementationA()
b = libpyextension.ImplementationB()

print 'test handle int'
print a.handle_int(1)
print b.handle_int(1)

l = [1] * 5
print 'test handle vector'
print a.handle_vector(l)
print b.handle_vector(l)

d = {1: 1, 2: 2}
print 'test handle map'
print a.handle_map(d)
print b.handle_map(d)
