import sys

def printfunction (string, number):
    print string + '\n'
    string += number

def main ():

    print 'fuck'
    printfunction ('shit', '0')
    printfunction ('shit', 7)
    printfunction ('shit', 3.5)

if __name__ == '__main__':
    main()
