SELECT po.order_date as order_date,
              p.name || ' (age:' || p.age || ')' AS person_information
FROM person_order as po (primary_id, id, menu_id, order_date)
    NATURAL JOIN person p 
ORDER BY order_date, person_information;

