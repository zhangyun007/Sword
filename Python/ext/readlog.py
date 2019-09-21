#!/usr/bin/python 
#coding:UTF-8

import time
import os, sys, io

# sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf-8')

d = {}

f = open('log') 
#f = open('/var/log/nginx/access.log') 

try: 
	while True: 
		line = f.readline() 
		if len(line) == 0: 
			break 
		print(line) 
		a = line.split(' ')
	# a[0]为时间  a[1]为接口 a[2]为响应时间
	if a[1] in d.keys():
		d[a[1]][0] += 1
		d[a[1]][1] += float(a[2])
		if float(a[2]) >= 0.1:
			d[a[1]][2] +=1
	else:
		# [0,0,0] 第一项为访问次数，第二项为响应时间总和，第三项为超过100ms的次数
		if float(a[2]) >= 0.1:
			d[a[1]] = [1, float(a[2]), 1]
		else:
			d[a[1]] = [1, float(a[2]), 0]
finally: 
	f.close()

print(d)

#计算接口的平均相应时间
for x in d.keys():
	d[x][1] = d[x][1] / d[x][0]

# 按照接口访问次数倒序排序
c = sorted(d.items(), key=lambda d:d[1][0], reverse=True)

print(c)