select pz.name, count(pz.id) as count_of_orders,  round(avg(price), 2) as average_price, 
                     max(price) as max_price, min(price) as min_price
from person_order
    join menu on menu.id = person_order.menu_id
    join pizzeria pz on pz.id = menu.pizzeria_id
group by pz.name
order by pz.name;
