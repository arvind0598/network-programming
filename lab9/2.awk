BEGIN {
  recv_size = 0.0
  start_time = 400
  stop_time = 0
}

{
  event = $1
  time = $2
  from_node = $3
  to_node = $4
  pkt_size = $6
  if(start_time > time) start_time = time
  if(event == "r") {
    if(stop_time < time) stop_time = time
    if(to_node == 3) recv_size += pkt_size
  }
}

END {
  printf("Throughput : %.2f kbps\n", recv_size/(stop_time - start_time) * 0.008)
}