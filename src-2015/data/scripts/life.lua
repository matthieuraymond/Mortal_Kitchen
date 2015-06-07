physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 30
physics_size_y    = 75
density           = 2.0
physics_can_sleep = true
physics_rotation  = false

addanim('heart.png',100, 50)
playanim('heart.png',false)

function step()

end

function contact(with)
  -- print('coin contact with ' .. with)
  if with == 'player' then
    killed = true
	player_life = player_life + 1000
	playsound("piece.wav")
  end  
end

function onAnimEnd()
  playanim('heart.png',false)
end

function onFloor()

end