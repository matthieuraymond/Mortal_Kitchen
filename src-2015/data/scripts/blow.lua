physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 17
physics_size_y    = 50
physics_can_sleep = true
physics_rotation  = false
damage            = 50
push              = 1.0
range             = 100* 5.0 -- 100 for px to m (0.05 is in m)
density           = 2
speed_x           = 6
speed_y           = 0
last_pos_x        = 0
gone_through      = 0


addanim('blow.png',17,100)
playanim('blow.png',false)

initialized = false

function step()
	if initialized and (last_pos_x - pos_x) ~= 0 then
		if last_pos_x - pos_x < 0 then
			sign = 1
		else 
			sign = -1
		end
			set_velocity_x(sign * speed_x)
	elseif not(initialized) then
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
  if with == 'player' then
	son = {"ouille.wav","aieaieaie.wav"}
	playsound(son[math.random(1,2)])
  end 
end

function onAnimEnd()
  playanim('blow.png',false)
end

function onFloor()

end
