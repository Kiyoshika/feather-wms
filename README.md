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

Fortunately, the makefile will take care of all of the work for you, just create one superuser named `fwmsadmin` with a pssword and a regular user 'fwmsuser'.

You will also have to change the authentication method from "peer" to "md5".

**NOTE**: Currently the client password is hardcoded as "sample" in `QueryManager.hpp` - ideally this should be read from a file but for now this is fine.

```text
sudo -i -u postgres

psql

create role fwmsadmin superuser login password 'admin_password';

create role fwmsuser login password 'sample'; /* this will be the account used by the client for SELECT/INSERTs */

show hba_file; /* this will give you a directory to use in next step */

quit;
```

After you create the roles above and obtain the hba file path, open it in a text editor (with sudo) and scroll down to the bottom. You'll need to change all "peer" connections to  "md5" **EXCEPT THE "postgres" ROLE, LEAVE THAT AS PEER**.

Next, use `sudo service postgresql restart` to restart the postgres server and reload the config.

Finally, set the `PGPASSWORD` envinroment variable to the password you set for `fwmsadmin` and run the makefile from the root directory.

```text
export PGPASSWORD=admin_password

make newdb
```

This will execute all necessary SQL to construct the database for the first time. You wouldn't need to do this again unless you add/modify tables or switch computers.
