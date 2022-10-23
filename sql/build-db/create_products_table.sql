drop table if exists products;
create table if not exists products (
	sku varchar(30) not null,
	upc varchar(30) not null,
	name varchar(50) not null,
	description varchar(300),
	item_cost numeric not null,
	listing_price numeric not null,
	length numeric not null,
	width numeric not null,
	height numeric not null,
	weight numeric not null,
	is_active boolean not null,
	unique(sku, upc, name)
);

create index if not exists sku_upc_name on products (
	sku asc,
	upc asc,
	name asc
);



