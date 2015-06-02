physics_center_x  = 0
physics_center_y  = 0
physics_size_x    = 10
physics_size_y    = 10
physics_can_sleep = true
physics_rotation  = true
damage            = 25
range             = 3
density           = 0

addanim('void.png',10)
playanim('void.png',false)

function step()

end

function contact(with)

end

function onAnimEnd()
  playanim('void.png',false)
end

function onFloor()

end