addanim('heart.png',100, 50)
playanim('heart.png',false)

physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 30
physics_size_y    = 75
physics_can_sleep = true
physics_rotation  = true
damage            = -50
push              = 1.0
range             = 3
density           = 2
speed_x           = 0
speed_y           = 0
last_pos_x        = 0

player = 'heart.png'


addanim(player,100,50)
playanim(player,false)

initialized = false

function step()

end

function contact(with)
  if with == 'player' then
	playsound("piece.wav")
  end  
end

function onAnimEnd()
  playanim(player,false)
end

function onFloor()
end