SQL_DIR = ./sql/build-db
# executes all SQL to build database for first time
# assumes you have "PGPASSWORD" environment variable set
newdb:
	psql -d postgres -U fwmsadmin < ${SQL_DIR}/create_database.sql
	psql -d fwmsprod -U fwmsadmin < ${SQL_DIR}/create_location_table.sql
	psql -d fwmsprod -U fwmsadmin < ${SQL_DIR}/create_products_table.sql
	psql -d fwmsprod -U fwmsadmin -c  'alter default privileges for role fwmsadmin in schema public grant all on tables to fwmsuser'
	
