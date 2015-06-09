physics_center_x  =  0
physics_center_y  =  0
physics_size_x    = 200
physics_size_y    = 150
density           = 2
physics_can_sleep = false
physics_rotation  = false

state = 'walk'
side = 'left'
player = 'kebab.'
separator = '.'
on_floor = 1
step_index = 0
count = 0
rand = math.random(50,100)
view_range = math.random(200,300)
aggressive_range = math.random(300,400)
addanim(player ..'walk'..separator..'left.png',600,100)
addanim(player ..'walk'..separator..'right.png',600, 100)
addanim(player ..'fight'..separator..'right.png',600, 100)
addanim(player ..'fight'..separator..'left.png',600, 100)
playanim(player .. state .. separator .. side .. '.png',true)

need_to_blow = false
is_falling = false


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
	--print("tql")
	state = 'walk'
	if step_index < 50 then
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
	--print("alert")
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
	--print("agressive")
	if state ~= 'fight'  then
		state = 'fight'
		playanim(player .. state .. separator .. side .. '.png',false)
		set_velocity_y(7.0)
		on_floor = 0
	end
end


function step()
	if math.abs(player_pos_x - (pos_x - physics_size_x))  < 400 then -- factor to add
		if math.random(0,100) > 70 then
			aggressive()
		end
	elseif math.abs(player_pos_x - pos_x) < 500 then
		alert()
	else
		tql()
	end
	if need_to_blow then
		if side == "left" then
			factor = -1
		else
			factor = 1
		end
		attack('blow.lua',name, side, pos_x + factor * (physics_size_x + 50), 100)
		need_to_blow = false
		allowed_to_blow = false
	end
	physics()
end

function contact(with)
	
end

function onFloor()
	on_floor = 1
	-- if player_pos_x < pos_x then
		-- side = "left"
		-- factor = -1
	-- else
		-- side = "right"
		-- factor = 1
	-- end
	-- attack('blow.lua',name, side, pos_x + factor * (physics_size_x + 10), 100)
	if state == 'fight' and is_falling then
		need_to_blow = true
		is_falling = false
	end
	state = 'wait'
end

function onAnimEnd()
  if state == 'fight' then
	stopanim()	
	is_falling = true
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
