create materialized view mv_dmitriy_visits_and_eats as 
		(select p.name AS pizzeria_name
		FROM pizzeria p
			join menu m on p.id  = m.pizzeria_id
			join person_visits pv on p.id = pv.pizzeria_id
			join person p2 on p2.id  = pv.person_id 
		where p2.name = 'Dmitriy' and pv.visit_date = '2022-01-08' and m.price < 800)