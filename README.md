# InMemoryDb
 Implementation of a small in memory database that can perform CRUD operations.

## How to build
There is a .bat (**build_windows.bat**) file which could be used to build the application for Windows. Before starting this .bat file, make sure to do the necessary changes as per your environment. Open the .bat file with your favorite text editor. You will see the following comment:<br/>
*REM Change this to the correct Visual Studio version*<br/>
Here you need to specify the version of Visual Studio that you have and are planning to use. On my side I have Visual Studio 2019 so I am using: **Visual Studio 16 2019**. If you have a different version, change the line after the comment. <br/>
Next thing you need to change is the second comment:<br/>
*REM Change this to the appropriate directory* <br/>
Here you should provide the path to the MSBuild.exe application. If you are using Visual Studio 2019 Community, chances are high that you might not have to change anything. If not, change with the appropriate path. <br/><br/>
After the changes are done, run the .bat file. It will build the application first. Then it will build the unit tests. When building the unit tests, it will get the required version of GoogleTest.

## What does the application do?
The application demonstrates the work of the InMemoryDb class, which provides operations on in-memory database. While demonstrating this, it also executes performance tests in order to verify the work of the class. <br/>
First of all it will compare the performance of the Find Matching Records algorithm against the original one. The tests are performed on 1000000 records. There are two cases - In the first case the algorithm shall be able to find only one matching record. In the second case it shall find 1000000 matching records. This case measures the performance of getting all the 1000000 records. <br/>
The second performance measurement is on the Remove Record algorithm.<br/>
The third performance measurement is on the Add New Record functionality.

## What does each algorithm do?
The main part of this task - the algorithms for database operations are found in the InMemoryDb class. The other classes are just helper classes used for the performance measurements. There are three algorithms implemented.

### Find Matching Record
With this operation, the user is able to search for records, matching a given pattern. The algorithm is an updated and more optimized version of the original algorithm. It does the operations in the same logic but in more optimized way. Basically, it goes trough all the available records, checks if the given string matches the data in the select column and if so, it gets a reference (pointer) to the selected record. <br/>
Two versions are available. The first one is more optimized (On my PC it is able to process 1000000 records in 150ms), but it is also very specific for the given table and if a new table is to be added, some significant changes will be required. The second version is able to process 1000000 records in 300ms. However, it is more generic and can easily be updated with new data. For comparison, the original algorithm takes ~7 seconds to process all the records.

### Remove Record By Id
This function searches for a record with a given ID (keep in mind that the IDs are unique) and if it finds it, that record is set to default values. Its ID is set to 0, which marks it as deleted record. All such records are kept as a reference so when a new record is to be added, it will be directly placed in the place of such deleted record. This one saves a lot of time, because deleting a record from a vector will require shifting of the rest of the records and this one is not a cheap operation. 

### Add New Record
When adding a new record, the algorithm first checks if we have records, marked as deleted so it will place the new record in their place. If no such place is available, it will place it at the end of the vector. The reason behind this is that when you need to add a new record at the end, it might require reallocation of memory which is not a cheap operation. By reusing the places of old deleted records, we save from unnecessary reallocation.