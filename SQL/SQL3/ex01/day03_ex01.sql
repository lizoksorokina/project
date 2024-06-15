SELECT m.id AS menu_id
FROM menu m
LEFT JOIN person_order po ON po.menu_id = m.id
WHERE po.menu_id IS NULL
ORDER BY m.id;