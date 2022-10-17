insert into locations (
    warehouse,
    name,
    aisle,
    bay,
    level,
    picking_flow_int,
    is_pickable,
    is_active
) values (
    '{warehouse}',
    '{name}',
    {aisle},
    {bay},
    {level},
    {picking_flow_int},
    {is_pickable},
    {is_active}
);
