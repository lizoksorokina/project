select p.name as person_name, m.pizza_name as pizza_name, pz.name as pizzeria_name
FROM person as p
		join person_order po on p.id = po.person_id
		join menu m on m.id = po.menu_id
		join pizzeria pz on pz.id = m.pizzeria_id
ORDER BY person_name, pizza_name, pizzeria_name
	