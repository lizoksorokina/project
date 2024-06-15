CREATE UNIQUE INDEX IF NOT EXISTS  idx_person_discounts_unique on person_discounts(person_id, pizzeria_id);
	
SET enable_seqscan = off;

EXPLAIN ANALYSE 
SELECT *
FROM  person_discounts
--DROP INDEX idx_person_discounts_unique
