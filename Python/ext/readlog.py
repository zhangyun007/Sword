#!/usr/bin/python 
#coding:UTF-8

import time
import os, sys, io

# sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')

d = {}

f = open('/var/log/nginx/access.log') 
try: 
    while True: 
        line = f.readline() 
        if len(line) == 0: 
            break 
        a = line.split(' ')
	for i in a:
		print(i)
finally: 
    f.close()
