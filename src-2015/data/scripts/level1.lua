
-- main platform color
platform = color(255,0,0)
tile(platform, 'vide.png', 0,0,32,32)

-- Table
tile(color(0,0,255), 'table.salle.png', 0,0, 160,140)

-- load tile map
tilemap('map0.png',32,32)

-- add enemies

function init_entities() 
	set_entity("enemy", "salad.lua", 1.5, 100)
	set_attack("life.lua", "", "", 1.58* 1280, 350)
	set_entity("enemy", "tomato.lua", 2.0, 100)
	set_entity("enemy", "meatboy.lua", 2.6, 100)
	set_entity("enemy", "tomato.lua",2.8,100)
	set_entity("enemy", "ketchup.lua", 3.0, 0)
	set_entity("enemy", "mayo.lua", 3.2, 0)
	set_entity("enemy", "ketchup.lua", 3.4, 0)
	set_entity("enemy", "mayo.lua", 3.55, 0)
	set_entity("enemy", "ketchup.lua", 3.7, 0)
	set_attack("life.lua", "", "", 4.38* 1280, 350)
	set_attack("life.lua", "", "", 4.25* 1280, 350)
	set_entity("enemy", "meatboy.lua", 4.5, 100)
	set_entity("enemy", "tomato.lua", 5.7, 100)
	set_entity("enemy", "salad.lua", 5.8, 100)
	set_entity("enemy", "tomato.lua", 5.9, 100)
	set_entity("boss", "maxipain.lua", 8.5* 1280, 250)
end

