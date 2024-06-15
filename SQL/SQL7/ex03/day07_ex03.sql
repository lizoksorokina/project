with actions as
  (select pi.name, count(pizzeria_id) as total_count
   from person_visits as pv
   join pizzeria pi on pv.pizzeria_id = pi.id
   group by 1
   
   union all 
   
   select pi.name, count(pi.name) as total_count
   from person_order po
   join menu m on po.menu_id = m.id
   join pizzeria pi on m.pizzeria_id = pi.id
   group by 1)

select name, sum(total_count) as total_count
from actions
group by name
order by total_count desc, name asc