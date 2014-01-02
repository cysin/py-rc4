#!/usr/bin/env python

from distutils.core import setup, Extension

setup(name='rc4 Module',
      version='0.1',
      description='rc4',
      author='',
      author_email='blueflycn@gmail.com',
      url='',
      packages=['rc4'],
      ext_modules=[Extension("rc4/_rc4",
                              ["src/py_rc4.c",
                               "src/rc4.c"
                               ],
                              libraries=["m"])]
	)
