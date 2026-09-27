HOW TO RUN THE DOCKERFILE

To build the dockerfile:
docker build -t campusguard .
To run the dockerfile:
docker run --rm campusguard
Run with gdb:
docker run --rm -it --entrypoint gdb campusguard ./campusguard
Run with valgrind:
docker run --rm --entrypoint valgrind campusguard ./campusguard