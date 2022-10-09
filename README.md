# Feather WMS (Warehouse Management System)
This is a barebones warehouse management system I'm building as a side project. The basic features would be:
* configuring locations and product catalog
* receiving product and storing into a temp staging location
* putaway process to transfer product from temp staging location to pickable location
* orders to generate picks following pick path logic
* shipping containers

Documentation will likely be written during development as it becomes more stable.

# Building from Source
In order to build the project, you must have the PostgreSQL database and the dev package.

For Unix-based systems:
* Postgres: `sudo apt-get install postgresql` 
* PosgreSQL Dev:  `sudo apt-get install -y postgresql-server-dev-all`

Now you can clone this repo with its submodules (includes `libpqxx` dependency for C++ -> PostgreSQL communication):
* `git clone --recursive git@github.com:Kiyoshika/feather-wms`

Then finally build in either `Debug` or `Release` mode:
* `cd feather-wms`
* `mkdir build && cd build`
* `cmake -DCMAKE_BUILD_TYPE=Debug ..`
* `make`

# Building the Database
Before you can get started with development (or usage) you will need to build the database.

Fortunately, the makefile will take care of all of the work for you, you just need to create one superuser named `fwmsadmin` with a pssword.

```text
sudo -i -u postgres

psql

create role fwmsadmin superuser login password 'your_password';

quit;
```

Once you have the admin role set, use the `PGPASSWORD` envinroment variable and run the makefile from the root directory.

```text
export PGPASSWORD=your_password

make newdb
```

This will execute all necessary SQL to construct the database for the first time. You wouldn't need to do this again unless you add additional tables or switch computers.
