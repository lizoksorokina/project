SELECT person.name AS name, pizza_name,price,  TRIM(TRAILING '.' FROM TO_CHAR(menu.price - (menu.price *(person_discounts.discount/100)), 'FM999999990.99')) as discount_price,
pizzeria.name AS pizzeria_name
FROM person
JOIN person_order ON person_order.person_id = person.id
JOIN menu ON person_order.menu_id = menu.id
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
JOIN person_discounts ON person_discounts.person_id = person_order.person_id
ORDER BY name, pizza_name;