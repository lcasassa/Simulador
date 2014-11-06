Simulador
=========


1) Instalar Ode 0.12.

No hagas "sudo apt-get install libode-dev" porque instala la version 0.11.1.

sudo apt-get install automake

sudo apt-get install libtool

http://sourceforge.net/projects/opende/files/ODE/0.12/ode-0.12.tar.bz2/download

tar xjf ode-0.12.tar.bz2

cd ode-0.12

sh autogen.sh

./configure --enable-double-precision --prefix=$(PWD)/install

make

2) Instalar fuzzylight 3.0

https://code.google.com/p/fuzzylite/downloads/detail?name=fuzzylite-3.0-ubuntu64.zip&can=2&q=
ver README
cmake .
make
