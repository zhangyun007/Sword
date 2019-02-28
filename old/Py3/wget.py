import os
import sys
import urllib.request
 
os.chdir("/var/tmp")
os.getcwd()
 
for url in sys.argv:
 
        if url != "wget.py" :
 
                name = url.split('/')[-1]
 
                print(name)
         
                a = urllib.request.urlopen(url)
         
                f = open(name, "wb")
         
                f.write(a.read())
         
                f.close()
         
                print(name+ ' Saved!')
