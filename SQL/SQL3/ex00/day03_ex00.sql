SELECT m.pizza_name, m.price, pz.name as pizzeria_name, pv.visit_date  as visit_date
FROM menu m
	join pizzeria pz on m.pizzeria_id  = pz.id
	join person_visits pv on pv.pizzeria_id = pz.id 
	join person p on p.id = pv.person_id 
where p.name = 'Kate' and m.price between 800 and 1000
order by pizza_name, price, pizzeria_name