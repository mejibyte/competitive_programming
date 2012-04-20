pwd = Dir.pwd
Dir.glob("*").select { |f| File.directory?(f) }.each do |p|
  Dir.chdir(File.join(pwd, p))
  puts "# #{p}..."
  Dir.glob("*.ans") do |input|
    puts "  #{input}"
    new_name = input.gsub(".ans", ".out")
    File.rename input, new_name
  end
  system "dos2unix *"
  Dir.chdir(pwd)
end