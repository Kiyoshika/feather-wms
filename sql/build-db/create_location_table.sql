drop table if exists locations;
create table if not exists locations (
    warehouse varchar(5) not null,
    name varchar(30) not null,
    aisle integer,
    bay integer,
    level integer,
    picking_flow_int integer,
    is_pickable boolean not null,
    is_active boolean not null
);

create index if not exists warehouse on locations (
    warehouse asc
);

create index if not exists warehouse_location on locations (
    warehouse asc,
    name asc
);

create index if not exists pick_flow on locations (
    picking_flow_int asc
);

create index if not exists warehouse_pick_flow on locations (
    warehouse asc,
    picking_flow_int asc
);