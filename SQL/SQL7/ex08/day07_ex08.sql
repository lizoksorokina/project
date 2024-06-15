select p.address, pz.name, count(p.address) as count_of_orders
from person_order po
    join person p on p.id = po.person_id
    join menu m on m.id = po.menu_id
    join pizzeria pz on pz.id = m.pizzeria_id
group by p.address, pz.name
order by p.address;