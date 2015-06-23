
-- main platform color
platform = color(255,0,0)
tile(platform, 'vide.png', 0,0,32,32)

-- Table
tile(color(0,0,255), 'frigo.png', 0,0, 196,292)
tile(color(0,255,255), 'etagere1.png', 0,0, 196,56)
tile(color(255,255,255), 'table.salle.png', 0,0, 160,140)

-- load tile map
tilemap('map2.png',32,32)

-- add enemies

function init_entities() 

	set_entity("enemy", "ketchup.lua", 0.8, 0)
	set_entity("enemy", "meatboy.lua", 1.2, 100)

	set_entity("enemy", "ketchup-high.lua", 2.1, 0)
	set_entity("enemy", "mayo-high.lua", 2.5, 0)
	set_entity("enemy", "ketchup-high.lua", 2.85, 0)
	
	set_entity("enemy", "tomato.lua", 2.0, 0)
	set_entity("enemy", "salad.lua", 2.2, 0)
	set_entity("enemy", "oignon.lua", 2.35, 0)
	set_entity("enemy", "tomato.lua", 2.6, 0)
	set_entity("enemy", "oignon.lua", 2.8, 0)
	set_entity("enemy", "tomato.lua", 3.0, 0)
	set_entity("enemy", "salad.lua", 3.2, 0)
end

