* Show welcome screen and ask the user to enter their name and a loyalty number  
  MAIN MENU:  
  \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*  
                                                   Welcome to EZ-MART  
  Enter your last name:  
  Enter your loyalty number:  
  \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*  
    
  MENU \#2  
  \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*  
  You have won $\_\_  
  Select 4 categories from the following list of product categories:  
1.  Fruits & Vegetables  
2. Meats  
3. Cleaning Supplies  
4. Pharmacy  
5. Music & Movies  
6. Games

  Select your category \[1 of 3\]:      \<shopper enters a category number\>

  Select your category \[2 of 3\]:

  Select your category \[3 of 3\]:

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*  
Here are the products we have selected for you worth your winning amount\!\!\!\!\!\!

1. Eggs  \[2 doz\]                                              8.99  
2. Potatoes \[2 \* 5lb\]                                   10.87  
3. Pepto Bismol \[1\]                                        6.99  
4. DVDs \[6\]                                                    79.99  
   Tax \[8.25%\]                                              13.49  
     
   Total                                                          199.99       \[must be less than winning amount\]  
   \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*  
     
     
     
     
     
     
 


MENU \#2:

1. Iterate over 3 or 4 times to collect user’s choice and store them either in a list or 4 separate variables  
2. Prompt the user if they entered wrong choice (error-handling)

DETAILS:

1. Define a LIST for each set of categories that contain sample data  
2. A function that calculates price per each category of items  
   1. This function should accept   
   2. It should return …  
        
3. A function that generates a tuple based on a random product (out of selected category), quantity, and cost  
   1. This function accepts….  
   2. It returns a tuple that looks like (“potatoes”, 4, 9.99)  
   3.   
4. A function that creates a list containing customer’s name, followed by tuples containing product, quantity, and amount, for e.g.:  
     
   \[“John Doe”, “Loyalty\#”, (“potatoes”, 4, 9.99), (“Port”, 4, 29.99), (“Pepto”, 1, 9.99)…\]  
     
5. A

* Say that they are a lucky customer and won free groceries that value up to $250. Store prompts a list of categories and prompts the buyer to pick 4 categories.   
* Response should be in the form of 4 numbers with no spaces in between, e.g. 1542  
  * *How-To: Make sure the 4 numbers the user chose are valid*  
    * *Repeat through each input.*   
    * *Check if each character is a number or not*  
    * *Check if the numbers correspond to an actual category i.e. if there are 5 categories, then they can’t input 6 or above*  
* Pick a random product from each of the 4 categories  
  * Use a random number generator to pick an item, as well as assign a price and quantity to it  
  * Add these elements to the cart  
* Display a receipt  
  * Should have the user’s name, their loyalty number, the items, their quantity, their prices, the total price of the items, and a number representing store points that they received for using our store.  
    * (Possible idea) If the items don’t completely add up to $250, then give the remaining amount to the customer in the form of a gift card/extra store points.