
SELECT name FROM person_order
    JOIN person ON person_id = person.id
    JOIN menu ON menu_id = menu.id
WHERE gender = 'male'
  AND (address = 'Moscow' OR address = 'Samara')
  AND (pizza_name = 'pepperoni pizza' OR pizza_name = 'mushroom pizza')
ORDER BY person.name DESC;

