proc finish {} {
  global ns nf nt
  $ns flush-trace
  close $nf
  close $nt
}

set ns [new Simulator]
set nf [open out2.nam w]
set nt [open out2.tr w]
$ns namtrace-all $nf
$ns trace-all $nt

# create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]

# node config

$n1 shape square
$n1 color red

# get bandwidth from command line

set bandwidth [lindex $argv 0]
set bw "${bandwidth}Mb"

# setup links

$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link-op $n0 $n2 orient right-down

$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link-op $n1 $n2 orient right-up

$ns duplex-link $n2 $n3 $bw 10ms DropTail
$ns duplex-link-op $n2 $n3 orient right

$ns duplex-link $n3 $n4 1Mb 10ms DropTail
$ns duplex-link-op $n3 $n4 orient right-up

$ns duplex-link $n4 $n6 1Mb 10ms DropTail
$ns duplex-link-op $n4 $n6 orient right

$ns duplex-link $n3 $n5 1Mb 10ms DropTail
$ns duplex-link-op $n3 $n5 orient right-down

$ns duplex-link $n5 $n7 1Mb 10ms DropTail
$ns duplex-link-op $n5 $n7 orient right

# setup tcp ftp from 0 to 6

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n6 $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp

# setup udp cbr from 1 to 7
set udp [new Agent/UDP]
$ns attach-agent $n1 $udp
set null [new Agent/Null]
$ns attach-agent $n7 $null
$ns connect $udp $null
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp

# begin
$ns at 1.0 "$ftp start"
$ns at 2.0 "$cbr start"
$ns at 8.0 "$ftp stop"
$ns at 9.0 "$cbr stop"
$ns at 10.0 "finish"

$ns run