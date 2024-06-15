select name, rating 
FROM pizzeria
where id not in (select pizzeria_id from person_visits)