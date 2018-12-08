import os
import sys

# print "Hey"
# i=10000000; #10e7
# while i<=1000000000: #10e9
# 	#print i
# 	os.system("mpirun -np 2 ./trap_parallel.out 0 1 "+str(i+1)+" -hostfile machines"+" >> stepVtime_parallel")
# 	#print "Here"
# 	os.system("mpirun ./trap_serial.out 0 1 "+str(i+1)+" -hostfile machines"+" >> stepVtime_serial")
# 	i=i+100000000 #10e8
	

f1=open("parallel","r")
f2=open("serial","r")

parallel=f1.read().split("\n");
serial=f2.read().split("\n");

# i=1;
# while i<len(parallel):
# 	parallel[1].replace("\n","")
# 	serial[1].replace("\n","")
# 	print repr(parallel[1])
# 	print "Here"
# 	parallel[1]=str(float(parallel[1])/float(serial[1]))+'\n'

parallel_list=[]
for line in parallel:
	line=line.split(" ");
	parallel_list.append(line);


serial_list=[]
for line in serial:
	line=line.split(" ");
	serial_list.append(line);
# print serial_list

for line in parallel_list:
	for line2 in serial_list:
		# print line +" "+line2
		if len(line)>1 and line[0]==line2[0]:
			line[1]=str(float(line2[1])/float(line[1]))
# final_list=[[]]
# for line in (0,len(serial_list),1):
# 	if len(parallel_list[line])>1 and len(serial_list[line])>1:
# 		final_list[line][0]=line+1
# 		final_list[line][1]=str(float(parallel_list[line][1])/float(serial_list[line][1]))
# 		final_list[line][2]='\n'
# f1.close();
# f2.close();

file_write=""
for line in parallel_list:
	if len(line)>1:
		file_write=file_write+line[0]+" "+line[1]+"\n"

# print file_write
f=open("speed","w")
f.write(file_write)

