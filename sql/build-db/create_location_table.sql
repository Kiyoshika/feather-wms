create table if not exists locations (
    warehouse varchar(5) not null,
    name varchar(30) not null,
    aisle integer,
    bay integer,
    level integer,
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