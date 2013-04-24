# a gnuplot script
# ubuntu $ sudo apt-get install gnuplot
#        $ gnuplot -persist plot_temp_humidity.gnu

set datafile separator ","
set xdata time
set timefmt "%s"
set format x "%m/%d/%Y %H:%M:%S"

set xlabel 'Time'
set ylabel 'Humidity %'

set xtics rotate

plot 'DATA.CSV' using 1:4 with linespoints
