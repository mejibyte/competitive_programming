require 'highline/import'

template = "probid = PROBID
name = NAME
allow_submit = ALLOW_SUBMIT
color = COLOR
timelimit = TIMELIMIT
"

id = nil
name = nil
allow_submit = nil
color = nil
timelimit = nil

begin
  id = ask("Problem ID (Max. 8 characters)? ") do |q|
    q.validate = /\A[a-z0-9]{1,8}\Z/ 
    q.default = id
  end
  
  name = ask("Full problem name? ") do |q| 
    q.validate = /\A.{1,}\Z/ 
    q.default = name
  end
  allow_submit = ask("Allow submit? (true or false) ") do |q|
     q.validate = /true|false/
     q.default = allow_submit || "true"
  end
  
  color = ask("Color? (Suggestions: blue, red, green, yellow, black, pink, purple, gray, orange, white, brown, cyan) ") do |q|
    q.default = color
    q.validate = /\A.{1,}\Z/
  end
  
  timelimit = ask("Timelimit? (in seconds) ", Integer) do |q|
    q.in = 1..60 
    q.default = timelimit
  end

  puts "ID = '#{id}'"
  puts "Name = '#{name}'"
  puts "Allow submit = #{allow_submit}"
  puts "Color = '#{color}'"
  puts "Timelimit = #{timelimit}"

end while !agree("Is everything correct? (y/n) ")

content = template.gsub("PROBID", id).gsub("NAME", name).gsub("ALLOW_SUBMIT", allow_submit).gsub("COLOR", color).gsub("TIMELIMIT", timelimit.to_s)
File.open("domjudge-problem.ini", "w") { |f| f.write(content) }
puts "Wrote file domjudge-problem.ini"
