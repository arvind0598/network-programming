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
set n4 [$ns node]

# setup links
$ns duplex-link $n0 $n4 2Mb 10ms DropTail
$ns duplex-link-op $n0 $n4 orient right-down

$ns duplex-link $n1 $n4 2Mb 10ms DropTail
$ns duplex-link-op $n1 $n4 orient left-down

$ns duplex-link $n2 $n4 2Mb 10ms DropTail
$ns duplex-link-op $n2 $n4 orient left-up

$ns duplex-link $n3 $n4 2Mb 10ms DropTail
$ns duplex-link-op $n3 $n4 orient right-up

# setup n0 n3 as a cbr udp link
set udp1 [new Agent/UDP]
$ns attach-agent $n0 $udp1
set null1 [new Agent/Null]
$ns attach-agent $n3 $null1
$ns connect $udp1 $null1
$udp1 set fid_ 1

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set type_ CBR

# setup n1 n2 as a cbr udp link
set udp2 [new Agent/UDP]
$ns attach-agent $n1 $udp2
set null2 [new Agent/Null]
$ns attach-agent $n2 $null2
$ns connect $udp2 $null2
$udp2 set fid_ 2

set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $udp2
$cbr2 set type_ CBR

# events
$ns at 1.0 "$cbr1 start"
$ns at 2.0 "$cbr2 start"
$ns at 8.0 "$cbr1 stop"
$ns at 9.0 "$cbr2 stop"
$ns at 10.0 "finish"

$ns run