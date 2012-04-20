require 'fileutils'

pwd = Dir.pwd
Dir.glob("*").select { |f| File.directory?(f) }.each do |p|
  Dir.chdir(File.join(pwd, p))
  puts "# #{p}..."
  
  puts "Zipping..."
  FileUtils.rm_f "bundle.zip"
  system("zip bundle.zip *")
  
  puts "Uploading..."
  system("curl -vv -F upload=Upload -F problem_archive=@bundle.zip --user admin:espectacular http://juez.factorcomun.org/jury/problem.php")
  Dir.chdir(pwd)
end
