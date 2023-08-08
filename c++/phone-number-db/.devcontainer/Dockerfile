FROM gcc:13.2.0-bookworm

# Install dependencies
RUN apt-get -qq update; \
    apt-get install -qqy --no-install-recommends \
        gnupg2 wget ca-certificates apt-transport-https \
        autoconf automake cmake dpkg-dev file make patch \
        git libcppunit-dev
