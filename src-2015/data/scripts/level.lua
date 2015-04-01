

-- main platform color
platform = color(255,0,0)
tile(platform, 'area01_level_tiles.png', 16,32, 16,16 )
lborder = color(128,0,0)
tile(lborder, 'area01_level_tiles.png', 48,0, 16,16 )
rborder = color(196,0,0)
tile(rborder, 'area01_level_tiles.png', 64,0, 16,16 )

-- sign
tile(color(0,0,255), 'area01_level_tiles.png', 176,0, 32,32 )

-- load background image
background('background.jpg')

-- load tile map
tilemap('map0.png',16,16)

-- automatically add borders
for j=0,num_tiles_y()-1 do
  for i=0,num_tiles_x()-1 do
    if tileat(i,j) == platform and tileat(i+1,j) == color(0,0,0) then
	  set_tileat(i,j,rborder)
	end
    if tileat(i,j) == platform and tileat(i-1,j) == color(0,0,0) then
	  set_tileat(i,j,lborder)
	end
  end
end
