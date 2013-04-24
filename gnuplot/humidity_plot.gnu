# a gnuplot script
# ubuntu $ sudo apt-get install gnuplot
#        $ gnuplot -persist plot_temp_humidity.gnu

set datafile separator ","
set xdata time
set timefmt "%s"
set format x "%m/%d/%Y %H:%M:%S"

set xlabel 'Time AEST'
set ylabel 'Relative Humidity %'

set xtics rotate

plot '../sample_data/DATA.CSV' using 1:3
