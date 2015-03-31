addanim('spinning_coin_gold.png',16)
initanim('spinning_coin_gold.png', true)
playanim()

function step()
	-- print('step entity' .. name)
	if name == "coin1" then
		--pos_x = pos_x + 16*elapsed/1000
	end
	if name == "coin4" then
		-- pos_x = pos_x - 16*elapsed/1000
	end
end

function contact(with)
	if with == "player" then
		killed = true
	end
end

function onAnimEnd()
end
