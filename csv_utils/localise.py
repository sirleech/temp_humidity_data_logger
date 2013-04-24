import csv

ifile  = open('../sample_data/DATA.CSV', 'rb')
ofile  = open('../sample_data/localised.CSV', 'wb')
reader = csv.reader(ifile, delimiter=',', quotechar='"')
writer = csv.writer(ofile, delimiter=',', quotechar='"')

header = ["Time UTC+10","Temperature (c)","RH (%)"]
writer.writerow(header)

reader.next()
for row in reader:
	unix_time = row[0]
	row[0] = int(unix_time) + 36000
	writer.writerow(row)

ifile.close()
ofile.close()
