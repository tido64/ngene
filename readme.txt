Ngene
=====

A cross-platform generic genetic algorithm for multipurpose usage, conceived by
Tommy Anh Tuan Nguyen as a result of persistence and boredom, as well as for
its academic purposes and gains.

The program is provided as is without any warranties or indemnity whatsoever.


Dependencies
============

The code has been compiled and tested on Windows and some Unix-based operating
systems. However, there shouldn't be any problem to use Ngene on other
platforms as the code is meant to be platform independent.

Boost C++ Libraries (>= 1.34.1)
-------------------------------

Windows:

	You will need to download Boost C++ Libraries and copy the header files
	to the libs/ folder. You can obtain it from the following url:

	http://www.boost.org/

	Download and extract the compressed file, then copy or move the folder
	named "boost" into the libs/ folder.


Unix:

	For most package-based distros, you can get the libboost-dev package
	from the repositories. Otherwise, you can obtain Boost header files
	from:

	http://www.boost.org/

	Instructions for how to install them are also on this page.


OpenMP (optional)
-----------------
Take advantage of your multi-core/-processor to speed up the evolution. This is
entirely optional and will not break the code in anyway if you don't have the
opportunity or any wish to use it.

Windows:

	In Visual Studio, you will need to specify the /openmp flag. For other
	compilers, please check your manual or try looking it up on the
	Internet.


Unix:

	Just make sure you use a compiler that supports OpenMP. From what I
	know, GCC >= 4.2 supports it.
