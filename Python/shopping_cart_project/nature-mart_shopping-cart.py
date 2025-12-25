'''
*******************************************************************************
                        Nature Mart Shopping Cart
                      nature-mart_shopping-cart.py
                         Author: Avinash Erusu
                  Course: AP Computer Science Principles
                          For: AP Create Task
                              Year: 2022
*******************************************************************************
Description:
  This program acts as a virtual shopping cart. The customer receives a special coupon.
  The customer will then select 4 categories of products,
  and the store will select items that add up to the coupon amount.
  The customer will receive a receipt with all of the items.
'''


# Import Python's standard libraries
from random import randint, randrange, uniform

COUPON_AMOUNT_WON = 250

# Initialize constants for min and max prices for each store category
# The following costs are in cents
FRUIT_MIN_COST = 99
FRUIT_MAX_COST = 299
VEG_MIN_COST = 99
VEG_MAX_COST = 499
MEAT_MIN_COST = 799
MEAT_MAX_COST = 1399
BAKE_MIN_COST = 199
BAKE_MAX_COST = 2199
CAN_MIN_COST = 75
CAN_MAX_COST = 199

# The products in the following menu options are sold by pound
MENU_OPT_1 = 1
MENU_OPT_2 = 2
MENU_OPT_3 = 3
# The products in the following menu options are sold by qty
MENU_OPT_4 = 4
MENU_OPT_5 = 5

# Constants used for the receipt
LINE_WIDTH = 100
COMPANY_NAME = "Nature Cart"
COMPANY_PHONE = "888-NAT-CART"
COMPANY_ADDR = "127 Orchard Ct."


# Initialize lists of store categories
fruits = ["apple", "mixed berries", "banana", "orange", "grape",
          "pear", "kiwi", "tomato", "papaya", "passion fruit",
          "dragon fruit", "mango", "pineapple"]

vegetables = ["lettuce", "onion", "bellpepper", "cucumber", "corn",
              "carrot", "potato", "cabbage", "yam", "sweet potato", 
              "celery", "broccoli", "cauliflower", "spinach", "beet"]

meats = ["beef", "pork", "chicken", "sausage", "lamb", "tuna",
         "salmon", "tilapia", "shrimp", "turkey", "lobster", "oyster"]

baked_goods = ["bread", "cookies (12)", "croissants (6)",
               "apple pie", "pumpkin pie", "berry pie", "vanilla cake",
               "chocolate cake", "baguette", "bagels (12)",
               "apple turnovers (4)"]

canned_goods = ["canned beans", "canned tuna", "canned corn",
                "canned olives", "canned tomatoes", "canned green beans",
                "canned carrots", "canned mixed fruits", "condensed milk",
                "coconut milk", "cream of mushroom", "canned beef stew",
                "canned gumbo"]

# List of product categories available in the grocery store
product_categories = [fruits, vegetables, meats, baked_goods, canned_goods]

# Initialize a list containing category values that represent
# products sold by lb and products sold by quantity
product_by_lb = [MENU_OPT_1, MENU_OPT_2, MENU_OPT_3]
product_by_qty = [MENU_OPT_4, MENU_OPT_5]

# Functions
def get_customer_info():
  '''
    Asks for and receives the customer's name and ID

    Input:
      None
    
    Output:
      A tuple containing the customer's name and ID
      e.g.: ("Matthew Johnson", 20013947)
  '''
  customer_name = str.upper(input("Please enter your name: "))
  loyalty_num = str.upper(input("Please enter your Loyalty #: "))
  print(f"\nCongratulations, {customer_name}!!\nFor being our lucky 1,000th customer today, you have won ${COUPON_AMOUNT_WON}!!")
  print("Pick any 4 categories from the list below and we'll fill your cart with your choices (worth $250 or less)")

  return customer_name, loyalty_num

def display_menu():
  '''
    Presents a menu containing different product categories to theshopper
  '''
  print("\nOur categories are:\n\
        1. Fruits\n\
        2. Vegetables\n\
        3. Meats\n\
        4. Baked Goods\n\
        5. Canned Goods")

def display_chosen_categs(chosen_categories):
  '''
    Presents all of the categories that the customer has chosen so far
    in a comma separated list

    Input:
      A list representing the categories the customer has chosen so far
    
    Output:
      None
  '''
  for category in chosen_categories:
    print(category, end="")
    # Prints a comma and a space between the categories
    if(category != chosen_categories[-1]):
      print(", ", end="")

def validate_chosen_categ(customers_categories, categ_chosen, categ_counter):
  '''
    Ensures that the category the customer has chosen is valid
    i.e. The number they selected is 1-5 and has not already been chosen
    If the category the customer chose is invalid, they will be prompted to
    try again until they choose a valid category

    Input:
      A list representing all of the categories the customer chose so far
      An integer representing the category the customer chose
      An integer representing the number category they are choosing, out of 4
    
    Output:
      An integer representing the valid category the customer chose
      e.g. 4
  '''
  while((categ_chosen < 1) or (categ_chosen > 5) or (categ_chosen in customers_categories)):
    print("\nSorry, that is an invalid category.")
    
    # Displays the already-chosen categories only if
    # the user previously chose a valid category
    if(customers_categories != []):
      print("The categories you already chose are:")
      display_chosen_categs(customers_categories)
    
    display_menu()
    categ_chosen = int(input("\nEnter choice [" + str(categ_counter + 1) + " of 4]: "))
  
  return categ_chosen

def get_categories():
  '''
    Prompts the user to select 4 categories, one after the other
    and stores the entered choices into a list

    Input:
      None
    
    Output:
      A list of integers representing 4 categories the shopper chose
      e.g.: [1, 5, 3, 2]
  '''
  # Initialize a list, populate it based on the customers' category selection
  customers_categories = []

  for categ_counter in range(4):
    display_menu()
    print("Please enter a number [1-5] to select a category.")
    categ_chosen = input("Enter choice [" + str(categ_counter + 1) + " of 4]: ")
    categ_chosen = int(categ_chosen)

    categ_chosen = validate_chosen_categ(customers_categories, categ_chosen, categ_counter)
    
    customers_categories.append(categ_chosen)

    # Displays all selected categories
    print("\nCategories selected so far: ", end="")
    display_chosen_categs(customers_categories)

  return customers_categories

def pick_product(menu_choice):
  '''
    Randomly selects an item from a given list
    
    Input:
      An integer that corresponds to one of the 5 categories of products

    Output:
      The randomly selected product as a string
      e.g.: "pumpkin pie"
  '''
  category_chosen = product_categories[menu_choice - 1]
  index = randrange(len(category_chosen))
  product = category_chosen[index]

  return product

def gen_qty(menu_choice):
  '''
    Randomly generates a number that represents how much of an item will be purchased.
    This number is a float for products sold by pound,
    and an integer for products sold by quantity
    
    Input:
      An integer that corresponds to one of the 5 categories of products

    Output:
      A number representing the amount of the item that will be purchased
      e.g.: 2.6
  '''
  if(menu_choice in product_by_lb):
    quantity = round(uniform(1, 5), 2)  # Pick an amount between 1 and 5
  else:
    quantity = randint(1, 5)            # Pick an amount between 1 and 5
  
  return quantity

def gen_price(menu_choice):
  '''
    Randomly generates a price for an item
    
    Input:
      An integer that corresponds to one of the 5 categories of products

    Output:
      A float that represents the price of 1 item
      e.g.: 13.52
  '''
  if(menu_choice == 1):
    price = randint(FRUIT_MIN_COST, FRUIT_MAX_COST)
  elif(menu_choice == 2):
    price = randint(VEG_MIN_COST, VEG_MAX_COST)
  elif(menu_choice == 3):
    price = randint(MEAT_MIN_COST, MEAT_MAX_COST)
  elif(menu_choice == 4):
    price = randint(BAKE_MIN_COST, BAKE_MAX_COST)
  else:
    price = randint(CAN_MIN_COST, CAN_MAX_COST)
  
  price /= 100    # Converts the generated value into 2 decimal; x.xx format

  return price

def pack_product(menu_choice):
  '''
    Combines a product's name, quantity, price per item, and total price into a tuple

    Input:
      An integer that corresponds to one of the 5 categories of products

    Output:
      A tuple that contains the product name, quantity, price per item, and total price
      e.g.: ("potatoes", 3.4, 4, 13.60)
  '''

  item_name  = pick_product(menu_choice)
  item_qty   = gen_qty(menu_choice)
  item_price = gen_price(menu_choice)
  total_item_cost = round(item_qty * item_price, 2)   # Calculate total cost of quantity number of items

  packed_product = (item_name, item_qty, item_price, total_item_cost)

  return packed_product

def pack_all_products(menu_choices):
  '''
    Conbines several tuples, each tuple representing a single product, into a list
    that represents the customer's shopping cart.

    Input:
      A list of integers representing 4 categories the shopper chose

    Output:
      A list containing several tuples, each tuple representing a single product.
      Each tuple contains the product's name, quantity, price per item, and total price
      Also returns the total cost of every product in the cart
      These two items are in a tuple
      e.g.:
        ([('beef', 8.84, 12.76, 112.8), ('carrot', 14.0, 1.67, 23.38)], 136.18)
  '''

  # Initialize an empty list to dynamically build a shopping cart
  # containing random items from store categories
  cart = []

  # Holds the cost of all products selected so far
  total_cart_cost = 0
  index_of_product_cost = -1
  menu_index = 0
  duplicate_product = False

  # Iterate over each menu choice from the menu_choices list
  while(total_cart_cost <= COUPON_AMOUNT_WON):
    # Takes remainder by 4 to loop through the 4 item list
    # since it will only return 0, 1, 2, or 3
    menu_choice = menu_choices[menu_index % 4]
    product = pack_product(menu_choice)
    product_cost = product[index_of_product_cost]

    # Adds the product to the cart only if the item doesn't go over the budget
    if((total_cart_cost + product_cost) <= COUPON_AMOUNT_WON):
      # Only checks for duplicate products if the cart isn't empty
      if(len(cart) > 0):
        # Goes through each item in the cart and makes sure
        # the currently selected item isn't already in the cart
        for item in range(len(cart)):
          if(product[0] in cart[item][0]):
            duplicate_product = True
            break
      
      # If the currently selected item is not in the cart, it is added to the cart
      if(not duplicate_product):
        total_cart_cost += product_cost
        cart.append(product)
      
      duplicate_product = False
    else:
      break

    menu_index += 1
  
  # Pack tuple with filled cart and total cost
  return (cart, total_cart_cost)

def print_banner(customer_name, customer_id):
  '''
    Prints the banner/header of the final receipt

    Input:
      The customer's name
      The customer's Member ID
    
    Output:
      None
  '''
  print("\n\n")
  print("=" * LINE_WIDTH)
  #TODO: try to use LINE_WIDTH constant instead of 40:
  print(f'{COMPANY_NAME:^100s}')
  print(f'{COMPANY_PHONE:^100s}')
  print(f'{COMPANY_ADDR:^100s}')
  print("=" * LINE_WIDTH)
  
  print("Customer Name: " + str(customer_name))
  print("Member ID: " + str(customer_id))

  # Prints the header for the list of products bought
  print(" " * 15, end="")
  print(f'{"S#":<2s}', end="")
  print(" " * 10, end="")
  print(f'{"Product Name":<20s}', end="")
  print(" " * 13, end="")
  print(f'{"Quantity":<8s}', end="")
  print(" " * 10, end="")
  print(f'{"Price":<7s}', end="")
  print(" " * 15)

  print("-" * LINE_WIDTH)

def print_products(cart, total_cart_cost):
  '''
    Prints all of the products in the cart as a receipt

    Input:
      A list representing the customer's shopping cart containing all of the products and their
      respective quantities, prices, and total prices
      The total cost of all the products in the cart
    
    Output:
      None
      
  '''
  for product in range(len(cart)):
    print(" " * 15, end="")
    print(f'{(product + 1):>2n}', end="") # Prints the Serial number / item number of the item, right justified
    print(" " * 10, end="")
    print(f'{cart[product][0]:<20s}', end="") # Prints the product name
    print(" " * 13, end="")
    print(f'{cart[product][1]:>8n}', end="") # Prints the product quantity
    print(" " * 10, end="")
    print("$", end="") # Prints the $ for the price (takes the 7th of the characters allocated for it)
    print(f'{cart[product][3]:>6.2f}', end="") # Prints the total price for qty # of that item
    print(" " * 15)

  # Prints the total price of the receipt
  print()
  print(f'{"Total Price:":>68}', end="")
  print(" " * 10, end="")
  print("$" + (f'{total_cart_cost:>6.2f}'), end="")
  print(" " * 15)

def print_footer():
  '''
    Prints the footer of the receipt

    Input:
      None
    
    Output:
      None
  '''
  print("=" * LINE_WIDTH)
  print(f'{"Thank you for shopping with us":^100s}')
  print("=" * LINE_WIDTH)



customer_name, member_id = get_customer_info()

customers_categories = get_categories()
shopping_cart, total_cost = pack_all_products(customers_categories)

total_cost = round(total_cost, 2)

print_banner(customer_name, member_id)
print_products(shopping_cart, total_cost)
print_footer()