WITH FEM AS (
    SELECT pizzeria.name AS pizzeria_name
    FROM pizzeria
        JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id
        JOIN person ON gender = 'female'
        AND person.id = person_visits.person_id
    ORDER BY pizzeria_name
),
MALE AS (
    SELECT pizzeria.name AS pizzeria_name
    FROM pizzeria
        JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id
        JOIN person ON gender = 'male'
        AND person.id = person_visits.person_id
    ORDER BY pizzeria_name
) (
    SELECT pizzeria_name
    FROM FEM
    EXCEPT ALL
    SELECT pizzeria_name
    FROM MALE
)
UNION ALL
(
    SELECT pizzeria_name
    FROM MALE
    EXCEPT ALL
    SELECT pizzeria_name
    FROM FEM
)
ORDER BY pizzeria_name