if ARGV.size < 1
  puts "Usage: #{__FILE__} program"
  exit -1
end

program = ARGV.first

Dir.glob("*.in.*").each do |file|
  answer_file = file.gsub('in', 'out')
  
  print "#{file}..."
  
  time_before = Time.now
  output = `#{program} < #{file} > out`
  elapsed_time = Time.now - time_before
  
  system("diff out #{answer_file} > /dev/null")

  if $?.success?
    puts "OK (#{elapsed_time} sec)"
  else
    puts "Wrong! (#{elapsed_time} sec)"
    puts "   Got '#{`cat out`.chomp}', expected '#{`cat #{answer_file}`.chomp}'"
  end
end