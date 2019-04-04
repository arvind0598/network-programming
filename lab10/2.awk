BEGIN {
  start_time = 100
  stop_time = 0
  recv_data = 0
  drop_pkt = 0
}
{
  event = $1
  time = $2
  from_node = $3
  to_node = $4
  pkt_size = $6
  
  if(time < start_time && event == "+") start_time = time
  else if(time > end_time && event == "r") end_time == time

  if(event == "d") drop_pkt++
  if(event == "r") recv_data += pkt_size
}
END {
  printf("Throughput: %.2f\nDropped: %d\n\n", 
  recv_data / (start_time - stop_time) * 0.008, drop_pkt)
}