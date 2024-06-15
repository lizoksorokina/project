with visits as (select pi.name,
                       count(pizzeria_id),
                       'visit' as action_type
                from person_visits as pv
                         join pizzeria pi on pv.pizzeria_id = pi.id
                group by pi.name
                order by count desc
                limit 3),
                
     orders as (select pi.name,
                       count(pi.name),
                       'order' as action_type
                from person_order po
                         join menu m on po.menu_id = m.id
                         join pizzeria pi on m.pizzeria_id = pi.id
                group by pi.name
                order by count desc
                limit 3)
				
select name, count, action_type
from visits
union all
select name, count, action_type
from orders
order by action_type asc, count desc;