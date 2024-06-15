SELECT distinct
    po.order_date AS action_date, 
    p.name AS person_name
FROM 
    person_order AS po
JOIN 
    person_visits AS pv ON pv.visit_date = po.order_date
JOIN 
    person AS p ON p.id = po.person_id
ORDER BY 
    action_date, 
    person_name DESC;

 