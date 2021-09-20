# Construct a K-D tree and parse through it.

**Version 1.0.0**

An Extension of the Dictionaries made from linked list https://github.com/Justin-Chen1010/Dictionary-Linked-List

**How you would call the program:**

```
dict datafile outputfile < queryfile
```
We can insert the coordinates of the place that we want to find for example we would put in the queryfile 

```
144.959522 -37.800095
```

The program will first parse through the file then recursively insert into the kdtree. After inserting the data, it will recursively iterate through the tree to make queries, and return the all of the information at that coordinate for example if we were to pick a spot in a mall we would find, it would also print to stdout the amount of key comparisons that were done to complete the search:

**Example Output to stdout:**
```
144.959522 -37.800095 -- > 4815
```

**Example Output to file:**

```

144.959522 -37.800095 --> Census year: 2018 || Block ID: 240 || Property ID: 104466 || Base
property ID: 104466 || CLUE small area: Carlton || Trading Name: The Bio 21 Cluster || Industry (ANZSIC4)
code: 6910 || Industry (ANZSIC4) description: Scientific Research Services || x coordinate: 144.9593
|| y coordinate: -37.8002 || Location: (-37.80023252, 144.9592806) ||

144.959522 -37.800095 --> Census year: 2018 || Block ID: 240 || Property ID: 104466 || Base
property ID: 104466 || CLUE small area: Carlton || Trading Name: The Co-Op Bookstore || Industry (ANZSIC4)
code: 4244 || Industry (ANZSIC4) description: Newspaper and Book Retailing || x coordinate: 144.9593
|| y coordinate: -37.8002 || Location: (-37.80023252, 144.9592806) ||

144.959522 -37.800095 --> Census year: 2018 || Block ID: 240 || Property ID: 104466 || Base
property ID: 104466 || CLUE small area: Carlton || Trading Name: Baretto Cafe || Industry (ANZSIC4)
code: 4511 || Industry (ANZSIC4) description: Cafes and Restaurants || x coordinate: 144.9593 || y
coordinate: -37.8002 || Location: (-37.80023252, 144.9592806) ||

```