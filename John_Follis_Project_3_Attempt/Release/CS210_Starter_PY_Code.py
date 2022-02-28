import re
import string


"""The first function reads the file Groceries.txt and then prints out 
all of the itmes and how many times each were purchased.
"""
def printAllItems():
   num = 0
   food_list = []
   all_food  = []
   counter = 0

   f=open("Groceries.txt", "r")
   
   
   for word in f.readlines():
      line = word.rstrip()
      if line not in food_list:
         food_list.append(line)
   
   f.close()

   f = open("Groceries.txt", "r")

   for word in f.readlines():
      line = word.rstrip()
      all_food.append(line)

   f.close()
   
   while num < len(food_list):
      counter = all_food.count(food_list[num])
      print(food_list[num], counter)
      counter = 0 
      num += 1



""" This function takes a usersInput and then returns the number of
times the item was purchaed.
"""

def PrintSelectItem(v):
   num = 0
   food_list = []
   all_food  = []
   counter = 0

   f=open("Groceries.txt", "r")
   
   
   for word in f.readlines():
      line = word.rstrip()
      if line not in food_list:
         food_list.append(line)
   
   f.close()

   f = open("Groceries.txt", "r")

   for word in f.readlines():
      line = word.rstrip()
      all_food.append(line)

   f.close()
   
   counter = all_food.count(v)

   return counter ;



""" This Function reads the Groceries.txt file and then 
creates the file frequency.dat and writes all of the items and how many times 
they were purchased to the file.
"""

def createFile():
   num = 0
   food_list = []
   all_food  = []
   counter = 0

   f=open("Groceries.txt", "r")
   
   
   for word in f.readlines():
      line = word.rstrip()
      if line not in food_list:
         food_list.append(line)
   
   f.close()

   f = open("Groceries.txt", "r")

   for word in f.readlines():
      line = word.rstrip()
      all_food.append(line)

   f.close()
   
   f = open("frequency.dat", "w")
   while num < len(food_list):
      counter = all_food.count(food_list[num])
      f.write((food_list[num] + " " + str(counter) + "\n"))
      counter = 0 
      num += 1


    
