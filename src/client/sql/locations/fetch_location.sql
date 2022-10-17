select
	warehouse,
	name,
	aisle,
	bay,
	level,
	is_pickable,
	is_active
from
	locations
where
	warehouse = '{warehouse}'
and name = '{name}';
