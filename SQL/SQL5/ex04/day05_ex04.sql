create index idx_menu_unique on menu(pizzeria_id, pizza_name);

SET enable_seqscan to off;

EXPLAIN analyze
select *
from menu 
where pizza_name = 'cheese pizza'and pizza_name = 'pepperoni pizza'