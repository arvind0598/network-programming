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
$ns duplex-link $n0 $n1 2Mb 10ms DropTail
$ns duplex-link-op $n0 $n1 orient up

$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link-op $n1 $n2 orient right

$ns duplex-link $n2 $n3 2Mb 10ms DropTail
$ns duplex-link-op $n2 $n3 orient down

$ns duplex-link $n3 $n0 2Mb 10ms DropTail
$ns duplex-link-op $n3 $n0 orient left

# setup n0 n1 as a ftp tcp link
set tcp1 [new Agent/TCP]
$ns attach-agent $n0 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP

# setup n2 n3 as a cbr udp link
set udp2 [new Agent/UDP]
$ns attach-agent $n2 $udp2
set null2 [new Agent/Null]
$ns attach-agent $n3 $null2
$ns connect $udp2 $null2
$udp2 set fid_ 2

set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $udp2
$cbr2 set type_ CBR

# events
$ns at 1.0 "$ftp1 start"
$ns at 2.0 "$cbr2 start"
$ns rtmodel-at 5.0 down $n0 $n1
$ns at 9.0 "$cbr2 stop"
$ns at 10.0 "finish"

$ns run