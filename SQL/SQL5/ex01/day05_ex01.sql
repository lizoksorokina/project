SET enable_seqscan to off;

EXPLAIN ANALYZE
select m.pizza_name, name AS pizzeria_name
FROM menu m
    JOIN pizzeria p ON m.pizzeria_id = p.id;