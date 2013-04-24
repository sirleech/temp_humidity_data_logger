import csv
import datetime

ifile  = open('../sample_data/DATA.CSV', 'rb')
ofile  = open('../sample_data/localised.CSV', 'wb')
ofile_readable  = open('../sample_data/localised_readable.CSV', 'wb')
reader = csv.reader(ifile, delimiter=',', quotechar='"')
writer = csv.writer(ofile, delimiter=',', quotechar='"')
writer_readable = csv.writer(ofile_readable, delimiter=',', quotechar='"')

header = ["Time (local)","Temperature (c)","RH (%)"]

# write first row of CSV as headers
writer.writerow(header)
writer_readable.writerow(header)

reader.next()
for row in reader:
	
	# adjust time to local timezone
	# utc + 10 AEST

	unix_time = row[0]
	offset = 10 * 60 * 60
	unix_time_adjusted = int(unix_time) + offset
	row[0] = unix_time_adjusted

	writer.writerow(row)
	readable_time = datetime.datetime.fromtimestamp(int(unix_time)).strftime('%Y-%m-%d %H:%M:%S')
	row[0] = readable_time
	writer_readable.writerow(row)

ifile.close()
ofile.close()
ofile_readable.close()
