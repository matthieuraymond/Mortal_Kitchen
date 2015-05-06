physics_center_x  =  0
physics_center_y  =  0
physics_size_x    = 12
physics_size_y    = 16
physics_can_sleep = false
physics_rotation  = false

addanim('gripe.run_left.png',32)
addanim('gripe.run_right.png',32)
addanim('gripe.turn_left_to_right.png',32)
addanim('gripe.turn_right_to_left.png',32)

playanim('gripe.run_left.png',true)
stopanim()

-- define a state variable which can be: 
-- 'wait_left', 'wait_right'
-- 'walk_left', 'walk_right'
-- 'turn_left', 'turn_right'

state = 'wait_left'

function step()

  -- update state
  if state == 'wait_left' or state == 'wait_right' then
    if Key_q then
	  if state == 'wait_left' then 
	    -- already in the correct orientation, just walk!
	    state = 'walk_left'
	    playanim('gripe.run_left.png',true)
	  else
	    -- uho, need to turn left
	    state = 'turn_left'
	    playanim('gripe.turn_right_to_left.png',false)
	  end
    elseif Key_d then
	  if state == 'wait_right' then 
	    -- already in the correct orientation, just walk!
	    state = 'walk_right'
	    playanim('gripe.run_right.png',true)
	  else
	    -- uho, need to turn right
	    state = 'turn_right'
	    playanim('gripe.turn_left_to_right.png',false)
	  end
	end
  else
    if not Key_q and state == 'walk_left' then
	  state = 'wait_left'
	  stopanim()
    elseif not Key_d and state == 'walk_right' then
	  state = 'wait_right'
	  stopanim()
	end
  end

  if Key_z then
    set_impulse(0.0,6.0)
  end

  -- walk if state is 'walk_*'
  if state == 'walk_left' then
    set_velocity_x(-6.0)
  elseif state == 'walk_right' then
    set_velocity_x(6.0)
  end

end

function contact(with)
  
end

function onAnimEnd()
  if state == 'turn_left' then
    state = 'walk_left'
	playanim('gripe.run_left.png',true)
  end
  if state == 'turn_right' then
    state = 'walk_right'
	playanim('gripe.run_right.png',true)
  end
end
