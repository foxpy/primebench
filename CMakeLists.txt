cmake_minimum_required(VERSION 3.1)
project(Primebench)

add_subdirectory(qc)
add_executable(primes primes.c)
target_link_libraries(primes PUBLIC qc)
