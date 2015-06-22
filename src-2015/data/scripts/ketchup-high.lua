physics_center_x  =  0
physics_center_y  =  0
physics_size_x    = 20
physics_size_y    = 25
density           = 0.1
physics_can_sleep = false
physics_rotation  = false
is_movable        = true

player = 'ketchup'
separator = '.'
addanim(player..'.png',80,250)
playanim(player .. '.png',false)

function step()
	set_y(730)
	set_x(x_init)
	if state ~= 'fight' then 
		state = 'fight'
		playanim(player .. '.png',false)
		attack('drop.lua',name, "left", pos_x + 2*physics_size_x, 680)
	end
end

function contact(with)

end

function onFloor()

end

function onAnimEnd()
  if state == 'fight' then
	state = 'wait'
  end
end
