cmake_minimum_required(VERSION 3.5)
project(arrow_flight_example)

find_package(Arrow REQUIRED)
find_package(ArrowFlight REQUIRED)

add_executable(flight_server server.cpp)
target_link_libraries(flight_server PRIVATE Arrow::arrow ArrowFlight::arrow_flight)

add_executable(flight_client client.cpp)
target_link_libraries(flight_client PRIVATE Arrow::arrow ArrowFlight::arrow_flight)
