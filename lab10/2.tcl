proc finish {} {
  global ns nf nt
  $ns flush-trace
  close $nf
  close $nt
  # exec nam out2.nam
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

# get argument
set rate [lindex $argv 0]

# setup links

$ns duplex-link $n0 $n1 1Mb 50ms DropTail
$ns duplex-link-op $n0 $n1 orient right

$ns duplex-link $n1 $n2 100Kb 5ms DropTail
$ns duplex-link-op $n1 $n2 orient right

# tcp 0 to 2

set udp [new Agent/UDP]
$ns attach-agent $n0 $udp
set null [new Agent/Null]
$ns attach-agent $n2 $null
$ns connect $udp $null
set cbr [new Application/Traffic/CBR]
$cbr set rate_ $rate
$cbr attach-agent $udp

$ns at 1.0 "$cbr start"
$ns at 9.0 "$cbr stop"
$ns at 10.0 "finish"

$ns run

