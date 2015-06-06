physics_center_x  =  0
physics_center_y  =  0
physics_size_x    = 35
physics_size_y    = 120
density           = 5
physics_can_sleep = false
physics_rotation  = false

-- define a state variable which can be: 
-- 'wait_left', 'wait_right'
-- 'walk_left', 'walk_right'
-- 'turn_left', 'turn_right'

state = 'wait'
side = 'left'
player = 'sergio.'
separator = '.'
on_floor = true

addanim(player .. 'walk'..separator..'left.png',256)
addanim(player .. 'walk'..separator..'right.png',256)
addanim(player .. 'fight'..separator..'right.png',256)
addanim(player .. 'fight'..separator..'left.png',256)

playanim(player .. 'walk'..separator..'left.png',true)
stopanim()

function step()

	if state == 'wait' then
		if Key_q then
			state = 'walk'
			side = 'left'
			playanim(player .. state .. separator .. side .. '.png',true)
		elseif Key_d then
			state = 'walk'
			side = 'right'
			playanim(player .. state .. separator .. side .. '.png',true)
		end
		if Key_e and on_floor then
			state = 'fight'
			playsound("pipou.wav")
			playanim(player .. state .. separator .. side .. '.png',false)
			
			-- attack
			coef = 1
			if side == "left" then
				coef = -1
			end
			attack('punch.lua',name, side, pos_x + coef * physics_size_x, pos_y + 60)
		end 
	end
	
	
	-- reset states
	if state == 'walk' and not Key_q and not Key_d then
		state = 'wait'
		stopanim()
	end

	if Key_z and on_floor then
		set_velocity_y(6.0)
		on_floor = false
		-- play jump anim not a loop
		playsound("boing.wav")
	end

	-- walk if state is 'walk_*'
	if state == 'walk' then 
		factor = 1
		if side == 'left' then
			factor = -1
		end
		set_velocity_x(factor * 2.2)
	end
end

function contact(with)
	
end

function onFloor()
	on_floor = true
end

function onAnimEnd()
  if state == 'fight' then
	state = 'wait'
  end
  if state == 'jumping' and on_floor then
    state = 'wait'
  end
end
