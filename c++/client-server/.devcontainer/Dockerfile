FROM gcc:13.2.0-bookworm

# Install dependencies
RUN apt-get -qq update; \
    apt-get install -qqy --no-install-recommends \
        gnupg2 wget ca-certificates apt-transport-https \
        autoconf automake cmake dpkg-dev file make patch \
        git
 
RUN git clone --depth 1 https://github.com/google/googletest.git; \
    cd googletest; \
    mkdir build; \
    cd build; \
    cmake .. -DBUILD_GMOCK=OFF; \
    make; \
    make install


RUN git clone --depth 1 --shallow-submodules --recurse-submodules https://github.com/boostorg/boost.git; \
    cd boost; \
    mkdir build; \
    cd build; \
    cmake ..; \
    make; \
    make install
