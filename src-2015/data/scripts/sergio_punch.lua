physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 10
physics_size_y    = 10
physics_can_sleep = true
physics_rotation  = true
damage            = 50
push              = 15.0
density           = 0
range             = 100*0.8 -- 100 for px to m (0.05 is in m)
speed_x           = 6.5
speed_y           = 1
gone_through      = 0
last_pos_x        = 0


addanim('void.png',10,100)
playanim('void.png',false)

initialized = false

function step()
	if not initialized then
		last_pos_x = pos_x
		initialized = true
	end
	gone_through = gone_through + math.abs(last_pos_x - pos_x)
	last_pos_x = pos_x
	if gone_through > range then
		killed = true
	end
end

function contact(with)

end

function onAnimEnd()
  playanim('void.png',false)
end

function onFloor()
	killed = true
end