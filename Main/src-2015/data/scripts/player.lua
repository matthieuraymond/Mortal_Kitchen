right = 'snipe.run_right.png'
left = 'snipe.run_left.png'

addanim(left,32)
addanim(right,32)
initanim(left, true)
initanim(right, true)

function step()

	if Key_d then
		current(right)
		playanim()
		pos_x = pos_x + 16 * elapsed/1000
	elseif Key_q then
		current(left)
		playanim()
		pos_x = pos_x - 16 * elapsed/1000
	else
		stopanim()
	end
end

function contact(with)

end

function onAnimEnd()

end
