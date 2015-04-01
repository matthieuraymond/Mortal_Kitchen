
-- main platform color
platform = color(255,0,0)
tile(platform, 'area01_level_tiles.png', 16,32, 16,16 )
lborder = color(128,0,0)
tile(lborder, 'area01_level_tiles.png', 48,0, 16,16 )
rborder = color(196,0,0)
tile(rborder, 'area01_level_tiles.png', 64,0, 16,16 )
bborder = color(64,0,0)
tile(bborder, 'area01_level_tiles.png', 56,32,16,16)
blborder = color(32,0,0)
tile(blborder, 'area01_level_tiles.png', 48,32,16,16)
brborder = color(16,0,0)
tile(brborder, 'area01_level_tiles.png', 64,32,16,16)

-- sign
sign = color(0,0,255)
tile(sign, 'area01_level_tiles.png', 176,0, 32,32 )

-- spike
spike = color(0,255,0)
tile(spike, 'area01_level_tiles.png', 176,64,16,32) 

-- load tile map
tilemap('map0.png',16,16)

-- automatically add borders
for j = 0, num_tiles_y()-1 do
for i = 0, num_tiles_x()-1 do
	if tileat(i,j) == platform and tileat(i+1,j) == color(255,255,255) then
		set_tileat(i,j,rborder)
	end
	if tileat(i,j) == platform and tileat(i-1,j) == color(255,255,255) then
		set_tileat(i,j,lborder)
	end
	if tileat(i,j) == platform and tileat(i,j-1) == color(255,255,255) and tileat(i,j-2) == color(255,255,255) then
		set_tileat(i,j-1,bborder)
	end
	if tileat(i,j) == rborder and tileat(i,j-1) == color(255,255,255) and tileat(i,j-2) == color(255,255,255) then
		set_tileat(i,j-1,brborder)
	end 
	if tileat(i,j) == lborder and tileat(i,j-1) == color(255,255,255) and tileat(i,j-2) == color(255,255,255) then
		set_tileat(i,j-1,blborder)
	end 
	
end
end