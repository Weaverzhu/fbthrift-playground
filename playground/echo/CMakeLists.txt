add_executable(server server.cc)
add_executable(client client.cc)

target_link_libraries(server PUBLIC
    echo-cpp2
    rpc_bundle
)

target_link_libraries(client PUBLIC
    echo-cpp2
    rpc_bundle
)

target_link_options(server PUBLIC -lpthread)

target_link_options(client PUBLIC -lpthread)