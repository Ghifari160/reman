FROM ubuntu:18.04

LABEL maintainer "GHIFARI160 <ghifari@ghifari160.com>"

RUN set -x && \
    apt update && \
    apt upgrade -y && \
    apt autoremove -y && \
    apt install --no-install-recommends --no-install-suggests -y curl ca-certificates && \
    apt clean && \
    rm -rf /var/lib/apt/lists/* && \
    mkdir /init

#################
## Build Tools ##
#################

RUN set -x && \
    apt update && \
    apt install --no-install-recommends --no-install-suggests -y git build-essential clang python && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

#################
##    CMake    ##
#################

RUN set -x && \
    apt update && \
    apt install --no-install-recommends --no-install-suggests -y libssl-dev libcurl4-openssl-dev zlib1g-dev && \
    apt clean && \
    rm -rf /var/lib/apt/lists/* && \
    cd /root && \
    curl -sL https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz | tar -zxvf - && \
    cd cmake-3.18.4 && \
    ./bootstrap --system-curl --parallel=4 && \
    make -j4 && \
    make install

#################
## depot_tools ##
#################

RUN set -x && \
    cd /root && \
    git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git

ENV PATH="/root/depot_tools:${PATH}"

#################
##    ReMan    ##
#################

RUN set -x && \
    apt update && \
    apt install --no-install-recommends --no-install-suggests -y rsync zip && \
    apt clean && \
    rm -rf /var/lib/apt/lists/* && \
    cd /root && \
    git clone https://github.com/ghifari160/reman.git && \
    cd reman && \
    ./install.sh

ENV PATH="/root/reman/bin:${PATH}"
ENV REMAN_DIR="/root/reman"
