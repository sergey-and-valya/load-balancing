-- config file template

matrix_file        = "matrix_big"                            -- matrix file
lua_function_file  = "lua/domain_functions/sample1.lua"      -- lua function file

steps          = 10           -- number of system model launche
accuracy       = 6            -- accuracy for load balancing

load_balancing = true         -- use load balancing or not
print_results  = false        -- print results


local Standart = require"Standart"

load_balancing_algorithm = Standart.LoadBalancingAlgorithm.new()
rebalancer               = Standart.Rebalancer.new()
environment              = Standart.Environment.new(load_balancing, print_results)
domain_model             = Standart.DomainModel.new(matrix_file, Standart.LuaFunction.new(lua_function_file), steps)

if is_root then
    start_time = time()
end

environment:run(comm, domain_model, load_balancing_algorithm, rebalancer)

comm:barrier()

if is_root then
    print("Total time: " .. ((time() - start_time) / 1000))
end