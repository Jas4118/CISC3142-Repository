<h1 align="center">Lab 1 - Reading Data with C++</h1>

<p> This is Lab 1 for CISC. 3142. This program will read all of the lines on input from the CSV file and write to an output file with certain information. Along with printing all of the information, it the program calculates the average price per brand and average price per category. Furthermore, for each year, the program prints the number of SKU's and the list of SKU's themselves.</p>

<h2 align="center">Explanation of the Problem</h2>

<p>The program must read all of the files from the CSV file and output the data to a file. In the file, the data in the input file should be restated and other information should be calculated throughout the program. These other information include the average price per brand, the average price per category, the list of SKU's per year, and the count SKU's per year.</p>

<h2 align="center">Techniques Used</h2>

<p>This problem requires many data structures to solve. The main ones I have used include maps and vectors. When a user runs the software, the program puts all of the input information in vectors of varying datatypes. The vectors are filled until there is no input left. To calculate the price per brand and price per category, the program utilizes maps with a key and value. The map stores a key with the brand and category and stores the prices as the value as a vector. Each price is pushed into the value vector until all of the necessary data is processed. Then, using the information in the map, the categories and prices are saved to the output file and the sum and averages are computed. Finally, the data is neatly saved and formatted in the output file.

\n

I have indepth, hand drawn trace documents showcasing each important function and the final output final. You can find them in this directory. </p>