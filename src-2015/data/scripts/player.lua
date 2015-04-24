right = 'tomate.walk_right.png'
left = 'tomate.walk_left.png'
fight_right = 'tomate.fight_right.png'
fight_left = 'tomate.fight_left.png'

addanim(left,64)
addanim(right,64)
addanim(fight_left,100)
addanim(fight_right,100)
initanim(left, true)
initanim(fight_left, true)
initanim(right, true)
initanim(fight_right, true)

current(right);

function step()
	if Key_d then
		current(right)
		playanim()
		pos_x = pos_x + 32 * elapsed/1000
	elseif Key_q then
		current(left)
		playanim()
		pos_x = pos_x - 32 * elapsed/1000
	elseif Key_e then
		if (get_current() == left) or (get_current() == fight_left) then
			if(get_current() == left) then
				pos_x = pos_x - 32
			end
			current(fight_left)
		else
			current(fight_right)
		end
		playanim()
	else
		stopanim()
	end
end

function contact(with)

end

function onAnimEnd()

end
