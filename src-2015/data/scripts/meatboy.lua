physics_center_x  =  20
physics_center_y  =  -30
physics_size_x    = 75
physics_size_y    = 170
density           = 20
physics_can_sleep = false
physics_rotation  = false
is_movable        = true

state = 'fight'
side = 'left'
player = 'meatboy.'
separator = '.'
addanim(player..'fight'..separator..'right.png',430,125)
addanim(player..'fight'..separator..'left.png',430,125)
playanim(player .. 'fight' .. separator .. side .. '.png',false)

function step()
	if state ~= 'fight' then
		if  pos_x < 4000 then
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
