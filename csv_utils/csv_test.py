import csv

with open('../sample_data/DATA.CSV', 'rb') as csvfile:
	reader = csv.reader(csvfile, delimiter=',', quotechar='"')
	for row in reader:
		unix_time = row[0]
		temp = row[1]
		rh = row[2]
		print "unixtime: " + unix_time + "| temp: " + temp + "C" + "| RH: " + rh + "%"
