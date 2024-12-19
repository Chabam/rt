FROM ubuntu:latest AS dependencies
RUN apt update && apt install -y \
    git \
    libwayland-dev \
    libxkbcommon-dev \
    xorg-dev \
    ninja-build \
    python3 \
    python3-jinja2 \
    cmake \
    clang \
    clang-tools

FROM dependencies AS cmake_gen
WORKDIR /rt
COPY . /rt
RUN cmake --preset=linux-x64-dbg

FROM cmake_gen AS build_rt
WORKDIR /rt
RUN cmake --build _build

FROM scratch
COPY --from=build_rt /rt/_build/ /rt
ENTRYPOINT ["/rt"]
