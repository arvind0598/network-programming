BEGIN {
  pkt_total = 0
  pkt_drop = 0
  pkt_success = 0
}
{
  event = $1
  curr_node_str = $3
  curr_node = 0 + substr($3, 2, length($3) - 2)
  level = $4
  
  dest_node_str = $15
  split(dest_node_str, dest_node_arr, ":")
  dest_node = 0 + dest_node_arr[1]

  if(event == "s") pkt_total++
  if(event == "D") pkt_drop++
  if(level == "AGT" && curr_node == dest_node) pkt_success++
}
END {
  printf("Packet Drop Ratio: %f\nPacket delivery successs: %d\n",
   (pkt_drop / pkt_total), pkt_success)
}