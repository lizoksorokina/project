select m.pizza_name, m.price, p.name as pizzeria_name
from menu m 
		left join pizzeria p on p.id  = m.pizzeria_id 
		left join person_order po on m.id = po.menu_id 
where po.person_id is null
order by pizza_name, price