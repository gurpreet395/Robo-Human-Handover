import urllib2  # the lib that handles the url stuff
import time
while(True):
  data = urllib2.urlopen('http://10.200.35.62/Hand.txt') # it's a file like object and works just like a file
  for line in data: # files are iterable
    print line
    f = open("hand.txt", "w")
    f.write(line)      # str() converts to string
#f.write("0.5 0.3 0.2") 
  time.sleep(.5)
f.close()

