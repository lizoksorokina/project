SELECT p.name, count(pv.person_id)
FROM person p
		Join person_visits pv on pv.person_id = p.id 
group by p.name
having  count(pv.person_id) > 3
		