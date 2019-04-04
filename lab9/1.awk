BEGIN {
  udp_pkt_total = 0
  udp_pkt_drop = 0
  udp_pkt_success = 0
  tcp_pkt_total = 0
  tcp_pkt_drop = 0
  tcp_pkt_success = 0
}
{
  event = $1
  curr_node= $3
  level = $4
  type = $7

  if(event == "D") {
    if(type == "cbr") udp_pkt_drop++
    else if(type == "tcp") tcp_pkt_drop++
  }

  if(level == "AGT") {
    if(type == "cbr") {
      if(event == "s") udp_pkt_total++   
      if(event == "r" && curr_node == "_9_") udp_pkt_success++
    }

    else if(type == "tcp") {
      if(event == "s") tcp_pkt_total++
      if(event == "r" && curr_node == "_1_") tcp_pkt_success++
    }
  }
}
END {
  printf("TCP Packet Drop Ratio: %.2f\nPacket delivery successs: %d\n",
   (tcp_pkt_drop / tcp_pkt_total), tcp_pkt_success)
  printf("UDP Packet Drop Ratio: %.2f\nPacket delivery successs: %d\n",
   (udp_pkt_drop / udp_pkt_total), udp_pkt_success)
}