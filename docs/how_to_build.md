# How to build
1. install cmake



2. build libevent

```
cd deps
git submodule add https://github.com/libevent/libevent
git checkout release-2.1.12-stable
./autogen.sh
./configure --disable-openssl
make
sudo make install
```
3. build google test
```
cd deps
git submodule add https://github.com/google/googletest
cd googletest
mkdir build
cd build
cmake ..
make
sudo make install
```
