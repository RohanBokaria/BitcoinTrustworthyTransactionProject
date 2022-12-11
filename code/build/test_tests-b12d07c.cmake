add_test( test_create_network /workspaces/cs225/release-f22/BitcoinTrustworthyTransactionProject/code/build/test test_create_network  )
set_tests_properties( test_create_network PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/BitcoinTrustworthyTransactionProject/code/build)
add_test( test_is_valid /workspaces/cs225/release-f22/BitcoinTrustworthyTransactionProject/code/build/test test_is_valid  )
set_tests_properties( test_is_valid PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/BitcoinTrustworthyTransactionProject/code/build)
add_test( test_strongly_connected_components /workspaces/cs225/release-f22/BitcoinTrustworthyTransactionProject/code/build/test test_strongly_connected_components  )
set_tests_properties( test_strongly_connected_components PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/BitcoinTrustworthyTransactionProject/code/build)
add_test( [==[test_dijkstra's - shortest path functions]==] /workspaces/cs225/release-f22/BitcoinTrustworthyTransactionProject/code/build/test [==[test_dijkstra's - shortest path functions]==]  )
set_tests_properties( [==[test_dijkstra's - shortest path functions]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225/release-f22/BitcoinTrustworthyTransactionProject/code/build)
set( test_TESTS test_create_network test_is_valid test_strongly_connected_components [==[test_dijkstra's - shortest path functions]==])
