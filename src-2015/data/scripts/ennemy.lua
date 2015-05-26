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

state = 'walk'
side = '_left'
player = 'tomate.'
on_floor = 1
step_index = 0
count = 0
rand = math.random(50,100)
view_range = math.random(400,600)
playanim(player .. state .. side .. '.png',true)

function physics()
	-- walk if state is 'walk_*'
	if state == 'walk' then 
		factor = 1
		if side == '_left' then
			factor = -1
		end
		set_velocity_x(factor * 2.0)
	end
end


function tql()
	if step_index < 100 then
		step_index = step_index + 1
		
	else
		step_index = 0 
		if side== '_left' then
			side = '_right'
			playanim(player .. state .. side .. '.png',true)
		else
			side = '_left'
			playanim(player .. state .. side .. '.png',true)
		end
	end		
end


function alert()
	changed = false
	if player_pos_x < pos_x and count > rand then
			changed = side =="_right"
			side ="_left"
			count = 0
		
	elseif count > rand then
		changed = side=="_left"
		side = "_right"
		count = 0
	end
	
	count = count + 1
	
	if changed then
		playanim(player .. state .. side .. '.png',true)
		rand = math.random(50, 100)
	end

end

function step()
	if math.abs(player_pos_x - pos_x) < view_range then
		alert()
	else
		tql()
	end
	physics()
end



function contact(with)
	
end

function onFloor()
	on_floor = 1
end

function onAnimEnd()
  if state == 'fight' then
	state = 'wait'
  end
  if state == 'turn_left' then
    -- state = 'walk_left'
	-- playanim('gripe.run_left.png',true)
  end
  if state == 'turn_right' then
    -- state = 'walk_right'
	-- playanim('gripe.run_right.png',true)
  end
end
