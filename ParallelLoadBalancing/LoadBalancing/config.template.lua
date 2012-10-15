-- config file template

local Standart = require"Standart"

load_balancing_algorithm = Standart.LoadBalancingAlgorithm.new(6)
rebalancer               = Standart.Rebalancer.new()
environment              = Standart.Environment.new(true, false)
domain_model             = Standart.DomainModel.new("matrix_big", Standart.LuaFunction.new("lua/domain_functions/sample1.lua"), 10)

world_size     = 4            -- number of emulated processors

unit_tests     = false        -- turn on/off unit test

--TODO: use logging