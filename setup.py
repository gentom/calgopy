from distutils.core import setup, Extension

setup(name='gmsort', version='1.0', description='sort algorithms extension module for python',
      ext_modules=[Extension('gmsort', ['./sort/module/sort.c'])])
