select person_id , count(person_id) as count_of_visits
from person_visits pv
group by person_id
order by count_of_visits desc
