import csv

ifile  = open('../sample_data/DATA.CSV', 'rb')

reader = csv.reader(ifile, delimiter=',', quotechar='"')

for row in reader:
	unix_time = row[0]
	temp = row[1]
	rh = row[2]
	print "unixtime: " + unix_time + "| temp: " + temp + "C" + "| RH: " + rh + "%"

ifile.close()
