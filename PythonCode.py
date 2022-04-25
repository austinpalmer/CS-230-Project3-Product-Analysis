''' 
    www.geeksforgeeks.org/python-program-to-read-file-word-by-word
    and
    www.w3schools.com/python/python_file_open.asp
    were used as references for reading through file input
'''
import re
import string

def ItemFrequency():
    # Initialize lists for storing items
    items = []
    itemsAppeared = []
    # Open file
    with open('Items.txt', 'r') as myfile:
        # Store into list items
        for line in myfile:
            for word in line.split():
                items.append(word)
        # Count appearences of an item in the list
        for i in range(len(items)):
            itemCounter = 0
            for j in range(len(items)):
                if items[i] == items[j]:
                    itemCounter += 1
            # If item has not been printed, then print it with # of occurences
            if items[i] not in itemsAppeared:
                print("{}: {}".format(items[i], itemCounter))
                itemsAppeared.append(items[i])

def SearchItem(item):
    items = []
    itemsAppeared = []
    itemCounter = 0
    # Open file
    with open('Items.txt', 'r') as myfile:
        # Store into list items
        for line in myfile:
            for word in line.split():
                items.append(word)
        # Count appearences of item in the list
        for i in range(len(items)):
            if items[i] == item:
                itemCounter += 1
    return itemCounter

def DisplayHistogram():
    items = []
    itemsAppeared = []
    with open('Items.txt', 'r') as myfile, open('frequency.dat', 'x') as newfile:
        # Store into list items
        for line in myfile:
            for word in line.split():
                items.append(word)
        # Count appearences of an item in the list
        for i in range(len(items)):
            itemCounter = 0
            for j in range(len(items)):
                if items[i] == items[j]:
                    itemCounter += 1
            # If item has not been printed, then print it with # of occurences
            if items[i] not in itemsAppeared:
                newfile.write(items[i])
                newfile.write(" ")
                newfile.write(str(itemCounter))
                newfile.write("\n")
                itemsAppeared.append(items[i])
