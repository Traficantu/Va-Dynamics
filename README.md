## Task for VA Dynamics. 
##### **@Alexandru Mihaila - 09/07/2021**

# General info
- All features have been added: 
    - add individual to contacts
    - remove individual from contacts
    - search for individual in contacts
    - save / load automatically on exit , addition to contacts and startup
    - simple makefile included

Although my knowledge of C++ still has a way to go, I have managed to implement everything *minus* handling parsing input and checking if input is correct. The instructions did not specify this so I decided to not include and assume the user will only input correct data. Having said this, there exists error handling for searching or trying to delete inexistent individuals. 

# Known bugs
- Apart from some further parsing of input, there are no bugs that I am aware of after having tested it myself.


# Side note
-  The address book has been modeled as a singleton to ensure that there is only ever 1 we are adding individuals to and to avoid confusion. 
-  Each individual has a vector of addresses which could in the future have multiple, this was done on purpose as I believe that a individual might have a few addresses stacked on record.
-  Standard OOP approach was taken and classes were as simplified as possible.