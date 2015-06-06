physics_center_x  =  0
physics_center_y  =  0
physics_size_x    = 35
physics_size_y    = 125
density           = 2
physics_can_sleep = false
physics_rotation  = false

state = 'walk'
side = 'left'
player = 'tomate.'
separator = '.'
on_floor = 1
step_index = 0
count = 0
rand = math.random(50,100)
view_range = math.random(200,300)
aggressive_range = math.random(100,200)
addanim(player ..'walk'..separator..'left.png',256)
addanim(player ..'walk'..separator..'right.png',256)
addanim(player ..'fight'..separator..'right.png',256)
addanim(player ..'fight'..separator..'left.png',256)
playanim(player .. state .. separator .. side .. '.png',true)


function physics()

	factor = 1
	if side == 'left' then
		factor = -1
	end
	
	if state == 'walk' then 
		set_velocity_x(factor * 2.0)
	end
	
end


function tql()
	if step_index < 100 then
		step_index = step_index + 1
		
	else
		step_index = 0 
		if side== 'left' then
			side = 'right'
			playanim(player .. state .. separator .. side .. '.png',true)
		else
			side = 'left'
			playanim(player .. state .. separator .. side .. '.png',true)
		end
	end		
end


function alert()
	changed = false
	state = 'walk'
	if player_pos_x < pos_x and count > rand then
			changed = side =="right"
			side ="left"
			count = 0
		
	elseif count > rand then
		changed = side=="left"
		side = "right"
		count = 0
	end
	
	count = count + 1
	
	if changed then
		playanim(player .. state .. separator .. side .. '.png',true)
		rand = math.random(50, 100)
	end

end

function aggressive()
	if state ~= 'fight'  and math.random(0,100) > 50 then -- 50% chance of attacking
		if player_pos_x < pos_x then
			side="left"
		else
			side="right"
		end
		state = 'fight'
		playanim(player .. state .. separator .. side .. '.png',false)
		attack('punch.lua',name, side, pos_x + factor * physics_size_x, pos_y + 60)
	end
end


function step()
	if math.abs(player_pos_x - pos_x) < aggressive_range then
		aggressive_range = math.random(100,200)
		aggressive()
	elseif math.abs(player_pos_x - pos_x) < view_range then
		view_range = math.random(200,300)
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
