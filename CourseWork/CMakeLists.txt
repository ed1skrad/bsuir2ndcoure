cmake_minimum_required(VERSION 3.23.2)
project(CourseWork)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/libpqxx-7.8.1)
add_executable(CourseWork main.cpp models/Customer.cpp models/Customer.h models/Orders.cpp models/Order.h models/Transport.cpp models/Transport.h models/PublicTransport.cpp models/PublicTransport.h models/Bus.cpp models/Bus.h models/Trolleybus.cpp models/Trolleybus.h models/Taxi.cpp models/Taxi.h database/Database.cpp database/Database.h models/ticket/TransportTicket.cpp models/ticket/TransportTicket.h models/ticket/TicketManager.cpp models/ticket/TicketManager.h models/Stop.cpp models/Stop.h models/Route.cpp models/Route.h models/RouteStop.cpp models/RouteStop.h models/price/RoutePrice.cpp models/price/RoutePrice.h models/schedule/TransportSchedule.cpp models/schedule/TransportSchedule.h admin/Admin.cpp admin/Admin.h models/join/StopRoute.cpp models/join/StopRoute.h models/join/TransportRoute.cpp models/join/TransportRoute.h models/join/RouteStop.cpp models/join/RouteStop.h)

target_link_libraries(CourseWork pqxx)
