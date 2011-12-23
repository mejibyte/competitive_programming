n = 10
20.times do
  puts n
  5.times do
    first = rand(n) + 1
    print first

    (rand(8) + 1).times do
      second = first
      until second != first
        second = rand(n) + 1
      end
      print " "
      print second
    end
    puts

  end

  puts 0
end
puts 0