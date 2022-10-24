insert into products (
	sku,
	upc,
	name,
	description,
	item_cost,
	listing_price,
	length,
	width,
	height,
	weight,
	is_active
) values (
	'{sku}',
	'{upc}',
	'{name}',
	{description},
	{item_cost},
	{listing_price},
	{length},
	{width},
	{height},
	{weight},
	{is_active}
);
