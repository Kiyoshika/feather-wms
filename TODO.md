# TODO Dev List
Things I need to do in no particular order:
* Create a query manager to handle connections and specific transactions to avoid a bunch of boilerplate. Can have a base class which handles the barebones connection setup and subclasses that implement specific transactions (e.g., inserting a location into the database)
* Sanitize inputs on location (warehouse, location name, etc.) to only allow letters and numbers. This is to prevent SQL injection type attacks as right now the data is being directly substituted into the query.