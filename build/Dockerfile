FROM quay.io/school21/alpine:3.16

RUN apk --no-cache --upgrade add \
    valgrind \
    bash \
    build-base \
    cppcheck \
    alpine-sdk \
    pcre-dev \
    clang-extra-tools \
    gtest-dev \
    gtest \
    g++

RUN apk update

RUN apk add --no-cache cmake


WORKDIR /test

COPY . /test

WORKDIR "/test/src"

ENTRYPOINT ["make", "test", "valgrind"]