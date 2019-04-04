min=40
max=200
step=40

while [ $min -le $max ]
do
  rate=`echo $min"kbps"`
  ns 2.tcl $rate
  echo "Data rate :"$rate
  gawk -f 2.awk out2.tr
  min=$((min + step))
done