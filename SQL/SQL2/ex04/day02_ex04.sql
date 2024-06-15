SELECT m.pizza_name as pizza_name,p.name as pizzeria_name,  m.price 
FROM menu as m
			inner join pizzeria p on m.pizzeria_id = p.id
where m.pizza_name = 'mushroom pizza' or m.pizza_name = 'pepperoni pizza'
order by pizza_name, pizzeria_name