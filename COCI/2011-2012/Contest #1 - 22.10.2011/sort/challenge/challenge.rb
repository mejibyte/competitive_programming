require 'rubygems'
require 'mechanize'

results_url = "http://hsin.hr/coci/results.php?contest=1"

input = "5
5 2 3 4 1"

expected_output = "5"

agent = Mechanize.new
puts "Opening #{results_url}..."
page = agent.get(results_url)
rows = page.search("table.rezultati tr")[1..-1]
rows.each do |row|
  name = row.search("td")[1].text
  link = row.search("td")[7].search("a")
  next if link.empty?
  score = link.text
  next unless score.to_i > 0
  
  url = "http://hsin.hr/coci/" + link.attr("href")

  print name
  
  if url =~ /\.cpp/ || url =~ /\.c/  
    print " (C++)"
    `curl -s #{url} > program.cpp`
    `g++ -Dlinux program.cpp`
    output = `echo '#{input}' | ./a.out`
  elsif url =~ /\.java/
    print " (Java)"
    `curl -s #{url} > Sort.java`
    src = `cat Sort.java`
    src.gsub!("Main", "Sort")
    File.open("Sort.java", "w") { |f| f.write(src) }
    `javac Sort.java`
    output = `echo '#{input}' | java Sort`
  end
  

  puts ": #{output}"

  if output =~ /5/
    puts "*** CORRECT *** (Score: #{score})"
  end
end
