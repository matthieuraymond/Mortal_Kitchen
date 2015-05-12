physics_center_x  =  0
physics_center_y  =  0
physics_size_x    = 25
physics_size_y    = 75
physics_can_sleep = false
physics_rotation  = false

addanim('tomate.walk_left.png',64)
addanim('tomate.walk_right.png',64)
addanim('tomate.fight_right.png',100)
addanim('tomate.fight_left.png',100)

playanim('tomate.walk_left.png',true)
stopanim()

-- define a state variable which can be: 
-- 'wait_left', 'wait_right'
-- 'walk_left', 'walk_right'
-- 'turn_left', 'turn_right'

state = 'wait'
side = '_left'
player = 'tomate.'
on_floor = 1

function step()

	if state == 'wait' then
		if Key_q then
			state = 'walk'
			side = '_left'
			playanim(player .. state .. side .. '.png',true)
		elseif Key_d then
			state = 'walk'
			side = '_right'
			playanim(player .. state .. side .. '.png',true)
		end
		if Key_e and on_floor == 1 then
			state = 'fight'
			playanim(player .. state .. side .. '.png',false)
		end 
	end
	
	
	-- reset states
	if state == 'walk' and not Key_q and not Key_d then
		state = 'wait'
		stopanim()
	end
	
	--if state == 'fight' and not Key_e then
	--	state = 'wait'

	--	stopanim()
	--end

	if Key_z and on_floor == 1 then
		set_velocity_y(10.0)
		on_floor = 0
	end

	-- walk if state is 'walk_*'
	if state == 'walk' then 
		factor = 1
		if side == '_left' then
			factor = -1
		end
		set_velocity_x(factor * 12.0)
	end
end

function contact(with)
	
end

function onFloor()
	on_floor = 1
end

function onAnimEnd()
  if state == 'turn_left' then
    -- state = 'walk_left'
	-- playanim('gripe.run_left.png',true)
  end
  if state == 'turn_right' then
    -- state = 'walk_right'
	-- playanim('gripe.run_right.png',true)
  end
  if state == 'fight' then
    state = 'wait'
  end
end
