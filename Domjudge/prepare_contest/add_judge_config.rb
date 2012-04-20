colors = %w(blue red green yellow black pink purple gray orange white brown cyan)

pwd = Dir.pwd
Dir.glob("*").select { |f| File.directory?(f) }.each do |p|
  Dir.chdir(File.join(pwd, p))
  puts "# #{p}..."
  
  file_content = <<-TEXT
  probid = #{p}
  name = #{p}
  allow_submit = true
  color = #{colors.shift}
  timelimit = 1
  TEXT
  File.open("domjudge-problem.ini", 'w') {|f| f.write(file_content) }
  
  Dir.chdir(pwd)
end
