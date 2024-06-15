select distinct p.name 
from person p
join person_visits pv on p.id = pv.person_id 
order by p.name;

