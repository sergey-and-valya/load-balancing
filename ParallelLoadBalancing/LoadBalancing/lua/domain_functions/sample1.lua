local SIZE_BLOCK = 3

function LIMIT(arr, limit) 
	if arr > limit then
	   return limit
	else
	   return arr
	end
end

function func(values, i, j)
	local sum = 0.0
	local coef =
	{
		{
			1 / 4  * (i - 1) * (i - 2) * (j - 1) * (j - 2) * (j + 1),
			-1 / 4  * i * (i + 1) * (i - 2) * (j - 1) * (j - 2) * (j + 1),
			-1 / 4  * j * (i - 1) * (i - 2) * (i + 1) * (j + 1) * (j - 2)
		},
		{
			-1 / 12 * i * (i - 1) * (i - 2) * (j - 1) * (j - 2) * (j + 1),
			-1 / 12 * j * (i - 1) * (i - 2) * (i + 1) * (j - 1) * (j - 2),
			 1 / 36 * i * j * (i - 1) * (i - 2) * (j - 1) * (j + 2)
		},
		{
			 -1 / 36 * i * j * (i - 1) * (i - 2) * (j - 1) * (j + 1),
			  1 / 12 * i * j * (i - 1) * (i - 2) * (j + 1) * (j - 2),
			 -1 / 12 * i * j * (i + 1) * (i - 2) * (j - 1) * (j + 1)
		}
	}
		
	count_elem = 0
	for k = 1, SIZE_BLOCK do
		for l = 1, SIZE_BLOCK do
			if has_value(values, k, l) then
				count_elem = count_elem + 1						
			end
		end
	end
	
	count = 1 + (LIMIT(value(values, SIZE_BLOCK / 2, SIZE_BLOCK / 2) / 2.0, 1.0)) * 3
	
	for m = 1, count do
		for k = 1, SIZE_BLOCK do
			for l = 1, SIZE_BLOCK do
				if has_value(values, k, l) then
					local val = value(values, k, l)
					sum = sum + math.abs(math.cos(coef[k][l] * math.tanh(math.sin(math.pi * LIMIT(val, 10.0))) + math.sinh(LIMIT(val, 10.0)) + math.cosh(LIMIT(val, 10.0)) + math.tanh(LIMIT(LIMIT(math.pi * val, 10.0), 10))))
				end
			end
		end
	end
 
	return sum / count_elem
end