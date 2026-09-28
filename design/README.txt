HOW TO RUN THE DOCKERFILE

To build and run the dockerfile:
docker compose up --build
To run a built image:
docker compose up
Run with gdb:
docker compose run --rm --entrypoint gdb campusguard ./campusguard
Run with valgrind:
docker compose run --rm --entrypoint valgrind campusguard --leak-check=full ./campusguard
Run and put results in an output.txt so it is not truncated:
docker compose up --no-log-prefix *> output.txt