# cpp-code-example

This code snippet can read a database from a csv file and answer 2 simple queries.

## Query 1 :

FROM fileName.csv SELECT columnName1,columnName2, ...

In this query the code reads the csv file and then prints the data selected in the query onto the Terminal.

## Query 2 :

FROM fileName.csv SELECT columnName1,columnName2,... TAKE numberOfRecordesNeeded

In this query the code reads the csv file and then prints onlt the first  numberOfRecordesNeeded records of the data selected in the query onto the Terminal.

## Code Explanation : 

### Struct Database

This structure stores the database information. It has a title vector which stores the column names and the records vector stores all the records.

### Function from : 

This function transforms the csv into the database structure and returns it to the caller.

### Function select : 

This function takes the database as an arguement and removes all the unnecessary columns and returns a new database with only the selected columns.

### Function take :

This function only keeps the first "count" number of records in the database passed to it and returns the new database.


### Function print_database:

This function prints the database passed to it onto the terminal.

### Function remove_quotes & splitby:

These functions are needed to preprocess the user's input query.


