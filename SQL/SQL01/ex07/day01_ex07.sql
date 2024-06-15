SELECT po.order_date, 
              p.name || ' (age:' || p.age || ')' AS person_information
FROM person_order as po
		join person as p on p.id = po.person_id
ORDER BY po.order_date, p.name;