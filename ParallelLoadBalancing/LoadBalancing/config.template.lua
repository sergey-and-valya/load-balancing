-- config file template

local standart = require"Standart"

load_balancing_algorithm = standart.LoadBalancingAlgorithm.new(6)
rebalancer               = standart.Rebalancer.new()
environment              = standart.Environment.new(true, false)

matrix_file    = "matrix_big" -- used matrix file (default matrix_big)

steps          = 10           -- number of system model launches
world_size     = 4            -- number of emulated processors

unit_tests     = false        -- turn on/off unit test

--TODO: use logging