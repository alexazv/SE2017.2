PATH="$PATH:/home/alexandre/cmake/cmake-3.8.2-Linux-x86_64/bin"
rm -rf build
mkdir build
cd build

cmake -DBoard="bbc_microbit" ..
#make pristine -j4
make -j4

cd zephyr
cp -av zephyr.bin /media/alexandre/MICROBIT
