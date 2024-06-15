WITH FEM AS (
    SELECT DISTINCT pizzeria.name AS pizzeria_name
    FROM pizzeria
        JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id
        JOIN person_order ON person_order.person_id = person_visits.person_id
        JOIN menu ON menu.id = person_order.menu_id
        AND person_visits.pizzeria_id = menu.pizzeria_id
        JOIN person ON gender = 'female'
        AND person.id = person_order.person_id
    ORDER BY pizzeria_name
),
MALE AS (
    SELECT DISTINCT pizzeria.name AS pizzeria_name
    FROM pizzeria
        JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id
        JOIN person_order ON person_order.person_id = person_visits.person_id
        JOIN menu ON menu.id = person_order.menu_id
        AND person_visits.pizzeria_id = menu.pizzeria_id
        JOIN person ON gender = 'male'
        AND person.id = person_order.person_id
    ORDER BY pizzeria_name
) (
    SELECT pizzeria_name
    FROM FEM
    EXCEPT
    SELECT pizzeria_name
    FROM MALE
)
UNION
(
    SELECT pizzeria_name
    FROM MALE
    EXCEPT
    SELECT pizzeria_name
    FROM FEM
)
ORDER BY pizzeria_name