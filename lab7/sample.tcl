proc finish {} {
  global ns nf
  $ns flush-trace
  close $nf
  exec nam out.nam &
  exit 0
}

set ns [new Simulator]

$ns color 1 Red
$ns color 2 Blue

set nf [open out.nam w]
$ns namtrace-all $nf

# create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# setup links
$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link-op $n0 $n2 orient right-down

$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link-op $n1 $n2 orient right-up

$ns duplex-link $n2 $n3 1.7Mb 20ms DropTail
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n2 $n3 queuePos 0.5
$ns queue-limit $n2 $n3 10

# setup ftp and tcp over n0 n3
set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set tcpsink [new Agent/TCPSink]
$ns attach-agent $n3 $tcpsink
$ns connect $tcp $tcpsink
$tcp set fid_ 1

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

# setup cbr and udp over n1 n3
set udp [new Agent/UDP]
$ns attach-agent $n1 $udp
set null [new Agent/Null]
$ns attach-agent $n3 $null
$ns connect $udp $null
$tcp set fid_ 2

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR

# schedule events
$ns at 0.1 "$cbr start"
$ns at 1.0 "$ftp start"
$ns at 4.0 "$ftp stop"
$ns at 4.5 "$cbr stop"
$ns at 5.0 "finish"

$ns run