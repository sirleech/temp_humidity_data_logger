import csv

with open('DATA.CSV', 'rb') as csvfile:
	reader = csv.reader(csvfile, delimiter=',', quotechar='"')
	for row in reader:
		unix_time = row[0]
		temp = row[2]
		rh = row[3]
		print "unixtime: " + unix_time + "| temp: " + temp + "C" + "| RH: " + rh + "%"
