SQL_DIR = ./sql/build-db
# executes all SQL to build database for first time
# assumes you have "PGPASSWORD" environment variable set
newdb:
	psql -d postgres -U fwmsadmin < ${SQL_DIR}/create_database.sql
	psql -d fwmsprod -U fwmsadmin < ${SQL_DIR}/create_location_table.sql
	