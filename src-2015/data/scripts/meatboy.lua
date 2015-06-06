physics_center_x  =  20
physics_center_y  =  0
physics_size_x    = 75
physics_size_y    = 200
density           = 2
physics_can_sleep = false
physics_rotation  = false

state = 'fight'
side = 'left'
player = 'meatboy.'
separator = '.'
addanim('meatboy.fight'..separator..'right.png',430)
addanim('meatboy.fight'..separator..'left.png',430)
playanim(player .. 'fight' .. separator .. side .. '.png',false)

function step()
	if state ~= 'fight'  and math.random(0,100) > 30 then -- 70% chance of attacking
		if player_pos_x < pos_x then
			side="left"
			factor = -1
		else
			side="right"
			factor = 1
		end
		state = 'fight'
		playanim(player .. state .. separator .. side .. '.png',false)
		attack('meat.lua',name, side, pos_x + factor * (physics_size_x + 50), pos_y + 50)
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
