-- config file template

matrix_file    = "matrix_big" -- used matrix file (default matrix_big)

steps          = 10           -- number of system model launches
world_size     = 4            -- number of emulated processors
accuracy       = 6            -- accuracy for load balancing

load_balancing = false        -- use load balancing or not
print_results  = false        -- print results
unit_tests     = false        -- turn on/off unit test

--TODO: use logging