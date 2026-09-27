FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# build tools + debuggers
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    g++ \
    make \
    gdb \
    valgrind \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

# Build with debug symbols so gdb/valgrind are actually useful
RUN make clean && make

CMD ["./campusguard"]