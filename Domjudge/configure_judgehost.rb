# The purpose of this script is to configure the judgehosts after you have successfully configured
# and started the domserver and the instances that will run the judgehosts.
#
# This scripts takes at least two parameters:
# The first one is the public DNS of an EC2 instance running a DOMjudge server.
# The second one is the public DNS of an EC2 instance running a judgehost. 
# Alternatively, you can pass more jugehosts in the same way after the second parameter.
#
# What this script does:
#   - Connects to the domserver via SSH and downloads configuration files that should be shared
#     with the judgehosts.
#   - Connects to each judgehost and uploads those shared files.
#   - On each jugehost, starts the judging daemon.
#

require 'net/ssh'
require 'net/scp'
require 'fileutils'

def assert(value, message)
  unless value
    STDERR.puts message
    exit 1
  end
end

if ARGV.size < 2
  puts "Usage: ruby #{File.basename __FILE__} <host-to-domserver> <host-to-judgehost-1> [<host-to-judgehost-2> ...]"
  exit 1
end

domserver = ARGV[0]
domjudges = ARGV[1..-1]

assert domserver =~ /ec2[0-9-]+.compute-1.amazonaws.com/, "Host should be something like ec2-184-72-148-56.compute-1.amazonaws.com, but was #{domserver}."
domjudges.each_with_index do |judge, i|
  assert judge =~ /ec2[0-9-]+.compute-1.amazonaws.com/, "Judge #{i + 1} should be something like ec2-184-72-148-56.compute-1.amazonaws.com, but was #{judge}."
end


username = "ubuntu"
domserver_domjudge_path = "/home/ubuntu/domjudge/domserver"
judgehost_domjudge_path = "/home/ubuntu/domjudge/judgehost"

copy_files = %w(etc/dbpasswords.secret etc/common-config.php)

print "SSHing to Domserver #{username}@#{domserver}..."
Net::SSH.start(domserver, username) do |ssh|
  puts " OK"
  puts
  
  copy_files.each do |file|
    save_as = File.join("/tmp/domjudge", file)
    FileUtils.mkdir_p File.dirname(save_as)
    ssh.scp.download! File.join(domserver_domjudge_path, file), save_as
    puts "Downloaded #{file} from Domserver. Saved it to #{save_as}"
  end
end

 
print "Replacing localhost with the actual domserver host on passwords file..."

passwords_file = "/tmp/domjudge/etc/dbpasswords.secret"
content = File.read(passwords_file).gsub("localhost", domserver)
File.open(passwords_file, "w") do |f|
  f.write content
end

puts " OK"


domjudges.each_with_index do |judgehost, i|
  print "SSHing to Judgehost #{username}@#{judgehost}..."
  Net::SSH.start(judgehost, username) do |ssh|
    puts " OK"
    puts
    copy_files.each do |file|
      save_as = File.join(judgehost_domjudge_path, file)
      ssh.scp.upload! File.join("/tmp/domjudge", file), save_as
      puts "Copied #{file} to judgehost #{i + 1}. Saved it to #{save_as}"
    end

    print "Killing existing judgedaemons..."
    ssh.exec!("pkill -f bin/judgedaemon")
    puts " OK"
    
    print "Starting judgedaemon..."
    ssh.exec!("nohup #{File.join(judgehost_domjudge_path, "bin/judgedaemon")} > /dev/null 2>&1 &")
    running = ssh.exec!("pgrep -f bin/judgedaemon")
    puts " OK"
    
    running = running.split
    if running.size > 1
      puts "WARNING: Looks lake there are two different judgedaemons currently running on this judgehost!"
    end
    running.each { |s| puts "PID: " + s }
    
    host = ssh.exec!("hostname").chomp
    puts "Judge #{i + 1} is up and ready! Add #{host} as a judgehost on the domserver's web interface."
  end
end

puts
puts "Login to jury interface:"
puts " http://#{domserver}/jury"
username, password = content.split("\n").select { |l| l =~ /domjudge_jury/ }.first.split(":")[-2..-1]
puts " Username: #{username}"
puts " Password: #{password}"
