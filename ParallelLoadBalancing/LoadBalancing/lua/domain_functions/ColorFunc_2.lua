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

function GeneralFunc_2(values, i, j)

		local tab = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }
	for k = 1, SIZE_BLOCK do
		for l = 1, SIZE_BLOCK do
			if has_value(values, k, l) then
				tab[k][l] = value(values, k, l)			
			end
		end
	end
	
	local res = 0.0
	local max = 0.0
	
	for k = 1, SIZE_BLOCK do
		for l = 1, SIZE_BLOCK do
			max = max + math.abs(tab[k][l])
		end
	end
	
	if max < 10.0 then
		max = 10.0
	end
	
	local maxI = 1 + max % 18
	local count = 1000
	
	if (i % 2 == 0) and (j % 2 == 0) then
		count = count + 10000
	end
	if (i % 3 == 0) and (j % 3 == 0) then
		count = count + 1000
	end
	if (i % 5 == 0) and (j % 5 == 0) then
		count = count + 2000
	end
	
	for k = 2, count * maxI do
		res = res + LIMIT(math.abs(1/4 * i * math.cos(math.sin(tab[1][1]))), 5.0)
		res = res - LIMIT(math.abs(3 * j * math.cos(tab[1][2])), 5.0)
		res = res + 1/14 * math.sin(math.sin(tab[1][3]));
		res = res - 7 * math.cos(math.cos(tab[2][1]));
		res = res - math.sin(math.cos(tab[2][1]));
		res = res + math.cos(tab[2][2]);
		res = res - math.cos(math.sin(tab[3][1])+ k + tab[2][3]);
		res = res + math.sin(tab[3][2]);
		res = res * math.cos(tab[3][3]);	
		
		if SIZE_BLOCK > 3 then
			for l = 4, SIZE_BLOCK do
				for  m = 4, SIZE_BLOCK do
					res = res + math.sin(tab[l][m])
				end
			end
		end
	end
	
	res = math.abs(res);
	local ind = math.ceil(SIZE_BLOCK / 2)
	if res > tab[ind][ind] then
		res = tab[ind][ind]
	end
 
	return res
end

function func(values, i, j)

	local count_elem = 0
	local R_middle = 0
	local G_middle = 0
	local B_middle = 0
	
	local r = 0
	local g = 0
	local b = 0
	
	local r_center = 0
	local g_center = 0
	local b_center = 0
	local koef = 0.1
	
	local ind = math.ceil(SIZE_BLOCK / 2)
	r_center, g_center, b_center = ColorToRGB(value(values,ind,ind))
	
	for k = 1, SIZE_BLOCK do
		for l = 1, SIZE_BLOCK do
			if has_value(values, k, l) then
				r, g, b = ColorToRGB(value(values, k, l))
				R_middle = R_middle - koef * (r_center - r)
				G_middle = G_middle - koef * (g_center - g)
				B_middle = B_middle - koef * (b_center - b)
				count_elem = count_elem + 1
			end
		end
	end
	
	R_middle = R_middle + r_center
	G_middle = G_middle + g_center
	B_middle = B_middle + b_center
	local color_res = RGBToColor(R_middle, G_middle, B_middle)
	
	local sum = 0.0
	local count = color_res
	if count < 1000 then
		count = 1000
	end
	
	if count < 100000 then	
		count = count + 100000
		if (i % 2 == 0) and (j % 2 == 0) then
			count = count * 100
		end
		if (i % 2 == 0) and (j % 2 ~= 0) then
			count = count * 200
		end
		if (i % 2 ~= 0) and (j % 2 ~= 0) then
			count = count * 300
		end
		if (i % 2 ~= 0) and (j % 2 == 0) then
			count = count * 400
		end
	end
	
	for k = 1, count / 1000000 do
		GeneralFunc_2(values, i, j)
	end
 
	return color_res
end