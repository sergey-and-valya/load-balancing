local SIZE_BLOCK = 3

function LIMIT(arr, limit) 
	if arr > limit then
	   return limit
	else
	   return arr
	end
end

function ColorToRGB(color)
	local r = bit32.rshift(bit32.band(color, 0xFF0000), 16)
	local g = bit32.rshift(bit32.band(color, 0x00FF00), 8)
	local b = bit32.band(color, 0x0000FF)
	return r, g, b
end

function RGBToColor(red, green, blue)
	return bit32.bor(bit32.lshift(red, 16), bit32.lshift(green, 8), blue)
end

function GeneralFunc_1(values, i, j)
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
	
	count = 1600
	if (i == 0) or (j == 0) then	
		count = i + j
	else	
		if (i % 2 == 0) or (j % 2 == 0) then
			count = (i + j) / 2
		else
			if (i % 3 == 0) or (j % 3 == 0) then
				count = (i + j) / 3
			else
				if (i % 5 == 0) or (j % 5 == 0) then
					count = (i + j) / 5
				else
					if (i % 10 == 0) or (j % 10 == 0) then
						count = (i + j) / 10
					else
						if i + j <= 1000 then
							count = (i + j)
						else						
							count = (i + j) / 10
						end
					end
				end
			end
		end
	end
							
	count = count + LIMIT(value(values, SIZE_BLOCK / 2, SIZE_BLOCK / 2), 2000.0)
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

function func(values, i, j)

	local count_elem = 0
	local R_middle = 0
	local G_middle = 0
	local B_middle = 0
	
	local r = 0
	local g = 0
	local b = 0
	
	for k = 1, SIZE_BLOCK do
		for l = 1, SIZE_BLOCK do
			if has_value(values, k, l) then
				r, g, b = ColorToRGB(value(values, k, l))
				R_middle = R_middle + r
				G_middle = G_middle + g
				B_middle = B_middle + b
				count_elem = count_elem + 1
			end
		end
	end
	
	R_middle = R_middle / count_elem
	G_middle = G_middle / count_elem
	B_middle = B_middle / count_elem
	local color_res = RGBToColor(R_middle, G_middle, B_middle)
	
	local sum = 0.0
	local count = color_res
	if count < 1000 then
		count = 1000
	end
	
	if count < 100000 then	
		count = count + 100000
		if (i % 2 == 0) and (j % 2 == 0) then
			count = count * 10
		end
		if (i % 2 == 0) and (j % 2 ~= 0) then
			count = count * 20
		end
		if (i % 2 ~= 0) and (j % 2 ~= 0) then
			count = count * 30
		end
		if (i % 2 ~= 0) and (j % 2 == 0) then
			count = count * 40
		end
	end
	
	for k = 1, count / 1000000 do
		GeneralFunc_1(values, i, j)
	end
 
	return color_res
end