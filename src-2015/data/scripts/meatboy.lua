physics_center_x  =  20
physics_center_y  =  0
physics_size_x    = 75
physics_size_y    = 200
density           = 2
physics_can_sleep = false
physics_rotation  = false

addanim('meatboy.fight_right.png',430)
addanim('meatboy.fight_left.png',430)

-- define a state variable which can be: 
-- 'wait_left', 'wait_right'
-- 'walk_left', 'walk_right'
-- 'turn_left', 'turn_right'

state = 'fight'
side = '_left'
player = 'meatboy.'
playanim(player .. 'fight' .. side .. '.png',false)

function step()
	if state ~= 'fight'  and math.random(0,100) > 30 then -- 70% chance of attacking
		if player_pos_x < pos_x then
			side="_left"
			factor = -1
		else
			side="_right"
			factor = 1
		end
		state = 'fight'
		playanim(player .. state .. side .. '.png',false)
		attack('meat.lua',name, side, pos_x + factor * physics_size_x, pos_y + 50)
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
