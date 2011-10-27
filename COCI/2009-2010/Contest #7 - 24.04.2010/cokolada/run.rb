#! /usr/bin/ruby
1000.times do
  x = rand(1000000) + 1
  system "echo #{x} | ./cokolada > a"
  system "echo #{x} | ./cokolada.2 > b"
  system "diff a b"
  system "rm a b"
end
