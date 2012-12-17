-- config file template

matrix_file        = "matrix_big"                            -- matrix file
lua_function_file  = "lua/domain_functions/sample1.lua"      -- lua function file

steps          = 10           -- number of system model launches
accuracy       = 6            -- accuracy for load balancing

print_results  = false        -- print results

load_balancing_runs_per_step = 4            -- run load balancing up to 4 times between domain model runs

local Standart = require"Standart"

load_balancing_algorithm = Standart.LoadBalancingAlgorithm.new()
load_balancing_condition = Standart.LoadBalancingCondition.new(load_balancing_runs_per_step)
rebalancer               = Standart.Rebalancer.new()
environment              = Standart.Environment.new(print_results)
domain_model             = Standart.DomainModel.new(matrix_file, Standart.LuaFunction.new(lua_function_file), steps)

if is_root then
    start_time = time()
end

environment:run(comm, domain_model, load_balancing_algorithm, load_balancing_condition, rebalancer)

comm:barrier()

if is_root then
    print("Total time: " .. ((time() - start_time) / 1000))
end