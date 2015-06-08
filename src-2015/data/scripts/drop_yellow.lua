physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 18
physics_size_y    = 18
physics_can_sleep = true
physics_rotation  = true
damage            = 50
push              = 1.0
range             = 3
density           = 2
speed_x           = 0
speed_y           = 0
last_pos_x        = 0

player = 'drop_yellow.png'


addanim(player,20,100)
playanim(player,false)

initialized = false

function step()

end

function contact(with)
  if with == 'player' then
	son = {"ouille.wav","aieaieaie.wav"}
	playsound(son[math.random(1,2)])
  end 
end

function onAnimEnd()
  playanim(player,false)
end

function onFloor()
	killed = true
end