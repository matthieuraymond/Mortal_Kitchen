physics_center_x  =  0
physics_center_y  =  0
physics_size_x    = 20
physics_size_y    = 25
density           = 0.1
physics_can_sleep = false
physics_rotation  = false

player = 'mayo'
separator = '.'
addanim(player..'.png',80,150)
playanim(player .. '.png',false)

function step()
	set_y(550)
	if state ~= 'fight' then 
		state = 'fight'
		playanim(player .. '.png',false)
		attack('drop_yellow.lua',name, "left", pos_x + 2*physics_size_x, 500)
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
