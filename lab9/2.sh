min=50
max=250
step=25
factor=100

while [ $min -le $max ]
do
  num1=`echo "$min.0/$factor.0" | bc -l`
  num2=`printf "%.2f" $num1`
  ns 2.tcl $num2
  echo "Bandwidth : "$num2"Mb"
  gawk -f 2.awk out2.tr
  min=$((min + step))
done